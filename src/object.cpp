#include "object.hpp"
#define DRAWLINES 1
extern GLuint shaderProgram;

Object::Object()
{
    triangleArraySize = 0;
    xrot = 0; yrot = 0; zrot = 0;
    xscale = 1; yscale = 1; zscale = 1;
    xtln = 0; ytln = 0; ztln = 0;
    currentZ = 0.0;
    name = "default";
    trianglePoint = NULL;
    triangleColor = NULL;
    outsideTransform = glm::mat4(1.0f);
    rotationFlag = 1;
    initVboVao();
}

void Object::updateCentroid(glm::vec3 rPoint)
{
    centroid[0] =   rPoint[0];
    centroid[1] =   rPoint[1];
    centroid[2] =   rPoint[2];
    rotationFlag = 0;
    createMat();
}

void Object::addChild(Object *child,glm::vec3 pP, glm::vec3 cP)
{
    childArray.push_back(child);
    child->translate(-cP[0]+pP[0],-cP[1]+pP[1],-cP[2]+pP[2]);
    child->updateCentroid(cP);
}
void Object::applyOutsideTransform(glm::mat4 t)
{
    outsideTransform = t;
    createMat();
}

void Object::givename(std::string tempName)
{
    name = tempName;
}

void Object::zIncrease()
{
        currentZ = currentZ+0.1;
        if (currentZ >=MAX_SIZE_Z) currentZ = MAX_SIZE_Z;
}

void Object::zDecrease()
{
        currentZ -=0.1;
        if (currentZ <=-MAX_SIZE_Z) currentZ = -MAX_SIZE_Z;
}

glm::vec4 Object::getPoint()
{
    glm::vec4 temp;
    temp[0] = currentX;
    temp[1] = currentY;
    temp[2] = currentZ;
    temp[3] = 1;
    return temp;
}

glm::vec4 Object::getColor()
{
    glm::vec4 temp;
    temp[0] = rand()%1000/1000.0;   
    temp[1] = rand()%1000/1000.0;   
    temp[2] = rand()%1000/1000.0;   
    temp[3] = 1;
    return temp;  
}

void Object::updateXY(GLFWwindow * window,double X,double Y)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
     
    currentX = (X/width -0.5)*2*MAX_SIZE_X ;
    currentY = -(Y/height -0.5)*2*MAX_SIZE_Y ;
}

void Object::push()
{
    std::cout<<"XYZ " << getPoint()[0] <<" " << getPoint()[1] << 
" " << getPoint()[2]<<"\n";
    pointStack.push_back(getPoint());
    colorStack.push_back(getColor());
    createTriangles();
}

void Object::pop()
{
    if (pointStack.size() >0)
    {
        pointStack.pop_back();
        colorStack.pop_back();
    }
    createTriangles();
}

void Object::createTriangles()
{
    int stackSize;
    stackSize = pointStack.size();
    triangleArraySize = 0;
    if (stackSize >=3)
    {
        if (trianglePoint != NULL)
        {
                delete trianglePoint;
                delete triangleColor;
        }
        triangleArraySize = 3*(stackSize/3);
        trianglePoint = new glm::vec4[triangleArraySize];
        triangleColor = new glm::vec4[triangleArraySize];
    }
    else
    {
        return;
    } 
    int triangleIt = 0;
    glm::vec4 tempVec ={0,0,0,0};
    for (int i=0; i < triangleArraySize;i++)
    {   
        triangleColor[triangleIt] = colorStack[i];
        trianglePoint[triangleIt++] = pointStack[i];
        tempVec = tempVec + pointStack[i];
    }
    if (rotationFlag == 1)
    {
        centroid[0] = tempVec[0]/(float)triangleArraySize;
        centroid[1] = tempVec[1]/(float)triangleArraySize;
        centroid[2] = tempVec[2]/(float)triangleArraySize;
    }
}

void Object::createConTriangles()
{
    int stackSize;
    stackSize = pointStack.size();
    triangleArraySize = 0;
    if (stackSize >=3)
    {
        triangleArraySize = 3*(stackSize-2);
        trianglePoint = new glm::vec4[triangleArraySize];
        triangleColor = new glm::vec4[triangleArraySize];
    }
    else
    {
        return;
    } 
    int triangleIt = 0;
    for (int i=0; i < stackSize-2;i++)
    {   
        triangleColor[triangleIt] = colorStack[i];
        trianglePoint[triangleIt++] = pointStack[i];
        triangleColor[triangleIt] = colorStack[i+1];
        trianglePoint[triangleIt++] = pointStack[i+1];
        triangleColor[triangleIt] = colorStack[i+2];
        trianglePoint[triangleIt++] = pointStack[i+2];
    }
}

void Object::initVboVao()
{
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, 
            20000000,
            NULL, GL_DYNAMIC_DRAW);

}
void Object::setVboVao()
{
    auto tempSize = sizeof(trianglePoint[0])*triangleArraySize;
    glBufferSubData( GL_ARRAY_BUFFER, 0, tempSize,
            trianglePoint );
    glBufferSubData( GL_ARRAY_BUFFER, tempSize,
            tempSize, triangleColor);
    uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
    glUseProgram( shaderProgram );
    GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
            BUFFER_OFFSET(0) );

    GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, 
            BUFFER_OFFSET(tempSize));
    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(transMatrix));

}

