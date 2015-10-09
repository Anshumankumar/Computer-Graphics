#include <iostream>
#include "utils.hpp"
#include <fstream>

void fileStoreV(std::string filename,PointV pointV)
{
    std::ofstream fs(filename);
     for (auto point:pointV)
    {
        filestore(fs,point);
    }
    fs.close();
}
void createArm()
{
    std::string filename = "../models/humanoid_arm.raw";
    PointV pointV;
    PointV tempV;
    glm::vec3 center1 = {0,0,0};
    glm::vec3 center2 = {0,0,0.4};
    glm::vec3 center3 = {0,0,0.1};
    glm::vec3 color = {1,0.8431,0};
    pointV = shapes::frustum(center1,center2,0.1,0.1,color,color,
            color);
    tempV = shapes::sphere(center3,0.141,color);
    PointV::iterator it;
    it = pointV.begin();
    pointV.insert(it,tempV.begin(),tempV.end());
    tempV = shapes::hemisphere(center2,0.10,color,color);
    it = pointV.begin();
    pointV.insert(it,tempV.begin(),tempV.end());
    fileStoreV(filename,pointV);
}

void createHand()
{
    std::string filename = "../models/humanoid_hand.raw";
    PointV pointV;
    PointV tempV;
    glm::vec3 center1 = {0,0,0};
    glm::vec3 center2 = {0,0,0.4};
    glm::vec3 color = {1,0.8431,0};
    pointV = shapes::frustum(center1,center2,0.1,0.08,color,color,
            color);
    tempV = shapes::hemisphere(center2,0.08,color,color);
    PointV::iterator it;
    it = pointV.begin();
    pointV.insert(it,tempV.begin(),tempV.end());
    fileStoreV(filename,pointV);
}

void createBody()
{
    std::string filename = "../models/humanoid_body.raw";
    PointV pointV;
    glm::vec3 center1 = {0,0,0};
    glm::vec3 center2 = {0,0,0.8};
    glm::vec3 color = {1,0.8431,0};
    pointV = shapes::frustum(center1,center2,0.3,0.3,color,color,color);
    fileStoreV(filename,pointV);
}
void createHip()
{
    std::string filename = "../models/humanoid_hip.raw";
    PointV pointV;
    glm::vec3 center1 = {0,0,0};
    glm::vec3 center2 = {0,0,0.3};
    glm::vec3 color = {1,0.8431,0.2};
    pointV = shapes::frustum(center1,center2,0.3,0.3,color,color,color);
    fileStoreV(filename,pointV);
}

void createNeck()
{
    std::string filename = "../models/humanoid_neck.raw";
    PointV pointV;
    glm::vec3 center1 = {0,0,0};
    glm::vec3 center2 = {0,0,0.1};
    glm::vec3 color = {1,0.8431,0};
    pointV = shapes::frustum(center1,center2,0.15,0.15,color,color,color);
    fileStoreV(filename,pointV);
}

void createThigh()
{
    std::string filename = "../models/humanoid_thigh.raw";
    PointV pointV;
    glm::vec3 center1 = {0,0,0};
    glm::vec3 center2 = {0,0,0.6};
    glm::vec3 color = {1,0.8431,0};
    pointV = shapes::frustum(center1,center2,0.15,0.12,color,color,color);
    fileStoreV(filename,pointV);
}

void createLeg()
{
    std::string filename = "../models/humanoid_leg.raw";
    PointV pointV;
    glm::vec3 center1 = {0,0,0};
    glm::vec3 center2 = {0,0,0.6};
    glm::vec3 color = {1,0.8431,0};
    pointV = shapes::frustum(center1,center2,0.12,0.12,color,color,color);
    fileStoreV(filename,pointV);
}



void createFist()
{
    std::string filename = "../models/humanoid_fist.raw";
    PointV pointV;
    glm::vec3 center = {0,0,0};
    glm::vec3 color = {1,0.8431,0};
    pointV = shapes::sphere(center,0.12,color);;
    fileStoreV(filename,pointV); 
}

void createFoot()
{
    std::string filename = "../models/humanoid_foot.raw";
    PointV pointV;
    glm::vec3 center = {0,0,0};
    glm::vec3 color = {1,0.8431,0};
    pointV = shapes::cuboid(center,0.25,0.25,0.20,color);;
    fileStoreV(filename,pointV); 
}

void createHead()
{
    std::string filename = "../models/humanoid_head.raw";
    PointV pointV;
    glm::vec3 center = {0,0,0};
    glm::vec3 color = {1,0.8431,0};
    pointV = shapes::ellipsoid(center,0.25,0.25,0.3,color);;
    fileStoreV(filename,pointV); 
}





int main()
{

    std::cout << "Model Creator";
    createArm();
    createBody();
    createHand();
    createHead();
    createNeck();
    createThigh();
    createLeg();
    createFist();
    createFoot();
    createHip();
}
