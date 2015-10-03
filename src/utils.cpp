#include "utils.hpp"

void filestore(std::ofstream &fs, Point point )
{
    filestore(fs,point.x,point.y,point.z,point.cx,point.cy,point.cz);
}
void filestore(std::ofstream &fs,glm::vec4 v,double cx,double cy,double cz)
{
    filestore(fs,v[0],v[1],v[2],cx,cy,cz);
}
void filestore(std::ofstream & fs,double x,double y,double z,double cx,double cy, double cz)
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

PointV circle(glm::vec3 center, double radius, glm::vec3 color)
{
    int noOfPoints = radius*360;
    PointV  pointArray;
    pointArray.resize(noOfPoints*3);
    double thetha,thetha2;
    Point point;
    point.cx = color[0];
    point.cy = color[1];
    point.cz = color[2];
    point.z = center.z;
    int k = 0;
    for (int i = 0;i < noOfPoints; i++)
    {
        thetha = i*2*M_PI/noOfPoints;
        thetha2 = (i+1)*2*M_PI/noOfPoints;
        point.x = center[0] + radius*cos(thetha);
        point.y = center[1] + radius*sin(thetha);
        pointArray[k++]= point;
        point.x = center[0] + radius*cos(thetha2);
        point.y = center[1] + radius*sin(thetha2);
        pointArray[k++]= point;
        point.x = center[0];
        point.y = center[1];
        pointArray[k++]= point;
    }   
    return pointArray;   
}
