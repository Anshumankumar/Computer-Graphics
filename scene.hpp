#ifndef SCENE_HPP
#define SCENE_HPP
#include "object.hpp"
#include <sstream>

struct matxyz 
{
    double x,y,z;
};

struct wcsObjectTranform 
{
    matxyz scale;
    matxyz rotate;
    matxyz translate;

};

class Scene
{
    int objectsNo;
    Object* objectArray;
    wcsObjectTranform *wcsTransformArray;
    matxyz eye;
    matxyz lookAt;
    matxyz upVector;
    double lenLeft,lenRight,lenTop,lenBottom;
    double distanceNear,distanceFar;
    public:
    Scene(int noOfObjects);
    void parseFile(std::string filename);
    void draw();
};


#endif
