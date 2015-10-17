#include <iostream>
#include <fstream>
#include "utils.hpp"

int main()
{
    PointV vecP;
    glm::vec3  vecb1 = {0,0,0};
    glm::vec3  vecb2 = {0,0,0.6};
    glm::vec3  vec2 = {1,1,1};
    glm::vec3  vecc = {0,1,0};
    std::string filename = "../models/test.raw";
    std::ofstream fs(filename);
    vecP = shapes::cuboid(vecb1,8.0,8.0,8.0,vec2);
    std::cout << "Test File \n";
    for (auto point:vecP)
    {
        filestore(fs,point);
    }
    return 0;
}
