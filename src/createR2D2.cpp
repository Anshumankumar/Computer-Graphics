#include "utils.hpp"

using namespace std;
using namespace glm;

vec3 r2d2_color = {.7, 0.7, 0.7}; // off white

void createAxle() // root of hirerarchy
{
    string filename = "../models/r2d2_axle.raw";
    PointV pointV = shapes::cuboid(vec3(.0,.0,.0), .01, .01, .01, r2d2_color);
    fileStoreV(filename,pointV);
}

void createTorso()
{
    string filename = "../models/r2d2_torso.raw";
    vec3 center1 = {0, 0,   0};
    vec3 center2 = {0, 0, .05};
    vec3 center3 = {0, 0, .540};
    PointV pointV = shapes::frustum(center3, center2, .225, .225, r2d2_color, r2d2_color, r2d2_color); // cyclindrical body
    appendV(pointV, shapes::frustum(center2, center1, .225, .195, r2d2_color, r2d2_color, r2d2_color)); // lower frustrum
    fileStoreV(filename,pointV);
}

void createHead()
{
    string filename = "../models/r2d2_head.raw";
    vec3 center = {0,0,0};
    PointV pointV = shapes::hemisphere(center,.225,r2d2_color,r2d2_color);
    fileStoreV(filename,pointV);
}

void createLeg()
{
    string filename = "../models/r2d2_leg.raw";
    PointV pointV = shapes::cuboid(vec3(0,0,.000), .070, .200, .170, r2d2_color);
    appendV(pointV, shapes::cuboid(vec3(0,0,-.335), .070, .130, .500, r2d2_color));
    appendV(pointV, shapes::cuboid(vec3(0,0,-.635), .140, .220, .100, r2d2_color));
    fileStoreV(filename,pointV);
}

void createR2D2Parts()
{
    cout << " Creating parts for R2D2\n";
    createAxle();
    createTorso();
    createHead();
    createLeg();
}

int main()
{
    createR2D2Parts();
}
