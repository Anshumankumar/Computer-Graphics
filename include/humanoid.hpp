#ifndef HUMANOID_HPP
#define HUMANOID_HPP

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "object.hpp"
#include "scene.hpp"
#include "assembly.hpp"

class Humanoid:public Assembly
{
    double lHAngle ,rHAngle,lAAngle,rAAngle;
    double bendAngle;
    int walkFlag;
    public:
    Humanoid(std::string yamlFile);
    void bendBack();
    void bendFront();
    void walk();
    void rotateArm(glm::vec3 left,glm::vec3 right);
    void rotateHand(double left,double right);
};

#endif

