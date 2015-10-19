#include "humanoid.hpp"

extern Object * currentObject;
Humanoid::Humanoid():
    body("../textures/r2d2_torso.jpg"),
    leftHand("../textures/texture2.jpg"),
    rightHand("../textures/texture2.jpg"),
    leftLeg("../textures/texture2.jpg"),
    rightLeg("../textures/texture2.jpg"),
    neck("../textures/texture.jpg"),
    head("../textures/texture3.jpg"),
    torsal("../textures/texture.jpg"),
    leftThigh("../textures/texture.jpg"),
    rightThigh("../textures/texture.jpg"),
    leftArm("../textures/texture.jpg"),
    rightArm("../textures/texture.jpg"),
    rightFist("../textures/texture3.jpg"),
    leftFist("../textures/texture3.jpg"),
    leftFoot("../textures/texture3.jpg"),
    rightFoot("../textures/texture3.jpg")
{
    lHAngle = 0;
    rHAngle = 0;
    walkFlag = 0;
    currentObject = &torsal;
    body.readfile("humanoid_body.raw");
    leftArm.readfile("humanoid_arm.raw");
    rightArm.readfile("humanoid_arm.raw");
    rightHand.readfile("humanoid_hand.raw");
    leftHand.readfile("humanoid_hand.raw");
    neck.readfile("humanoid_neck.raw");
    head.readfile("humanoid_head.raw");
    leftFist.readfile("humanoid_fist.raw");
    rightFist.readfile("humanoid_fist.raw");
    torsal.readfile("humanoid_torsal.raw");
    leftThigh.readfile("humanoid_thigh.raw");
    rightThigh.readfile("humanoid_thigh.raw");
    leftLeg.readfile("humanoid_leg.raw");
    rightLeg.readfile("humanoid_leg.raw");
    rightFoot.readfile("humanoid_foot.raw");
    leftFoot.readfile("humanoid_foot.raw");
    mainObj = &torsal;
}



void Humanoid::createHierarchy()
{
    glm::vec3 linkBodyLeftArm = {-0.3, 0, 0};
    glm::vec3 linkBodyRightArm = {0.3,0,0};
    glm::vec3 linkBodyTorsal = {0,0,0.8};
    glm::vec3 linkBodyNeck = {0,0,0};
    glm::vec3 linkLeftArmBody =  {0.1,0,0};
    glm::vec3 linkRightArmBody = {-0.1,0,0};
    glm::vec3 linkTorsalBody = {0,0,0};
    glm::vec3 linkNeckBody={0,0,0.1};
    glm::vec3 linkNeckHead ={0,0,0};
    glm::vec3 linkHeadNeck ={0,0,0.2};
    glm::vec3 linkRightArmRightHand = { 0,0,0.4};
    glm::vec3 linkLeftArmLeftHand = {0,0,0.4};
    glm::vec3 linkLeftHandLeftArm;
    glm::vec3 linkRightHandRightArm;
    glm::vec3 linkRightHandRightFist = {0,0,0.4};
    glm::vec3 linkLeftHandLeftFist {0,0,0.4};
    glm::vec3 linkRightFistRightHand = {0,0,-0.15};
    glm::vec3 linkLeftFistLeftHand = {0,0,-0.15};
    glm::vec3 linkTorsalLeftThigh= {0.15,0,0.3};
    glm::vec3 linkTorsalRightThigh ={-0.15,0,0.3};
    glm::vec3 linkRightThighTorsal;
    glm::vec3 linkLeftThighTorsal;
    glm::vec3 linkRightThighRightLeg ={0,0,0.6};
    glm::vec3 linkLeftThighLeftLeg= {0,0,0.6};
    glm::vec3 linkLeftLegLeftThigh;
    glm::vec3 linkRightLegRightThigh;
    glm::vec3 linkLeftLegLeftFoot = {0,0,0.6};
    glm::vec3 linkRightLegRightFoot ={0,0,0.6};
    glm::vec3 linkLeftFootLeftLeg={0,0,-0.10};
    glm::vec3 linkRightFootRightLeg={0,0,-0.10};

    torsal.addChild(&body,linkTorsalBody,linkBodyTorsal);
    body.addChild(&rightArm,linkBodyRightArm,linkRightArmBody);
    body.addChild(&leftArm,linkBodyLeftArm,linkLeftArmBody);
    body.addChild(&neck,linkBodyNeck,linkNeckBody);
    leftArm.addChild(&leftHand,linkLeftArmLeftHand,linkLeftHandLeftArm);
    rightArm.addChild(&rightHand,linkRightArmRightHand,linkRightHandRightArm);
    leftHand.addChild(&leftFist,linkLeftHandLeftFist,linkLeftFistLeftHand);
    rightHand.addChild(&rightFist,linkRightHandRightFist,linkRightFistRightHand);
    torsal.addChild(&leftThigh,linkTorsalLeftThigh,linkLeftThighTorsal);
    torsal.addChild(&rightThigh,linkTorsalRightThigh,linkRightThighTorsal);
    leftThigh.addChild(&leftLeg,linkLeftThighLeftLeg,linkLeftLegLeftThigh);
    rightThigh.addChild(&rightLeg,linkRightThighRightLeg,linkRightLegRightThigh);
    leftLeg.addChild(&leftFoot,linkLeftLegLeftFoot,linkLeftFootLeftLeg);
    rightLeg.addChild(&rightFoot,linkRightLegRightFoot,linkRightFootRightLeg);
    neck.addChild(&head,linkNeckHead,linkHeadNeck);
    torsal.updateCentroid({0.0,0.0,0.0});
    torsal.rotate(M_PI/2,0,0);
}

