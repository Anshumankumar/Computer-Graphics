#include "utils.hpp"

void filestore(std::ofstream &fs, Point point )
{
    filestore(fs,point.x,point.y,point.z,point.cx,point.cy,point.cz,
            point.nx,point.ny,point.nz,point.tx,point.ty);
}
void filestore(std::ofstream &fs,glm::vec4 v,float cx,float cy,float cz)
{
    filestore(fs,v[0],v[1],v[2],cx,cy,cz);
}
void filestore(std::ofstream & fs,float x,float y,float z,float cx,float cy, float cz, float nx  ,float ny, float nz)
{
    fs << (float)x;
    fs <<",";
    fs << (float)y;
    fs <<",";
    fs << (float)z;
    fs <<",";
    fs << (float)cx;
    fs <<",";
    fs << (float)cy;
    fs <<",";
    fs << (float)cz;
    fs <<",";
    fs << (float)nx;
    fs <<",";
    fs << (float)ny;
    fs <<",";
    fs << (float)nz;
    fs <<",";
    fs <<tx;
    fs <<",";
    fs <<ty;
    fs <<std::endl;
}
namespace shapes
{
    PointV circle(glm::vec3 center, float a, glm::vec3 color)
    {
        return ellipse(center,a,a,color);
    }
    PointV ellipse(glm::vec3 center, float a,float b,
            glm::vec3 color)
    {
        int noOfPoints = a*360;
        PointV  pointArray;
        pointArray.resize(noOfPoints*3);
        float theta,theta2;
        Point point;
        point.cx = color[0];
        point.cy = color[1];
        point.cz = color[2];
        point.nx = 0;
        point.ny = 0;
        point.nz = 1;
        point.z = center.z;
        int k = 0;
        for (int i = 0;i < noOfPoints; i++)
        {
            theta = i*2*M_PI/noOfPoints;
            theta2 = (i+1)*2*M_PI/noOfPoints;
            point.x = center[0] + a*cos(theta);
            point.y = center[1] + b*sin(theta);
            pointArray[k++]= point;
            point.x = center[0] + a*cos(theta2);
            point.y = center[1] + b*sin(theta2);
            pointArray[k++]= point;
            point.x = center[0];
            point.y = center[1];
            pointArray[k++]= point;
        }   
        return pointArray;   
    }

    Point getPointEllipse(glm::vec3 center, float a,float b,float c,float theta,
            float phi,glm::vec3 color)
    {
        Point point;
        point.cx =  color[0];
        point.cy =  color[1];
        point.cz =  color[2];
        point.x = center[0] + a*cos(theta)*sin(phi);
        point.y = center[1] + b*sin(theta)*sin(phi);
        point.z = center[2] + c*cos(phi);
        point.nx = cos(theta)*sin(phi);
        point.ny = sin(theta)*sin(phi);
        point.nz = cos(phi);
        return point;   
    }
    PointV partEllipsoid(glm::vec3 center, float a, float b,
            float c, glm::vec3 color,float factor)
    {
        int noOfPoints1 = a*180;
        int noOfPoints2 = a*90;
        PointV  pointArray;
        pointArray.resize(noOfPoints1*noOfPoints2*6);
        float theta1,theta2;
        float phi1,phi2;
        int k = 0;
        for (int i = 0;i < noOfPoints1; i++)
        {
            theta1 = i*2*M_PI/noOfPoints1;
            theta2 = (i+1)*2*M_PI/noOfPoints1;
            for (int j = 0; j < noOfPoints2; j++)
            {
                phi1 = j*M_PI*factor/noOfPoints2;
                phi2 = (j+1)*M_PI*factor/noOfPoints2;
                pointArray[k++]= getPointEllipse(center,a,b,c,theta1,phi1,color);
                pointArray[k++]= getPointEllipse(center,a,b,c,theta1,phi2,color);
                pointArray[k++]= getPointEllipse(center,a,b,c,theta2,phi1,color);
                pointArray[k++]= getPointEllipse(center,a,b,c,theta1,phi2,color);
                pointArray[k++]= getPointEllipse(center,a,b,c,theta2,phi1,color);
                pointArray[k++]= getPointEllipse(center,a,b,c,theta2,phi2,color);
            } 
        }   
        return pointArray;   
    }

