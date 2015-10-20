#include "object.hpp"
#define DRAWLINES 0
extern GLuint shaderProgram;
int l1 =1;
int l2 =1;
int l3 =1;
Object::Object(std::string texImg)
{
    if (texImg == "NOTHING")
    {
        
        texImage = "../texture.jpg";
        texFlag = 0;
    }
    else
    {
        texImage = texImg;
        texFlag = 1;
    }
    xrot = 0; yrot = 0; zrot = 0;
    xscale = 1; yscale = 1; zscale = 1;
    xtln = 0; ytln = 0; ztln = 0;
    lxtln = 0; lytln = 0; lztln = 0;
    currentZ = 0.0;
    name = "default";
    outsideTransform = glm::mat4(1.0f);
    rotationFlag = 1;
    initVboVao();
}

void Object::startlight()
{
    lFlag = 1;
}
void Object::updateViewMat(glm::mat4 mat)
{
    viewMat = mat;
    for(auto& child:childArray)
    {
        child->updateViewMat(mat);
    }
    createMat();
}

void Object::changeTexImage(std::string tname)
{
    texImage = tname;
    texFlag = 2; 
    initVboVao();
}
void Object::loadImage()
{ 
  // std::cout << "Loading texture from: "<< texImage <<"\n"; 
  int width, height;
  unsigned char* image = SOIL_load_image(texImage.c_str(),
                                         &width, &height, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image);
  // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image);
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

Point Object::getPoint()
{
    Point point;
    point.x = currentX;
    point.y = currentY;
    point.z = currentZ;
    point.w = 1;
    point.cx = rand()%1000/1000.0;   
    point.cy = rand()%1000/1000.0;   
    point.cz = rand()%1000/1000.0;   
    point.ca = 1;   
    return point;
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
    pointArray.push_back(getPoint());
    createTriangles();
}

void Object::pop()
{
    if (pointArray.size() >0)
    {
        pointArray.pop_back();
    }
    createTriangles();
}

void Object::createTriangles()
{
}

void Object::initVboVao()
{
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, 
            20000000,NULL, GL_STATIC_DRAW);

    glUniform1i(glGetUniformLocation(shaderProgram, "texFlag"),texFlag);
    if (texFlag >=1 )
    {
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glUniform1i(glGetUniformLocation(shaderProgram, "mytex"), 0);
        glBindTexture(GL_TEXTURE_2D, tex);
        glActiveTexture(GL_TEXTURE0);  
        loadImage();
    }
}

void Object::setVboVao()
{

    glUniform1i(glGetUniformLocation(shaderProgram, "texFlag"),texFlag);
    glUniform1i(glGetUniformLocation(shaderProgram, "lFlag"),lFlag);
    glUniform1i(glGetUniformLocation(shaderProgram, "l1Flag"),l1);
    glUniform1i(glGetUniformLocation(shaderProgram, "l2Flag"),l2);
    glUniform1i(glGetUniformLocation(shaderProgram, "l3Flag"),l3);
    glBindTexture(GL_TEXTURE_2D, tex);
    auto tempSize = sizeof(Point)*pointArray.size();
    glBufferData( GL_ARRAY_BUFFER, tempSize, (void*)&pointArray[0],GL_STATIC_DRAW );
    uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
    normalMatrix = glGetUniformLocation( shaderProgram, "normalMatrix");
    viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");
    glUseProgram( shaderProgram );
    GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE,
            sizeof(Point), BUFFER_OFFSET(0));

    GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE,
            sizeof(Point), BUFFER_OFFSET(4*sizeof(float)));


    GLuint vNormal = glGetAttribLocation( shaderProgram, "vNormal" );
    glEnableVertexAttribArray( vNormal );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE,
            sizeof(Point),BUFFER_OFFSET(8*sizeof(float)));

    GLuint vTex = glGetAttribLocation( shaderProgram, "vTex" );
    glEnableVertexAttribArray( vTex );
    glVertexAttribPointer( vTex, 2, GL_FLOAT, GL_FALSE,
            sizeof(Point),BUFFER_OFFSET(11*sizeof(float)));


    glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(transMatrix));
    glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normalMat));
}

void Object::drawPointLines()
{
    setVboVao();
    glDrawArrays(GL_LINES,0,pointArray.size()-1);
    glDrawArrays(GL_POINTS,pointArray.size()-1,pointArray.size());
}
void Object::draw()
{
    setVboVao();
#if DRAWLINES == 0
    glDrawArrays(GL_TRIANGLES,0,pointArray.size());
#else
    glDrawArrays(GL_LINES,0,pointArray.size());
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
    transMatrix = glm::mat4(1.0f);
    transMatrix2 = glm::mat4(1.0f);
    tmat = {xtln,ytln,ztln };
    glm::vec3 ltmat = {lxtln,lytln,lztln };
    transMatrix = glm::translate(transMatrix, centroid);
    transMatrix = glm::rotate(transMatrix, xrot, glm::vec3(1.0f,0.0f,0.0f));
    transMatrix = glm::rotate(transMatrix, yrot, glm::vec3(0.0f,1.0f,0.0f));
    transMatrix = glm::rotate(transMatrix, zrot, glm::vec3(0.0f,0.0f,1.0f));
    transMatrix = glm::translate(transMatrix,-(centroid));

    tmat = tmat+ glm::mat3(transMatrix)*ltmat;
    xtln = tmat[0]; 
    ytln = tmat[1]; 
    ztln = tmat[2]; 
    transMatrix2 = glm::translate(transMatrix2,tmat);
    transMatrix = transMatrix2*transMatrix;

    tmat = {xscale,yscale,zscale };
    transMatrix = glm::scale(transMatrix,tmat);

    transMatrix = outsideTransform*transMatrix;
    for(auto& child:childArray)
    {
        child->applyOutsideTransform(transMatrix);
    }
    normalMat = glm::transpose (glm::inverse(glm::mat4(transMatrix)));

}

void Object::reset()
{
    xrot = 0; yrot = 0; zrot = 0;
    xtln = 0; ytln = 0; ztln = 0;
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
    filestore(fs,pointArray);
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
        std::cout << "Unable to open raw file"<<filename<<"\n";
        fs.close();
        return;
    }
    fileread(fs,pointArray);
    fs.close();
    createTriangles();
    createMat();
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

void Object::ltranslate( float delx, float dely, float delz)
{
    lxtln = lxtln+delx;
    lytln = lytln+dely;
    lztln = lztln+delz;
    createMat();
    lxtln = 0;
    lytln = 0;
    lztln = 0;
}


void Object::resize(float sx,float sy,float sz)
{
    xscale = sx;
    yscale = sy;
    zscale = sz;
    createMat();
}
