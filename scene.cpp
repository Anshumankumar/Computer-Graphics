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
    objectArray = new Object[objectsNo];
    wcsTransformArray = new wcsObjectTranform[objectsNo];
}

void Scene::parseFile(std::string filename)
{
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
            std::cout << i <<  cline << std::endl; 
        }

        if(i >=objectsNo) break;
    }
    std::stringstream ss;
    ss = getLine(fs);
    ss >> eye.x;
    ss >> eye.y;
    ss >> eye.z;
    ss = getLine(fs);
    ss >> lookAt.x;
    ss >> lookAt.y;
    ss >> lookAt.z;
    ss = getLine(fs);
    ss >> upVector.x;
    ss >> upVector.y;
    ss >> upVector.z;
    ss = getLine(fs);
    ss >> lenLeft;
    ss >> lenRight;
    ss >> lenTop;
    ss >> lenBottom;
    ss = getLine(fs);
    ss >> distanceNear;
    ss >> distanceFar;
}

void Scene::draw()
{
    for (int i; i<objectsNo;i++)
    {
        objectArray[i].draw();
    }
}
