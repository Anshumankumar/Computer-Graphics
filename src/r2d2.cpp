#include "r2d2.hpp"

extern Object *currentObject;

R2D2::R2D2()
{
  walkFlag = 0;
  currentObject = &torso;

  torso.readfile("r2d2_torso.raw");
  head.readfile("r2d2_head.raw");
  leftLeg.readfile("r2d2_leg.raw");
  rightLeg.readfile("r2d2_leg.raw");
}

void R2D2::createHierarchy()
{
  glm::vec3 linkTorsoHead = {0,0,.54};
  glm::vec3 linkHeadTorso = {0,0,0};
  glm::vec3 linkTorsoLeftLeg= {.227, 0, .420};
  glm::vec3 linkLeftLegTorso = {.50, 0, 0};
  glm::vec3 linkTorsoRightLeg= {-.227, 0, .420};
  glm::vec3 linkRightLegTorso = {-.50, 0, 0};

  torso.addChild(&head, linkTorsoHead, linkHeadTorso);
  torso.addChild(&leftLeg, linkTorsoLeftLeg, linkLeftLegTorso);
  torso.addChild(&rightLeg, linkTorsoRightLeg, linkRightLegTorso);
}

void R2D2::rotateHand(double left, double right)
{}

void R2D2::rotateArm(glm::vec3 left, glm::vec3 right)
{}

void R2D2::bendFront()
{}

void R2D2::bendBack()
{}

void R2D2::walk()
{}

void R2D2::draw()
{
    torso.draw();
}

