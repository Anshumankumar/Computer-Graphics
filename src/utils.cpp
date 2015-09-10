#include "utils.hpp"

void filestore(std::ofstream &fs,glm::vec4 v,float cx,float cy,float cz)
{
    filestore(fs,v[0],v[1],v[2],cx,cy,cz);
}
void filestore(std::ofstream & fs,float x,float y,float z,float cx,float cy, float cz)
{
    fs << x;
    fs <<",";
    fs << y;
    fs <<",";
    fs << z;
    fs <<",";
    fs << cx;
    fs <<",";
    fs << cy;
    fs <<",";
    fs << cz;
    fs <<std::endl;
}

