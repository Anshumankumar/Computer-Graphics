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
    std::cout << "YO\n";
    vecP = shapes::cuboid(vecb1,0.5,0.5,0.5,vec2);
    std::cout << "YO2\n";
    for (auto point:vecP)
    {
        filestore(fs,point);
    }
    return 0;
}
