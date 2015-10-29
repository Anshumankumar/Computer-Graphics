#ifndef R2D2_HPP
#define R2D2_HPP

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "object.hpp"
#include "scene.hpp"
#include "assembly.hpp"

class R2D2:public Assembly
{
    float headAngle, torsoAngle;
    float bendAngle;
    int walkFlag;
    public: 
    using Assembly::Assembly;
    void bendTorso();
    void bendBack();
    void bendFront();
    void rotateHand(double left,double right);
};

#endif

