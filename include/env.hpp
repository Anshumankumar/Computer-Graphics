#ifndef ENV_HPP
#define ENV_HPP

#include <chrono>
#include <thread>
#include "object.hpp"
#include "humanoid.hpp"
#include "r2d2.hpp"
#include "assembly.hpp"

extern Assembly *robo;
extern Object *currentObject2;

double nCk(double n, double k);
std::vector<double> binomials(double n);

class Env:public Object
{
private:
    glm::vec3 cPos,cUp,cRot;
    glm::vec3 cpdel,crdel;
    std::map<std::string,Assembly*>::iterator currentRobo;
    std::map<std::string,Assembly*> roboArray;
    int numObjectsInEnv;
    int currObjIndx;
public:
    Object env;
    Object spotLight;
    Object bezierCamera;
    Object bezierControlVertices;
    Object bezierCurve;
    void draw();
    void addObject();
    void swap();
    void createViewMat();
    void initCam();
    void translate(float delx , float dely ,float delz);
    void rotate(float delx, float dely, float delz);
    void appendYaml(int frameNo);
    void parseFrame(int recordFlag = 0);
    void moveNext();
    void addBezierPoint();
    void removeLastBezierPoint();
    void computeBezierCurve();
    Env(int a);
};
#endif // ENV_HPP
