#include <iostream>
#include <fstream>
#include "utils.hpp"

using namespace std;
using namespace glm;

vec3 robo_color = {1,0.8431,0};

void createArm()
{
  string filename = "../models/humanoid_arm.raw";

  vec3 center1 = {0,0,0};
  vec3 center2 = {0,0,0.4};
  vec3 center3 = {0,0,0.1};

  PointV pointV = shapes::frustum(center2,center1,0.1,0.1,robo_color,robo_color,robo_color);
  appendV(pointV, shapes::sphere(center3,0.141,robo_color));
  appendV(pointV, shapes::hemisphere(center2,0.10,robo_color,robo_color));
  
  fileStoreV(filename,pointV);
}

void createHand()
{
  string filename = "../models/humanoid_hand.raw";

  vec3 center1 = {0,0,0};
  vec3 center2 = {0,0,0.4};

  PointV pointV = shapes::frustum(center2,center1,0.08,0.1,robo_color,robo_color,robo_color);
  appendV(pointV, shapes::hemisphere(center2,0.08,robo_color,robo_color));

  fileStoreV(filename,pointV);
}

void createBody()
{
  string filename = "../models/humanoid_body.raw";
  vec3 center1 = {0,0,0};
  vec3 center2 = {0,0,0.8};

  PointV pointV = shapes::frustum(center2,center1,0.3,0.3,robo_color,robo_color,robo_color);
  appendV(pointV, shapes::hemisphere(center2,0.3,robo_color,robo_color));

  fileStoreV(filename,pointV);
}

void createTorsal()
{
  string filename = "../models/humanoid_torsal.raw";

  vec3 center1 = {0,0,0};
  vec3 center2 = {0,0,0.3};

  PointV pointV = shapes::frustum(center2,center1,0.3,0.3,robo_color,robo_color,robo_color);
  fileStoreV(filename,pointV);
}

void createNeck()
{
  string filename = "../models/humanoid_neck.raw";
  PointV pointV;
  vec3 center1 = {0,0,0};
  vec3 center2 = {0,0,0.1};
  pointV = shapes::frustum(center2,center1,0.15,0.15,robo_color,robo_color,robo_color);
  fileStoreV(filename,pointV);
}

void createThigh()
{
  string filename = "../models/humanoid_thigh.raw";
  vec3 center1 = {0,0,0};
  vec3 center2 = {0,0,0.6};

  PointV pointV = shapes::frustum(center2,center1,0.12,0.15,robo_color,robo_color,robo_color);
  PointV tempV  = shapes::hemisphere(center1,0.15,robo_color,robo_color);
  move::rotate(tempV,M_PI,0,0);
  appendV(pointV, tempV);
  appendV(pointV, shapes::hemisphere(center2,0.12,robo_color,robo_color));

  fileStoreV(filename,pointV);
}

void createLeg()
{
  string filename = "../models/humanoid_leg.raw";
  vec3 center1 = {0,0,0};
  vec3 center2 = {0,0,0.6};
  PointV pointV = shapes::frustum(center2,center1,0.08,0.12,robo_color,robo_color,robo_color);
  fileStoreV(filename,pointV);
}

void createFist()
{
  string filename = "../models/humanoid_fist.raw";
  vec3 center = {0,0,0};
  PointV pointV = shapes::sphere(center,0.12,robo_color);;
  fileStoreV(filename,pointV); 
}

void createFoot()
{
  string filename = "../models/humanoid_foot.raw";
  vec3 center = {0,0,0};
  PointV pointV = shapes::cuboid(center,0.25,0.25,0.20,robo_color);
  fileStoreV(filename,pointV); 
}

void createHead()
{
  string filename = "../models/humanoid_head.raw";
  vec3 center = {0,0,0};
  PointV pointV = shapes::ellipsoid(center,0.25,0.25,0.3,robo_color);
  fileStoreV(filename,pointV); 
}

void createHumanoid()
{
  std ::cout << "Creating Humanoid parts \n";
  createArm();
  createBody();
  createHand();
  createHead();
  createNeck();
  createThigh();
  createLeg();
  createFist();
  createFoot();
  createTorsal();
  cout << "Human Robot parts ready :) \n";
  cout << "Integrate them to make complete robot \n \n";

}

void createSBody()
{
  string filename = "../models/roboS_body.raw";
  PointV pointV;
  vec3 center1 = {0,0,0};
  vec3 center2 = {0,0,0.8};
  pointV = shapes::frustum(center2,center1,0.4,0.4,robo_color,robo_color,robo_color);
  fileStoreV(filename,pointV);
}

void createSHead()
{
  string filename = "../models/roboS_head.raw";
  PointV pointV;
  vec3 center = {0,0,0};
  pointV = shapes::hemisphere(center,0.4,robo_color,robo_color);
  fileStoreV(filename,pointV);
}

void createSHand()
{
  string filename = "../models/humanoid_foot.raw";
  PointV pointV;
  vec3 center = {0,0,0};
  pointV = shapes::cuboid(center,0.20,0.10,0.8,robo_color);;
  fileStoreV(filename,pointV);

}

void createSLeg()
{
  string filename = "../models/humanoid_foot.raw";
  PointV pointV;
  vec3 center = {0,0,0};
  pointV = shapes::cuboid(center,0.25,0.25,0.20,robo_color);;
  fileStoreV(filename,pointV);
}

void createRoboS()
{
  cout << " Creating the Small Robo\n";
  createSHead();
  createSBody();
  createSHand();
  createSLeg();
  cout << ":( Evil is  coming\n";
}

int main()
{
  cout << "Model Creator\n";
  createHumanoid();
  createRoboS();
}
