#ifndef R2D2_HPP
#define R2D2_HPP

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "object.hpp"
#include "scene.hpp"
#include "robo.hpp"

class R2D2:public Robo
{
  Object axle;
  Object torso;
  Object head;
  Object leftLeg;
  Object rightLeg;
  float headAngle, torsoAngle;
  float bendAngle;
  const float kdbendAngle;
  int walkFlag;
public: 
  R2D2();
  void createHierarchy();
  void draw();
  void bendTorso();
  void bendBack();
  void bendFront();
  void walk();
  void rotateArm(glm::vec3 left,glm::vec3 right);
  void rotateHand(double left,double right);
  void translate(glm::vec3 del);
};

#endif

