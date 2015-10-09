#include "humanoid.hpp"

extern Object * currentObject;
Humanoid::Humanoid()
{
    currentObject = &body;
    body.readfile("humanoid_body.raw");
    leftArm.readfile("humanoid_arm.raw");
    rightArm.readfile("humanoid_arm.raw");
    rightHand.readfile("humanoid_hand.raw");
    leftHand.readfile("humanoid_hand.raw");
    neck.readfile("humanoid_neck.raw");
    head.readfile("humanoid_head.raw");
    leftFist.readfile("humanoid_fist.raw");
    rightFist.readfile("humanoid_fist.raw");
    hip.readfile("humanoid_hip.raw");
    leftThigh.readfile("humanoid_thigh.raw");
    rightThigh.readfile("humanoid_thigh.raw");
    leftLeg.readfile("humanoid_leg.raw");
    rightLeg.readfile("humanoid_leg.raw");
    rightFoot.readfile("humanoid_foot.raw");
    leftFoot.readfile("humanoid_foot.raw");
}



void Humanoid::createHierarchy()
{
    glm::vec3 linkBodyLeftArm = {-0.3, 0, 0};
    glm::vec3 linkBodyRightArm = {0.3,0,0};
    glm::vec3 linkBodyHip = {0,0,0.8};
    glm::vec3 linkBodyNeck = {0,0,0};
    glm::vec3 linkLeftArmBody =  {0.1,0,0};
    glm::vec3 linkRightArmBody = {-0.1,0,0};
    glm::vec3 linkHipBody;
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
    glm::vec3 linkHipLeftThigh= {0.15,0,0.3};
    glm::vec3 linkHipRightThigh ={-0.15,0,0.3};
    glm::vec3 linkRightThighHip;
    glm::vec3 linkLeftThighHip;
    glm::vec3 linkRightThighRightLeg ={0,0,0.6};
    glm::vec3 linkLeftThighLeftLeg= {0,0,0.6};
    glm::vec3 linkLeftLegLeftThigh;
    glm::vec3 linkRightLegRightThigh;
    glm::vec3 linkLeftLegLeftFoot = {0,0,0.6};
    glm::vec3 linkRightLegRightFoot ={0,0,0.6};
    glm::vec3 linkLeftFootLeftLeg={0,0,-0.10};
    glm::vec3 linkRightFootRightLeg={0,0,-0.10};

    body.addChild(&rightArm,linkBodyRightArm,linkRightArmBody);
    body.addChild(&leftArm,linkBodyLeftArm,linkLeftArmBody);
    body.addChild(&neck,linkBodyNeck,linkNeckBody);
    body.addChild(&hip,linkBodyHip,linkHipBody);
    leftArm.addChild(&leftHand,linkLeftArmLeftHand,linkLeftHandLeftArm);
    rightArm.addChild(&rightHand,linkRightArmRightHand,linkRightHandRightArm);
    leftHand.addChild(&leftFist,linkLeftHandLeftFist,linkLeftFistLeftHand);
    rightHand.addChild(&rightFist,linkRightHandRightFist,linkRightFistRightHand);
    hip.addChild(&leftThigh,linkHipLeftThigh,linkLeftThighHip);
    hip.addChild(&rightThigh,linkHipRightThigh,linkRightThighHip);
    leftThigh.addChild(&leftLeg,linkLeftThighLeftLeg,linkLeftLegLeftThigh);
    rightThigh.addChild(&rightLeg,linkRightThighRightLeg,linkRightLegRightThigh);
    leftLeg.addChild(&leftFoot,linkLeftLegLeftFoot,linkLeftFootLeftLeg);
    rightLeg.addChild(&rightFoot,linkRightLegRightFoot,linkRightFootRightLeg);
    neck.addChild(&head,linkNeckHead,linkHeadNeck);
    leftHand.rotate(M_PI/3,0.0,0.0);
    body.resize(0.5,0.5,0.5);
}

void Humanoid::draw()
{
    body.draw();
    leftArm.rotate(M_PI/100,0.0,0.0);
}

