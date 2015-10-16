#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/rotate_vector.hpp"

struct Point
{
    float x;
    float y;
    float z;
    float w;
    float cx; 
    float cy; 
    float cz;
    float ca;
    float nx; 
    float ny; 
    float nz; 
    float tx;
    float ty;
};
using PointV = std::vector<Point>;

void fileread(std::ifstream & fs, Point &point);
void fileread(std::ifstream & fs, PointV &pointv);
void filestore(std::ofstream &fs, Point point );
void filestore(std::ofstream &fs, PointV pointv );
void filestore(std::ofstream & fs,float x,float y,float z,float cx,
        float cy, float cz,  float nx = 0, float ny =0 ,float nz =0,
        float tx = 0,float ty = 0, float w =1.0, float ca = 1.0);

namespace shapes
{
    PointV circle(glm::vec3 center, float a, glm::vec3 color);
    PointV sphere(glm::vec3 center, float a, glm::vec3 color);
    PointV ellipsoid(glm::vec3 center, float a, float b, float c,
            glm::vec3 color);
    PointV partEllipsoid(glm::vec3 center, float a, float b,
            float c, glm::vec3 color,float factor);
    Point getPointEllipse(float a,float b,float c,float theta,
            float phi,glm::vec3 color);
    PointV ellipse(glm::vec3 center, float a,float b,
            glm::vec3 color);
    PointV hemisphere(glm::vec3 center, float a, glm::vec3 color,
            glm::vec3 colorbase);

    PointV cuboid (glm::vec3 center,float l, float b, float h,
            glm::vec3 color);
    PointV cylinder();
    PointV cone();
    PointV frustum(glm::vec3 b1Center, glm::vec3 b2Center,
            float radius1, float radius2, glm::vec3 color1,
            glm::vec3 color2,glm::vec3 color);

    PointV rectangle(glm::vec3 center, float l, float b,
            glm::vec3 color);
    Point getPointRect(glm::vec3  center, float l, float b,
            glm::vec3 color);

}

namespace move
{
    void rotate(PointV &pointArray, float angX, float angY,
            float angZ, glm::vec3 rPoint = {0,0,0});
    Point rotate(Point point, float angX, float angY, float angZ,
            glm::vec3 rPoint ={0,0,0});
    Point translate(Point point, float x,float y,float z);
}
#endif
