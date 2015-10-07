#include <iostream>
#include "utils.hpp"
#include <fstream>
void createArm()
{
    std::string filename = "../models/humanoid_arm.raw";
    std::ofstream fs(filename);
    PointV pointV;
    PointV tempV;
    glm::vec3 center1 = {0,0,0};
    glm::vec3 center2 = {0,0,0.8};
    glm::vec3 color = {1,0.8431,0};
    pointV = shapes::frustum(center1,center2,0.2,0.2,color,color,
            color);
    tempV = shapes::hemisphere(center2,0.2,color,color);
    PointV::iterator it;
    it = pointV.begin();
    pointV.insert(it,tempV.begin(),tempV.end());
    for (auto point:pointV)
    {
        filestore(fs,point);
    }
}

void createBody()
{
    std::string filename = "../models/humanoid_body.raw";
    std::ofstream fs(filename);
    PointV pointV;
    PointV tempV;
    glm::vec3 center1 = {0,0,0};
    glm::vec3 center2 = {0,0,0.8};
    glm::vec3 color = {1,0.8431,0};
    pointV = shapes::frustum(center1,center2,0.4,0.4,color,color,
            color);
    for (auto point:pointV)
    {
        filestore(fs,point);
    }

}
int main()
{

    std::cout << "Model Creator";
    createArm();
    createBody();
}
