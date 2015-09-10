#include "scene.hpp"

std::stringstream  getLine(std::ifstream &fs)
{
    std::string cline;
    std::stringstream ss;
    while(fs.good())
    {
        std::getline(fs,cline);
        if (cline == "" || cline[0]=='#')continue;
        break;        
    }
    ss.str(cline);
    return ss;
} 
Scene::Scene(int noOfObjects)
{
    objectsNo = noOfObjects; 
    objectArray = new Object[objectsNo+1];
    wcsTransformArray = new wcsObjectTranform[objectsNo];
    matWcsToVcs = glm::mat4(1.0f);
    matVcsToWcs = glm::mat4(1.0f);
    matVcsToCcs = glm::mat4(1.0f);
    matCcsToNdcs = glm::mat4(1.0f);
    matNdcsToDcs = glm::mat4(1.0f);
    currentState = WCS;

}

void Scene::parseFile(std::string filename)
{
    filename = "../" +filename;
    std::ifstream fs(filename);
    if(!fs.is_open())
    {
        std::cout << "Unable to open scan file\n";
        fs.close();
        exit(1);
        return;
    }
    std::string cline;
    int i = 0;
    while(fs.good())
    {
        std::getline(fs,cline);
        if (cline == "" || cline[0]=='#')continue;
        auto found = cline.find(".raw",0);
        if (found!=std::string::npos)
        {
            objectArray[i].readfile(cline);
            objectArray[i].givename(cline);
            objectArray[i].initVboVao();
            fs >> wcsTransformArray[i].scale.x;
            fs >> wcsTransformArray[i].scale.y;
            fs >> wcsTransformArray[i].scale.z;
            fs >> wcsTransformArray[i].rotate.x;
            fs >> wcsTransformArray[i].rotate.y;
            fs >> wcsTransformArray[i].rotate.z;
            fs >> wcsTransformArray[i].translate.x;
            fs >> wcsTransformArray[i].translate.y;
            fs >> wcsTransformArray[i].translate.z;
           objectArray[i].rotate(
                    wcsTransformArray[i].rotate.x,
                    wcsTransformArray[i].rotate.y,
                    wcsTransformArray[i].rotate.z
                    );
            objectArray[i].translate(
                    wcsTransformArray[i].translate.x,
                    wcsTransformArray[i].translate.y,
                    wcsTransformArray[i].translate.z
                    );
            objectArray[i].resize(
                    wcsTransformArray[i].scale.x,
                    wcsTransformArray[i].scale.y,
                    wcsTransformArray[i].scale.z
                    ); 
            i++;   
            std::cout << i<<": " <<  cline << std::endl; 
        }

        if(i >=objectsNo) break;
    }
    std::stringstream ss;
    ss = getLine(fs);
    ss >> eye[0];
    ss >> eye[1];
    ss >> eye[2];
    ss = getLine(fs);
    ss >> lookAt[0];
    ss >> lookAt[1];
    ss >> lookAt[2];
    ss = getLine(fs);
    ss >> upVector[0];
    ss >> upVector[1];
    ss >> upVector[2];
    ss = getLine(fs);
    ss >> lenLeft;
    ss >> lenRight;
    ss >> lenTop;
    ss >> lenBottom;
    ss = getLine(fs);
    ss >> distanceNear;
    ss >> distanceFar;
    wcsToVcs();
    vcsToCcs();
    ccsToNdcs();
    makeFrustum();
    createMat();
}
void Scene::makeFrustum()
{
    std::string filename = "../models/frustum.raw";
    std::ofstream fs(filename);
    if(!fs.is_open())
    {
        std::cout << "Unable to open scan file\n";
        fs.close();
        exit(1);
        return;
    }
    float f = distanceFar/distanceNear;
    glm::vec4 fp[8]=
        {
            {lenLeft,lenTop,-distanceNear,1},
            {lenRight,lenTop,-distanceNear,1},
            {lenRight,lenBottom,-distanceNear,1},
            {lenLeft,lenBottom,-distanceNear,1},
            {f*lenLeft,f*lenTop,-distanceFar,1},
            {f*lenRight,f*lenTop,-distanceFar,1},
            {f*lenRight,f*lenBottom,-distanceFar,1},
            {f*lenLeft,f*lenBottom,-distanceFar,1}
        };
    for (int i = 0;i<8;i++)
    {
        fp[i] = matVcsToWcs*fp[i];
    }
    for (int i =0;i<4;i++)
    {   
        filestore(fs,fp[i],0,1,1);
        filestore(fs,fp[i+4],0,1,1);
        filestore(fs,fp[i],0,1,1);
        filestore(fs,fp[(i+1)%4],0,1,1);
        filestore(fs,fp[i+4],0,1,1);
        filestore(fs,fp[((i+1)%4)+4],0,1,1);
    }
    glm::vec4 nearC ={0,0,-distanceNear,1};
    nearC = matVcsToWcs*nearC;
    filestore(fs,nearC[0],nearC[1],nearC[2],1,0,1);   
    filestore(fs,eye[0],eye[1],eye[2],1,0,1);   
    filestore(fs,eye[0],eye[1],eye[2],1,0,0);   
    
    fs.close(); 
    objectArray[objectsNo].readfile(filename);
    objectArray[objectsNo].givename(filename);

}

