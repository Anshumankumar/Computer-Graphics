#include <iostream>
#include <fstream>
#include "utils.hpp"

int main()
{
    PointV vecP;
    glm::vec3  vec = {0,0,0};
    glm::vec3  vec2 = {1,1,0};
    std::string filename = "../models/test.raw";
    std::ofstream fs(filename);
    std::cout << "YO\n";
    vecP = circle(vec,1,vec2);
    for (point:vecP)
    {
        filestore(fs,point);
    }
    return 0;
}