void Humanoid::rotateHand(double left, double right)
{
    if ((lHAngle+left) <= M_PI*2/3.0 && lHAngle+left > 0 )
    {
        lHAngle +=left;
        leftHand.rotate(left,0,0);
    }
    if (rHAngle+right < M_PI*2/3.0 && rHAngle+right > 0 )
    {
        rHAngle +=right;
        rightHand.rotate(right,0,0);
    }
}

void Humanoid::rotateArm(glm::vec3 left, glm::vec3 right)
{
    leftArm.rotate(left[0],0,0);
    rightArm.rotate(right[0],0,0);
    if (lAAngle - left[1] < 0 && lAAngle -left[1] > - 0.3*M_PI)
    {
        lAAngle -= left[1];
        leftArm.rotate(0.0,-left[1],0.0);
    }
    if (rAAngle + right[1] > 0 && rAAngle +right[1]  < 0.3*M_PI)
    {
        rAAngle += right[1];
        rightArm.rotate(0.0,right[1],0.0);
    }

}
void Humanoid::bendFront()
{
    if (bendAngle < M_PI/6)
    {
        bendAngle +=M_PI/36; 
        body.rotate(M_PI/36,0,0);
        //        torsal.rotate(-M_PI/36,0,0);
    }
}

void Humanoid::bendBack()
{
    if (bendAngle > -M_PI/6)
    {
        bendAngle -=M_PI/36; 
        body.rotate(-M_PI/36,0,0);
        //       body.rotate(-M_PI/36,0,0);
    }

}

void Humanoid::walk()
{
    torsal.ltranslate(0,-0.05,0);
    switch(walkFlag)
    {
        case 1:
            walkFlag = 0;
            leftThigh.rotate(M_PI/30,0,0);
            rightLeg.rotate(M_PI/20,0,0);
            rightThigh.rotate(-M_PI/30,0,0);
            break;
        case 0:
            walkFlag = 1;
            rightThigh.rotate(M_PI/30,0,0);
            rightLeg.rotate(-M_PI/20,0,0);
            leftThigh.rotate(-M_PI/30,0,0);
            break;
    }
}
void Humanoid::translate(glm::vec3 del)
{
    torsal.translate(del[0],del[1],del[2]);      
}
void Humanoid::draw()
{
    torsal.draw();
}

