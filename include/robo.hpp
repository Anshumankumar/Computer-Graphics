#ifndef ROBO_HPP
#define ROBO_HPP

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "object.hpp"
#include "scene.hpp"

class Robo
{
  public:
    Object * mainObj; 
    virtual void createHierarchy() =0;
    virtual void draw()= 0;
    virtual void bendBack()= 0;
    virtual void bendFront() = 0;
    virtual void walk()= 0;
    virtual void rotateArm(glm::vec3 left,glm::vec3 right)= 0;
    virtual  void rotateHand(double left,double right)= 0;
    virtual  void translate(glm::vec3 del) =0;

};

#endif
