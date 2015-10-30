#ifndef ENV_HPP
#define ENV_HPP

#include "object.hpp"
#include "humanoid.hpp"
#include "r2d2.hpp"
#include "assembly.hpp"

extern Assembly *robo;
extern Object *currentObject2;
class Env:public Object
{
    glm::vec3 cPos,cUp,cRot;
    int currentRobo = 0;
    std::vector<Assembly*> roboArray;
    public:
    Object env;
    Object spotLight;
    void draw();
    void addObject();
    void swap();
    void createViewMat();
    void initCam();
    void translate(float delx , float dely ,float delz);
    void rotate(float delx, float dely, float delz);
    void appendYaml(int frameNo);
    Env(int a);
};
#endif
