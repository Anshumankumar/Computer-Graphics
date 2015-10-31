#include "humanoid.hpp"

extern Object * currentObject;

Humanoid::Humanoid(std::string yamlFile):Assembly(yamlFile)
{
    mainObj->rotate(M_PI,0,0);
    walkFlag = 0;
}
void Humanoid::rotateHand(double left, double right)
{
    if ((lHAngle+left) <= M_PI*2/3.0 && lHAngle+left > 0 )
    {
        lHAngle +=left;
        objectMap["leftHand"].rotate(left,0,0);
    }
    if (rHAngle+right < M_PI*2/3.0 && rHAngle+right > 0 )
    {
        rHAngle +=right;
        objectMap["rightHand"].rotate(right,0,0);
    }
}

void Humanoid::rotateArm(glm::vec3 left, glm::vec3 right)
{
    objectMap["leftArm"].rotate(left[0],0,0);
    objectMap["rightArm"].rotate(right[0],0,0);
    if (lAAngle - left[1] < 0 && lAAngle -left[1] > - 0.3*M_PI)
    {
        lAAngle -= left[1];
        objectMap["leftArm"].rotate(0.0,-left[1],0.0);
    }
    if (rAAngle + right[1] > 0 && rAAngle +right[1]  < 0.3*M_PI)
    {
        rAAngle += right[1];
        objectMap["rightArm"].rotate(0.0,right[1],0.0);
    }

}
void Humanoid::bendFront()
{
    if (bendAngle < M_PI/6)
    {
        bendAngle +=M_PI/36; 
        objectMap["body"].rotate(M_PI/36,0,0);
    }
}

void Humanoid::bendBack()
{
    if (bendAngle > -M_PI/6)
    {
        bendAngle -=M_PI/36; 
        objectMap["body"].rotate(-M_PI/36,0,0);
    }

}

void Humanoid::walk()
{
    mainObj->ltranslate(0,-0.05,0);
    switch(walkFlag)
    {
        case 1:
            walkFlag = 0;
            objectMap["leftThigh"].rotate(M_PI/30,0,0);
            objectMap["rightLeg"].rotate(M_PI/20,0,0);
            objectMap["rightThigh"].rotate(-M_PI/30,0,0);
            break;
        case 0:
            walkFlag = 1;
            objectMap["rightThigh"].rotate(M_PI/30,0,0);
            objectMap["rightLeg"].rotate(-M_PI/20,0,0);
            objectMap["leftThigh"].rotate(-M_PI/30,0,0);
            break;
    }
}
