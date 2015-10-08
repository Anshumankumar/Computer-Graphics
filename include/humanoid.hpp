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
    Object hip;
    public: 
    Humanoid();
    void createHierarchy();
    void draw();
};

#endif

