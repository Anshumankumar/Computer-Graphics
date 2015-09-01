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

int main()
{
    std::string filename = "pen.raw";
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
   /* for (int j=0; j<91; j++)
    {
        int i = 4*j;   
        x = radius*cos(i*M_PI/180);
        z = radius*sin(i*M_PI/180);
        y = -height;
        cx = pow((i/180.0-1.0),2);
        cy = 0;
        cz = 0.2;

        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,0,-(height+0.20),0,1,0,0.2);
        filestore(fs,prevX,prevY,prevZ,prevCx,prevCy,prevCz);
        prevX = x;
        prevY = y;
        prevZ = z;
        prevCx = cx;
        prevCy = cy;
        prevCz = cz;
    } */
   for (int i=0; i<360; i++)
    {
        x = radius*cos(i*M_PI/180);
        z = radius*sin(i*M_PI/180);
        y = -height;
        cx = pow((i/180.0-1.0),2);
        cy = 0.5;
        cz = 0;

        filestore(fs,x,y,z,cx,cy,cz);
        y = height;
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i+1)*M_PI/180);
        z = radius*sin((i+1)*M_PI/180);
        cx = pow(((i+1)/180.0-1.0),2);
        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,x,y,z,cx,cy,cz);
        y = -height;
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i)*M_PI/180);
        z = radius*sin((i)*M_PI/180);
        cx = pow(((i)/180.0-1.0),2);
        filestore(fs,x,y,z,cx,cy,cz);
    } 
    radius = radius+0.003; 
    for (int i=0; i<360; i++)
    {
        x = radius*cos(i*M_PI/180);
        z = radius*sin(i*M_PI/180);
        y =  -0.25;
        cx = pow((i/180.0-1.0),2);
        cy = 0;
        cz = 0.5;

        filestore(fs,x,y,z,cx,cy,cz);
        y = -0.68;
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i+1)*M_PI/180);
        z = radius*sin((i+1)*M_PI/180);
        cx = pow(((i+1)/180.0-1.0),2);
        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,x,y,z,cx,cy,cz);
        y = -0.25;
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i)*M_PI/180);
        z = radius*sin((i)*M_PI/180);
        cx = pow(((i)/180.0-1.0),2);
        filestore(fs,x,y,z,cx,cy,cz);
    } 
    
    for (int i=0; i<360; i++)
    {
        radius = 0.05;
        x = radius*cos(i*M_PI/180);
        z = radius*sin(i*M_PI/180);
        y =  -height;
        cx = pow((i/180.0-1.0),2);
        cy = 0.8;
        cz = 0.8;

        filestore(fs,x,y,z,cx,cy,cz);
        radius = 0.01;
        y = -(height+0.15);
        x = radius*cos(i*M_PI/180);
        z = radius*sin(i*M_PI/180);

        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i+1)*M_PI/180);
        z = radius*sin((i+1)*M_PI/180);
        cx = pow(((i+1)/180.0-1.0),2);
        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,x,y,z,cx,cy,cz);
        y = -height;
        radius = 0.05;
        x = radius*cos((i+1)*M_PI/180);
        z = radius*sin((i+1)*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i)*M_PI/180);
        z = radius*sin((i)*M_PI/180);
        cx = pow((i/180.0-1.0),2);
        filestore(fs,x,y,z,cx,cy,cz);
    } 
    
   prevY =  height;
    for (int j=0; j<91; j++)
    {
        int i = 4*j;
        x = radius*cos(i*M_PI/180);
        z = radius*sin(i*M_PI/180);
        y = height;
        cx = pow((i/180.0-1.0),2);
        cy = 0;
        cz = 0.2;

        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,0,height+0.03,0,1,0,0.2);
        filestore(fs,prevX,prevY,prevZ,prevCx,prevCy,prevCz);
        prevX = x;
        prevY = y;
        prevZ = z;
        prevCx = cx;
        prevCy = cy;
        prevCz = cz;
    }
    radius = 0.006; 
    for (int i=0; i<360; i++)
    {
        x = radius*cos(i*M_PI/180);
        z = radius*sin(i*M_PI/180);
        y =  -(height+0.015);
        cx = pow((i/180.0-1.0),2);
        cy = 0.5;
        cz = 0.5;

        filestore(fs,x,y,z,cx,cy,cz);
        y = -(height+0.20);
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i+1)*M_PI/180);
        z = radius*sin((i+1)*M_PI/180);
        cx = pow(((i+1)/180.0-1.0),2);
        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,x,y,z,cx,cy,cz);
        y =  -(height+0.015);
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i)*M_PI/180);
        z = radius*sin((i)*M_PI/180);
        cx = pow(((i)/180.0-1.0),2);
        filestore(fs,x,y,z,cx,cy,cz);
    } 
    prevY =  -(height+0.20);
    prevX =  radius;
    prevZ = 0;
    for (int j=0; j<91; j++)
    {
        int i = 4*j;
        x = radius*cos(i*M_PI/180);
        z = radius*sin(i*M_PI/180);
        y = -(height+0.20);
        cx = pow((i/180.0-1.0),2);
        cy = 0;
        cz = 1;

        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,0,-(height+0.21),0,1,0,0.2);
        filestore(fs,prevX,prevY,prevZ,prevCx,prevCy,prevCz);
        prevX = x;
        prevY = y;
        prevZ = z;
        prevCx = cx;
        prevCy = cy;
        prevCz = cz;
    }
  
    fs.close();
}