    PointV sphere(glm::vec3 center, float a, glm::vec3 color)
    {
        return ellipsoid(center,a,a,a,color);
    }

    PointV ellipsoid(glm::vec3 center, float a, float b, float c,
            glm::vec3 color)
    {
        return partEllipsoid(center,a,b,c,color,1);
    }
    
    PointV hemisphere(glm::vec3 center, float a, glm::vec3 color,
            glm::vec3 colorbase)
    {
        PointV pointArray;
        PointV::iterator it;
        PointV tempArray;
        pointArray = partEllipsoid(center,a,a,a,color,0.5);
        it = pointArray.end();
        tempArray = circle(center,a,colorbase);
        pointArray.insert(it,tempArray.begin(),tempArray.end());
        return pointArray;
    }
    PointV cuboid (glm::vec3 center,float l, float b, float h,
            glm::vec3 color)
    {
        PointV pointArray;
        PointV tempArray;
        PointV::iterator it;
        glm::vec3 centerR = {center[0],center[1],center[2]+h/2};
        pointArray = rectangle(centerR,l,b,color);
        
        centerR = {center[0],center[1],center[2]-h/2};
        tempArray = rectangle(centerR,l,b,color);
        move::rotate(tempArray,-M_PI,0,0,centerR);
        it = pointArray.begin();
        pointArray.insert(it,tempArray.begin(),tempArray.end());
       
        centerR = {center[0],center[1]+b/2,center[2]};
        tempArray = rectangle(centerR,l,h,color);
        move::rotate(tempArray,-M_PI/2,0,0,centerR);
        it = pointArray.begin();
        pointArray.insert(it,tempArray.begin(),tempArray.end());
        
        centerR = {center[0],center[1]-b/2,center[2]};
        tempArray = rectangle(centerR,l,h,color);
        move::rotate(tempArray,M_PI/2,0,0,centerR);
        it = pointArray.begin();
        pointArray.insert(it,tempArray.begin(),tempArray.end());
        
        centerR = {center[0]+l/2,center[1],center[2]};
        tempArray = rectangle(centerR,h,b,color);
        move::rotate(tempArray,0,M_PI/2,0,centerR);
        it = pointArray.begin();
        pointArray.insert(it,tempArray.begin(),tempArray.end());

        centerR = {center[0]-l/2,center[1],center[2]};
        tempArray = rectangle(centerR,h,b,color);
        move::rotate(tempArray,0,-M_PI/2,0,centerR);
        it = pointArray.begin();
        pointArray.insert(it,tempArray.begin(),tempArray.end());
        return pointArray;

    }

    Point getPointRect(glm::vec3  center, float l, float b,
           glm::vec3 color )
    {
        Point point;
        point.x = center[0]+l;
        point.y = center[1]+b;
        point.z = center[2];
        point.cx =  color[0];
        point.cy =  color[1];
        point.cz =  color[2];
        point.nx = 0;
        point.ny = 0;
        point.nz = 1;
        return point;

    }

    PointV rectangle(glm::vec3 center, float l, float b,
            glm::vec3 color)
    {
        PointV pointArray;
        pointArray.push_back(getPointRect(center,l/2,b/2,color));
        pointArray.push_back(getPointRect(center,l/2,-b/2,color));
        pointArray.push_back(getPointRect(center,-l/2,b/2,color));
        pointArray.push_back(getPointRect(center,l/2,-b/2,color));
        pointArray.push_back(getPointRect(center,-l/2,b/2,color));
        pointArray.push_back(getPointRect(center,-l/2,-b/2,color));
        return pointArray;
    }
    
