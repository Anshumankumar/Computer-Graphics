#ifndef UTILS_HPP
#define UTILS_CPP

#include <fstream>
#include <iostream>
#include "glm/vec4.hpp"

void filestore(std::ofstream & fs,float x,float y,float z,float cx,float cy, float cz);
void filestore(std::ofstream &fs,glm::vec4 v,float cx,float cy,float cz);
#endif
