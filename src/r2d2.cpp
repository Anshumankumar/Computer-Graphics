#include "r2d2.hpp"

extern Object *currentObject;

R2D2::R2D2():
torso("../textures/r2d2_torso.jpg"),
  kdbendAngle(M_PI/36)
{
  bendAngle = 0;
  walkFlag = 0;
  currentObject = &axle;
  
  axle.readfile("r2d2_axle.raw");
  torso.readfile("r2d2_torso.raw");
  head.readfile("r2d2_head.raw");
  leftLeg.readfile("r2d2_leg.raw");
  rightLeg.readfile("r2d2_leg.raw");

  mainObj = &axle;
}

void R2D2::createHierarchy()
{
  glm::vec3 link_axle_torso = {.0, .0, .0};
  glm::vec3 link_torso_axle = {.0, .0, .370};
  glm::vec3 linkTorsoHead = {0,0,.54};
  glm::vec3 linkHeadTorso = {0,0,0};
  glm::vec3 linkTorsoLeftLeg= {.227, 0, .420};
  glm::vec3 linkLeftLegTorso = {.50, 0, 0};
  glm::vec3 linkTorsoRightLeg= {-.227, 0, .420};
  glm::vec3 linkRightLegTorso = {-.50, 0, 0};

  axle.addChild(&torso, link_axle_torso, link_torso_axle);
  torso.addChild(&head, linkTorsoHead, linkHeadTorso);
  torso.addChild(&leftLeg, linkTorsoLeftLeg, linkLeftLegTorso);
  torso.addChild(&rightLeg, linkTorsoRightLeg, linkRightLegTorso);

  axle.updateCentroid({.0, .0, .0});
  axle.rotate(-M_PI/2,0,0);
}

void R2D2::rotateHand(double left, double right)
{}

void R2D2::rotateArm(glm::vec3 left, glm::vec3 right)
{}

void R2D2::bendFront()
{
  if(bendAngle < M_PI/6) {
    bendAngle += kdbendAngle;
    leftLeg.rotate(kdbendAngle, 0, 0);
    rightLeg.rotate(kdbendAngle, 0, 0);
    torso.rotate(-kdbendAngle, 0, 0);
  }
}

void R2D2::bendBack()
{
  if(bendAngle > -M_PI/6) {
    bendAngle -= kdbendAngle;
    leftLeg.rotate(-kdbendAngle, 0, 0);
    rightLeg.rotate(-kdbendAngle, 0, 0);
    torso.rotate(kdbendAngle, 0, 0);
  }
}

void R2D2::walk()
{}

void R2D2::translate(glm::vec3 del)
{
    axle.translate(del[0],del[1],del[2]);
}

void R2D2::draw()
{
    torso.draw();
}

