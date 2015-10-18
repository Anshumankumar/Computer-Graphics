#ifndef R2D2_HPP
#define R2D2_HPP

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "object.hpp"
#include "scene.hpp"
#include "robo.hpp"

class R2D2:public Robo
{
  Object torso;
  Object head;
  Object leftLeg;
  Object rightLeg;
  double headAngle, torsoAngle;
  double bendAngle;
  int walkFlag;
public: 
  R2D2();
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