void Scene::changeState(int current)
{
    currentState = (state)current;
    createMat();
}

void Scene::createMat()
{  
    Object::createMat();
    if (currentState == WCS)
    {
        matFinal = transMatrix;
    }
    else if(currentState == VCS)
    {
        matFinal = transMatrix*matWcsToVcs;
    }
    else if (currentState == CCS)
    {
        matFinal = transMatrix*matVcsToCcs*matWcsToVcs;
    }
    else if (currentState == NDCS)
    {

        matFinal = transMatrix*matCcsToNdcs*matVcsToCcs*matWcsToVcs;
    }
    else if (currentState == DCS)
    {
        matFinal = transMatrix*matNdcsToDcs*matCcsToNdcs*
            matVcsToCcs*matWcsToVcs;
    }
    glm::mat4 ortho = glm::ortho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
    matFinal = ortho*matFinal;
    for (int i=0; i <objectsNo+1; i++)
    {
        objectArray[i].applyOutsideTransform(matFinal);
    }
}
void Scene::draw()
{
    for (int i; i<objectsNo;i++)
    {
        objectArray[i].draw();
    }
    objectArray[objectsNo].drawPointLines();
    Object::draw(); //No need of this, but just for fun
}
void Scene::wcsToVcs()
{
        glm::vec3 n = (eye-lookAt)/glm::length(eye-lookAt);
    glm::vec3 u = glm::cross(upVector,n);
    u = u/glm::length(u);
    glm::vec3 v = glm::cross(n,u);
    for (int i=0;i<3;i++)matWcsToVcs[i][0]=u[i];
    for (int i=0;i<3;i++)matWcsToVcs[i][1]=v[i];
    for (int i=0;i<3;i++)matWcsToVcs[i][2]=n[i];
    matWcsToVcs[3][0]=-glm::dot(eye,u);
    matWcsToVcs[3][1]=-glm::dot(eye,v);
    matWcsToVcs[3][2]=-glm::dot(eye,n);
    for (int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++) matVcsToWcs[i][j] = matWcsToVcs[j][i];
    }   
    for (int i=0;i<3;i++)
    {
        matVcsToWcs[3][i]=eye[i];
    }  

}

void Scene::ccsToNdcs()
{
    matCcsToNdcs[3][3] = 0;
    matCcsToNdcs[2][3] = -1;
    matCcsToNdcs[2][2] = (distanceFar+distanceNear)/(distanceNear-distanceFar);
    matCcsToNdcs[3][2] = 2*distanceFar*distanceNear/(distanceNear-distanceFar);
}
void Scene::vcsToCcs()
{
    matVcsToCcs[0][0] = 2*distanceNear/(lenRight-lenLeft);
    matVcsToCcs[1][1] = 2*distanceNear/(lenTop-lenBottom);

    matVcsToCcs[3][3] = 1;
    matVcsToCcs[2][3] = 0;
    matVcsToCcs[2][0] = (lenRight+lenLeft)/(lenRight-lenLeft);
    matVcsToCcs[2][1] = (lenTop+lenBottom)/(lenTop-lenBottom);
}
