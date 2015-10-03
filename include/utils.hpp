#ifndef UTILS_HPP
#define UTILS_CPP

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"

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
PointV circle(glm::vec3 center, double radius, glm::vec3 color);
PointV ellispe();
PointV ellisoid();
PointV sphere();
PointV hemisphere();
PointV cuboid();
PointV cylinder();
PointV cone();
PointV frustum();
#endif
