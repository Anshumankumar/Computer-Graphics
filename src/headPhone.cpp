#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
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

void surface (std::ofstream &fs, float startx,float endx,float radius,
        float cx =1,float cy = 1, float cz =1)

{
    float x,y,z;
    for (int i=0; i<361; i++)
    {
        z = radius*cos(i*M_PI/180);
        y = radius*sin(i*M_PI/180);
        x = startx;

        filestore(fs,x,y,z,cx,cy,cz);
        x = endx;
        filestore(fs,x,y,z,cx,cy,cz);
        z = radius*cos((i+1)*M_PI/180);
        y = radius*sin((i+1)*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,x,y,z,cx,cy,cz);
        x = startx;
        filestore(fs,x,y,z,cx,cy,cz);
        z = radius*cos((i)*M_PI/180);
        y = radius*sin((i)*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
    }

}
void circle (std::ofstream &fs, float x,float radius,
        float cx =1,float cy = 1, float cz =1)
{
    float y,z;
    for (int j=0; j<91  ; j++)
    {
        int i = 4*j;   
        z = radius*cos(i*M_PI/180);
        y = radius*sin(i*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
        z = radius*cos((i+4)*M_PI/180);
        y = radius*sin((i+4)*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
        z = 0;
        y = 0;
        filestore(fs,x,y,z,cx,cy,cz);
    }

}
int main()
{
    std::string filename = "../models/headPhone.raw";
    std::ofstream fs(filename);
    float x,y,z;
    float cx,cy,cz;
    float prevX,prevY,prevZ;
    float prevCx,prevCy,prevCz;
    float radius = 0.05;
    float height = 0.7;
    prevX = radius;prevY = -height; prevZ =0;
    prevCx= radius;prevCy = -radius; prevCz =0;
    if (!fs.is_open())
    {
        std::cout << "Unable to open file\n";
        fs.close();
        return 0;
    }
    radius = 0.5;
    for (int j=0; j<46; j++)
    {
        radius = 0.5;
        int i = 4*j;   
        x = radius*cos(i*M_PI/180);
        y = radius*sin(i*M_PI/180);
        z = 0.1;
        cx = 1;
        cy = 1;
        cz = 1;

        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i+4)*M_PI/180);
        y = radius*sin((i+4)*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
        radius = 0.48; 
        x = radius*cos((i+4)*M_PI/180);
        y = radius*sin((i+4)*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos(i*M_PI/180);
        y = radius*sin(i*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
        radius = 0.5; 
        x = radius*cos(i*M_PI/180);
        y = radius*sin(i*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
    }

    for (int j=0; j<46; j++)
    {
        radius = 0.5;
        int i = 4*j;   
        x = radius*cos(i*M_PI/180);
        y = radius*sin(i*M_PI/180);
        z = -0.1;
        cx = 1;
        cy = 1;
        cz = 1;

        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i+4)*M_PI/180);
        y = radius*sin((i+4)*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
        radius = 0.48; 
        x = radius*cos((i+4)*M_PI/180);
        y = radius*sin((i+4)*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos(i*M_PI/180);
        y = radius*sin(i*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
        radius = 0.5; 
        x = radius*cos(i*M_PI/180);
        y = radius*sin(i*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
    }
    radius = 0.5;
    for (int i=0; i<184; i++)
    {
        x = radius*cos(i*M_PI/180);
        y = radius*sin(i*M_PI/180);
        z = -0.1;
        cx = 0.8;
        cy = 0.8;
        cz = 0.8;

        filestore(fs,x,y,z,cx,cy,cz);
        z = 0.1;
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i+1)*M_PI/180);
        y = radius*sin((i+1)*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,x,y,z,cx,cy,cz);
        z = -0.1;
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i)*M_PI/180);
        y = radius*sin((i)*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
    }

    radius = 0.48;
    for (int i=0; i<184; i++)
    {
        x = radius*cos(i*M_PI/180);
        y = radius*sin(i*M_PI/180);
        z = -0.1;
        cx = 0.8;
        cy = 0.8;
        cz = 0.4;

        filestore(fs,x,y,z,cx,cy,cz);
        z = 0.1;
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i+1)*M_PI/180);
        y = radius*sin((i+1)*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,x,y,z,cx,cy,cz);
        z = -0.1;
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i)*M_PI/180);
        y = radius*sin((i)*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
    } 
    circle(fs,0.48,0.07,0,0,0.5);
    circle(fs,0.42,0.07,0,0,0.5);
    circle(fs,-0.48,0.07,0,0,0.5);
    circle(fs,-0.42,0.07,0,0,0.5);
    circle(fs,0.42,0.14,0,0,0.5);
    circle(fs,0.35,0.14,0.5,0.5,0.5);
    circle(fs,-0.42,0.14,0,0,0.5);
    circle(fs,-0.35,0.14,0.5,0.5,0.5);   
    surface(fs,0.48,0.42,0.07,0,0.3,0.3);
    surface(fs,-0.48,-0.42,0.07,0,0.3,0.3);
    surface(fs,-0.42,-0.35,0.14);
    surface(fs,0.42,0.35,0.14);
fs.close();
}