void Object::drawPointLines()
{
    setVboVao();
    glDrawArrays(GL_LINES,0,triangleArraySize-1);
    glDrawArrays(GL_POINTS,triangleArraySize-1,triangleArraySize);
}
void Object::draw()
{
    setVboVao();
    //std::cout <<name <<": "  << triangleArraySize << std::endl;
#if DRAWLINES == 0
    glDrawArrays(GL_TRIANGLES,0,triangleArraySize);
#else
    glDrawArrays(GL_LINES,0,triangleArraySize);
#endif
    for (auto& child:childArray)
    {
        child->draw();
    }
}

void printMat(glm::mat4 a)
{
    for ( int i = 0; i < 4;i++)
    {
        for ( int j = 0; j < 4;j++)
            std::cout << a[i][j] <<" ";
        std::cout << std::endl; 
    }   
}

void Object::createMat()
{
    glm::vec3 tmat;
    glm::mat4 transMatrix2;
    std::cout << centroid[0] <<"\n"; 
    tmat = {xtln,ytln,ztln };
    transMatrix = glm::translate(glm::mat4(1.0f),tmat);
    transMatrix = glm::translate(transMatrix, centroid);
    transMatrix = glm::rotate(transMatrix, xrot, glm::vec3(1.0f,0.0f,0.0f));
    transMatrix = glm::rotate(transMatrix, yrot, glm::vec3(0.0f,1.0f,0.0f));
    transMatrix = glm::rotate(transMatrix, zrot, glm::vec3(0.0f,0.0f,1.0f));

    transMatrix = glm::translate(transMatrix,-centroid);
    printMat(transMatrix2);
    tmat = {xscale,yscale,zscale };
    transMatrix = glm::scale(transMatrix,tmat);
    transMatrix = outsideTransform*transMatrix; 
    for(auto& child:childArray)
    {
        child->applyOutsideTransform(transMatrix);
    }
}

void Object::reset()
{
    xrot = 0; yrot = 0; zrot = 0;
    xtln = 0; ytln = 0; ztln = 0;
    glm::vec4 tempVec ={0,0,0,0};
    for (int i=0; i < triangleArraySize;i++)
    {   
        tempVec = tempVec + pointStack[i];
    }
    tempVec[0] = tempVec[0]/(float)triangleArraySize;
    tempVec[1] = tempVec[1]/(float)triangleArraySize;
    tempVec[2] = tempVec[2]/(float)triangleArraySize;
    for (int i=0; i < triangleArraySize;i++)
    {   
        pointStack[i]=pointStack[i]-tempVec;
        pointStack[i][3] = 1;
    }
    createTriangles();
    createMat();
}
void Object::savefile(std::string tempname)
{   
    std::string filename;
    if(tempname == "NOTHING")
    {
        std::cout << "Enter the Filename\n";
        std::cin >> filename;
    }
    else filename = tempname;
    filename = "../models/" +filename;
    std::ofstream fs(filename);
    if (!fs.is_open())
    {
        std::cout << "Unable to open file\n";
        fs.close();
        return;
    }  
    for (int i = 0; i <triangleArraySize;i++)
    {
        fs << trianglePoint[i][0];
        fs <<","; 
        fs << trianglePoint[i][1];
        fs <<","; 
        fs << trianglePoint[i][2];
        fs <<",";
        fs << triangleColor[i][0];
        fs <<",";
        fs << triangleColor[i][1];
        fs <<",";
        fs << triangleColor[i][2];
        fs <<std::endl;
    }
    fs.close();
    std::cout << "File Saved:"<< filename <<"\n";
}

void Object::readfile(std::string tempname)
{
    std::string filename;
    if(tempname == "NOTHING")
    {
        std::cout << "Enter the Filename\n";
        std::cin >> filename;
    }
    else filename = tempname;
    filename = "../models/" +filename;
    std::ifstream fs(filename);
    if (!fs.is_open())
    {
        std::cout << "Unable to open raw file\n";
        fs.close();
        return;
    }  
    while(fs.good())
    {
        std::string cline;
        fs >> cline;
        glm::vec4 cPoint,cColor;
        if (cline =="") continue;
        parseline(cline,cPoint,cColor);
        pointStack.push_back(cPoint);
        colorStack.push_back(cColor);
    }
    createTriangles();
    createMat();
}

void Object::parseline(std::string line,glm::vec4 &cPoint,
        glm::vec4 &cColor)
{
    std::string delimiter = ",";
    std::string token;
    for (int i =0;i<3;i++)
    {
        auto pos = line.find(delimiter);
        token = line.substr(0, pos);
        cPoint[i] = std::stof(token);   
        line.erase(0, pos + delimiter.length());
    }
    for (int i =0;i<3;i++)
    {
        auto pos = line.find(delimiter);
        token = line.substr(0, pos);
        cColor[i] = std::stof(token);   
        line.erase(0, pos + delimiter.length());
    }
    cPoint[3]=1;
    cColor[3]=1;
}

void Object::rotate( float delx, float dely, float delz)
{
    xrot = xrot+delx;
    yrot = yrot+dely;
    zrot = zrot+delz;
    createMat();
}

void Object::translate( float delx, float dely, float delz)
{
    xtln = xtln+delx;
    ytln = ytln+dely;
    ztln = ztln+delz;
    createMat();
}

void Object::resize(float sx,float sy,float sz)
{
    xscale = sx;
    yscale = sy;
    zscale = sz;
    createMat();
}
