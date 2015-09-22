#ifndef SCENE_HPP
#define SCENE_HPP
#include "object.hpp"
#include "utils.hpp"
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

class Scene:public Object
{
    public:
    enum state {WCS,VCS,CCS,NDCS,DCS};
    private:
    state currentState;
    int objectsNo;
    Object* objectArray;
    wcsObjectTranform *wcsTransformArray;
    Object frustum;
    glm::vec3 eye;
    glm::vec3 lookAt;
    glm::vec3 upVector;
    double lenLeft,lenRight,lenTop,lenBottom;
    double distanceNear,distanceFar;
    void createMat();
    glm::mat4 matWcsToVcs;
    glm::mat4 matVcsToWcs;
    glm::mat4 matVcsToCcs;
    glm::mat4 matCcsToNdcs;
    glm::mat4 matNdcsToDcs;
    glm::mat4 matFinal;
    void wcsToVcs();
    void vcsToCcs();
    void ccsToNdcs();
    void ndcsToDcs(double,double,double,double);
    void makeFrustum();
    public:
    Scene(int noOfObjects);
    void parseFile(std::string filename);
    void draw();
    void changeState(int current);
};


#endif
