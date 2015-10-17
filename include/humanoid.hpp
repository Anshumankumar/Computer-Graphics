#ifndef HUMANOID_HPP
#define HUMANOID_HPP

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

class Humanoid:public Robo
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
    void translate(glm::vec3 del);
};

#endif

