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
    std::string filename = "bat.raw";
    std::ofstream fs(filename);
    float x,y,z;
    float cx,cy,cz;
    float prevX,prevY,prevZ;
    float prevCx,prevCy,prevCz;
    float radius = 0.05;
    float height = 0.6;
    prevX = radius;prevY = height; prevZ =0;
    prevCx= radius;prevCy = -radius; prevCz =0;
    if (!fs.is_open())
    {
        std::cout << "Unable to open file\n";
        fs.close();
        return 0;
    } 
    for (int j=0; j<91; j++)
    {
        int i = 4*j;   
        x = radius*cos(i*M_PI/180);
        z = radius*sin(i*M_PI/180);
        y = height;
        cx = 0.8;
        cy = 0.8;
        cz = 0.5;

        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,0,height,0,0.8,0.8,0.5);
        filestore(fs,prevX,prevY,prevZ,prevCx,prevCy,prevCz);
        prevX = x;
        prevY = y;
        prevZ = z;
        prevCx = cx;
        prevCy = cy;
        prevCz = cz;
    }
   for (int i=0; i<360; i++)
    {
        x = radius*cos(i*M_PI/180);
        z = radius*sin(i*M_PI/180);
        y = height;
        cx = pow((i/180.0-1.0),2);
        cy = 0.5;
        cz = 0;

        filestore(fs,x,y,z,cx,cy,cz);
        y = 0.2;
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i+1)*M_PI/180);
        z = radius*sin((i+1)*M_PI/180);
        cx = pow(((i+1)/180.0-1.0),2);
        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,x,y,z,cx,cy,cz);
        y = height;
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i)*M_PI/180);
        z = radius*sin((i)*M_PI/180);
        cx = pow(((i)/180.0-1.0),2);
        filestore(fs,x,y,z,cx,cy,cz);
    } 
      prevY =  0.2;
    for (int j=0; j<91; j++)
    {
        int i = 4*j;
        x = radius*cos(i*M_PI/180);
        z = radius*sin(i*M_PI/180);
        y = 0.2;
        cx = 0.8;
        cy = 0.8;
        cz = 0.4;

        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,0,0.2,0,0.8,0.8,0.4);
        filestore(fs,prevX,prevY,prevZ,prevCx,prevCy,prevCz);
        prevX = x;
        prevY = y;
        prevZ = z;
        prevCx = cx;
        prevCy = cy;
        prevCz = cz;
    }
   
   prevCx =  0.8;prevCy = 0.8;prevCz =0.5;
   filestore(fs,-0.15,0.2,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,0.15,0.2,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,0.15,-0.8,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,0.15,-0.8,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,-0.8,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,0.2,-0.05,prevCx,prevCy,prevCz);
  
  
   prevCx =  1;prevCy = 1;prevCz =0.5;
   filestore(fs,0.15,0.2,0.05,prevCx,prevCy,prevCz);
   filestore(fs,0.15,0.2,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,0.2,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,0.2,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,0.2,0.05,prevCx,prevCy,prevCz);
   filestore(fs,0.15,0.2,0.05,prevCx,prevCy,prevCz);

   prevCx =  1;prevCy = 1;prevCz =0.5;
   filestore(fs,0.15,0.2,0.05,prevCx,prevCy,prevCz);
   filestore(fs,0.15,0.2,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,0.15,-0.8,0.05,prevCx,prevCy,prevCz);
   filestore(fs,0.15,-0.8,0.05,prevCx,prevCy,prevCz);
   filestore(fs,0.15,-0.8,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,0.15,0.2,-0.05,prevCx,prevCy,prevCz);

   filestore(fs,-0.15,0.2,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,0.2,0.05,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,-0.8,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,-0.8,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,-0.8,0.05,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,0.2,0.05,prevCx,prevCy,prevCz);


   prevCx =  0.8;prevCy = 0.8;prevCz =0.4;
   filestore(fs,0.15,0.2,0.05,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,0.2,0.05,prevCx,prevCy,prevCz);
   filestore(fs,0,-0.1,0.06,prevCx,prevCy,prevCz);
   
   prevCx =  0.7;prevCy = 0.7;prevCz =0.4;
   filestore(fs,0.15,0.2,0.05,prevCx,prevCy,prevCz);
   filestore(fs,0,-0.1,0.06,prevCx,prevCy,prevCz);
   filestore(fs,0,-0.6,0.06,prevCx,prevCy,prevCz);
   filestore(fs,0,-0.6,0.06,prevCx,prevCy,prevCz);
   filestore(fs,0.15,0.2,0.05,prevCx,prevCy,prevCz);
   filestore(fs,0.15,-0.8,0.05,prevCx,prevCy,prevCz);

   prevCx =  1;prevCy = 1;prevCz =0.4;
   filestore(fs,-0.15,0.2,0.05,prevCx,prevCy,prevCz);
   filestore(fs,0,-0.1,0.06,prevCx,prevCy,prevCz);
   filestore(fs,0,-0.6,0.06,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,0.2,0.05,prevCx,prevCy,prevCz);
   filestore(fs,0,-0.6,0.06,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,-0.8,0.05,prevCx,prevCy,prevCz);
   
   prevCx =  1;prevCy = 1;prevCz =0.5;
   filestore(fs,0.15,-0.8,0.05,prevCx,prevCy,prevCz);
   filestore(fs,0.15,-0.8,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,-0.8,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,-0.8,-0.05,prevCx,prevCy,prevCz);
   filestore(fs,-0.15,-0.8,0.05,prevCx,prevCy,prevCz);
   filestore(fs,0.15,-0.8,0.05,prevCx,prevCy,prevCz);
   radius = 0.15; 
   prevX = radius;
   prevY = -0.6;
   prevZ = 0.05;
   for (int j=0; j<91; j++)
   {
       int i = 2*j;   
       x = radius*cos(i*M_PI/180);
       y = -0.8-radius*sin(i*M_PI/180);
       z =  0.05;
       cx = 1;
       cy = 1;
       cz = 0.4;

       filestore(fs,x,y,z,cx,cy,cz);
       filestore(fs,0,-0.6,0.05,0.8,0.8,0.5);
       filestore(fs,prevX,prevY,prevZ,prevCx,prevCy,prevCz);
       prevX = x;
       prevY = y;
       prevZ = z;
       prevCx = cx;
       prevCy = cy;
       prevCz = cz;
   }


    for (int j=0; j<91; j++)
   {
       int i = 2*j;   
       x = radius*cos(i*M_PI/180);
       y = -0.8-radius*sin(i*M_PI/180);
       z =  -0.05;
       cx = 0.8;
       cy = 0.8;
       cz = 0.5;

       filestore(fs,x,y,z,cx,cy,cz);
       filestore(fs,0,-0.8,-0.05,0.8,0.8,0.5);
       filestore(fs,prevX,prevY,prevZ,prevCx,prevCy,prevCz);
       prevX = x;
       prevY = y;
       prevZ = z;
       prevCx = cx;
       prevCy = cy;
       prevCz = cz;
   }

    for (int i=0; i<180; i++)
    {
        x = radius*cos(i*M_PI/180);
        y = -0.8-radius*sin(i*M_PI/180);
        z = -0.05;
        cx = 0.9;
        cy = 0.9;
        cz = 0.55;

        filestore(fs,x,y,z,cx,cy,cz);
        z = 0.05;
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i+1)*M_PI/180);
        y = -0.8-radius*sin((i+1)*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
        filestore(fs,x,y,z,cx,cy,cz);
        z = -0.05;
        filestore(fs,x,y,z,cx,cy,cz);
        x = radius*cos((i)*M_PI/180);
        y = -0.8-radius*sin(i*M_PI/180);
        filestore(fs,x,y,z,cx,cy,cz);
    } 

   fs.close();
}
