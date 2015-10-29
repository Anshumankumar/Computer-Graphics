#include "r2d2.hpp"

#define BEND_ANGLE M_PI/30
void R2D2::rotateHand(double left, double right) // rotates head: TODO: organize keyboard ctrls better
{
  if(left == 0) {
    objectMap["head"].rotate(0,0,  BEND_ANGLE);
  }
  if(right == 0) {
    objectMap["head"].rotate(0,0, -BEND_ANGLE);
  }
}


void R2D2::bendFront()
{
  if(bendAngle < M_PI/6) {
    bendAngle += BEND_ANGLE;
    objectMap["torso"].rotate(BEND_ANGLE, 0, 0);
  }
}

void R2D2::bendBack()
{
  if(bendAngle > -M_PI/6) {
    bendAngle -= BEND_ANGLE;
    objectMap["torso"].rotate(-BEND_ANGLE, 0, 0);
  }
}


