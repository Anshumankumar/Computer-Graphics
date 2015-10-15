#ifndef HUMANOID_HPP
#define HUMANOID_HPP

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "object.hpp"
#include "scene.hpp"

class Humanoid
{
    Object body;
    Object head;
    Object leftArm;
    Object rightArm;
    Object rightHand;
    Object leftHand;
    Object leftFist;
    Object rightFist;
    Object neck;
    Object Antenna;
    Object leftThigh;
    Object rightThigh;
    Object leftLeg;
    Object rightLeg;
    Object leftFoot;
    Object rightFoot;
    Object torsal;
    double lHAngle ,rHAngle,lAAngle,rAAngle;
    double bendAngle;
    int walkFlag;
    public: 
    Humanoid();
    void createHierarchy();
    void draw();
    void bendBack();
    void bendFront();
    void walk();
    void rotateArm(glm::vec3 left,glm::vec3 right);
    void rotateHand(double left,double right);
};

#endif