    PointV frustum(glm::vec3 b1Center, glm::vec3 b2Center, float radius1,
            float radius2, glm::vec3 color1, glm::vec3 color2, 
            glm::vec3 colorS)
    { 
        PointV pointArray;
        PointV tempArray;
        PointV::iterator it;
        pointArray = circle(b1Center,radius1,color1);
        it = pointArray.begin();
        tempArray = circle(b2Center,radius2,color2);
        move::rotate(tempArray,M_PI,0,0,b2Center);
        pointArray.insert(it,tempArray.begin(),tempArray.end());
        int noOfPoints = radius1*360;
        int k = pointArray.size();
        pointArray.resize(pointArray.size()+noOfPoints*6);
        float theta,theta2;
        Point point;
        float angle = atan2(radius1-radius2,b1Center[2]-b2Center[2]);
        point.nz = sin(angle);
        point.cx = colorS[0];
        point.cy = colorS[1];
        point.cz = colorS[2];
        for (int i = 0;i < noOfPoints; i++)
        {
            theta = i*2*M_PI/noOfPoints;
            theta2 = (i+1)*2*M_PI/noOfPoints;

            point.x = b1Center[0] + radius1*cos(theta);
            point.y = b1Center[1] + radius1*sin(theta);
            point.nx = cos(angle)*cos(theta);
            point.ny = cos(angle)*sin(theta);
            point.z = b1Center[2];
            pointArray[k++]= point;
            point.x = b2Center[0] + radius2*cos(theta);
            point.y = b2Center[1] + radius2*sin(theta);
            point.z = b2Center[2];
            pointArray[k++]= point;
            point.x = b2Center[0] + radius2*cos(theta2);
            point.y = b2Center[1] + radius2*sin(theta2);
            point.nx = cos(angle)*cos(theta2);
            point.ny = cos(angle)*sin(theta2);

            pointArray[k++]= point;
            pointArray[k++]= point;
            point.x = b1Center[0] + radius1*cos(theta);
            point.y = b1Center[1] + radius1*sin(theta);
            point.z = b1Center[2];
            point.nx = cos(angle)*cos(theta);
            point.ny = cos(angle)*sin(theta);

            pointArray[k++]= point;
            point.x = b1Center[0] + radius1*cos(theta2);
            point.y = b1Center[1] + radius1*sin(theta2);
            point.nx = cos(angle)*cos(theta2);
            point.ny = cos(angle)*sin(theta2);

            pointArray[k++]= point;
        }
        return pointArray;   
    }
}
namespace move
{

    void rotate(PointV &pointArray, float angX, float angY,
            float angZ, glm::vec3 rPoint)
    {
        for (auto& point:pointArray)
        {
            point = rotate(point,angX,angY,angZ,rPoint);
        }
    }
    Point rotate(Point point, float angX, float angY, float angZ,
            glm::vec3 rPoint)
    {
        glm::vec3 vec,vecN;
        point = translate(point,-rPoint[0],-rPoint[1],-rPoint[2]);
        vec[0] = point.x;
        vec[1] = point.y;
        vec[2] = point.z;
        vecN[0] = point.nx;
        vecN[1] = point.ny;
        vecN[2] = point.nz;

        vec  = glm::rotateX(vec,(float)angX);
        vec  = glm::rotateY(vec,(float)angY);
        vec  = glm::rotateZ(vec,(float)angZ);
        vecN  = glm::rotateX(vecN,(float)angX);
        vecN  = glm::rotateY(vecN,(float)angY);
        vecN  = glm::rotateZ(vecN,(float)angZ);


        point.x = vec[0];
        point.y = vec[1];
        point.z = vec[2];
        point.nx = vecN[0];
        point.ny = vecN[1];
        point.nz = vecN[2];

        point = translate(point,rPoint[0],rPoint[1],rPoint[2]);
        return point;
    }

    Point translate(Point point, float x, float y, float z)
    {
        point.x = point.x + x;
        point.y = point.y + y;
        point.z = point.z + z;
        return point;
    }
}
