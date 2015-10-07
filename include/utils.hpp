#ifndef UTILS_HPP
#define UTILS_CPP

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/rotate_vector.hpp"

struct Point
{
    double x;
    double y;
    double z;
    double cx; 
    double cy; 
    double cz; 
};
using PointV = std::vector<Point>;


void filestore(std::ofstream &fs, Point point );
void filestore(std::ofstream &fs, Point* point );
void filestore(std::ofstream & fs,double x,double y,double z,double cx,double cy, double cz);
void filestore(std::ofstream &fs,glm::vec4 v,double cx,double cy,double cz);

namespace shapes
{
    PointV circle(glm::vec3 center, double a, glm::vec3 color);
    PointV sphere(glm::vec3 center, double a, glm::vec3 color);
    PointV ellipsoid(glm::vec3 center, double a, double b, double c,
            glm::vec3 color);
    PointV partEllipsoid(glm::vec3 center, double a, double b,
            double c, glm::vec3 color,double factor);
    Point getPointEllipse(double a,double b,double c,double theta,
            double phi,glm::vec3 color);
    PointV ellipse(glm::vec3 center, double a,double b,
            glm::vec3 color);
    PointV hemisphere(glm::vec3 center, double a, glm::vec3 color,
            glm::vec3 colorbase);

    PointV cuboid (glm::vec3 center,double l, double b, double h,
            glm::vec3 color);
    PointV cylinder();
    PointV cone();
    PointV frustum(glm::vec3 b1Center, glm::vec3 b2Center,
            double radius1, double radius2, glm::vec3 color1,
            glm::vec3 color2,glm::vec3 color);

    PointV rectangle(glm::vec3 center, double l, double b,
            glm::vec3 color);
    Point getPointRect(glm::vec3  center, double l, double b,
            glm::vec3 color);

}

namespace move
{
    void rotate(PointV &pointArray, double angX, double angY,
            double angZ, glm::vec3 rPoint = {0,0,0});
    Point rotate(Point point, double angX, double angY, double angZ,
            glm::vec3 rPoint ={0,0,0});
    Point translate(Point point, double x,double y,double z);
}
#endif
