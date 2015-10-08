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
}

void Humanoid::createHierarchy()
{
    glm::vec3 linkBodyLeftArm = {-0.3, 0, 0};
    glm::vec3 linkBodyRightArm = {0.3,0,0};
    glm::vec3 linkBodyHip;
    glm::vec3 linkBodyNeck;
    glm::vec3 linkLeftArmBody =  {0.1,0,0};
    glm::vec3 linkRightArmBody = {-0.1,0,0};
    glm::vec3 linkHipBody;
    glm::vec3 linkNeckBody;
    glm::vec3 linkNeckHead;
    glm::vec3 linkHeadNeck;
    glm::vec3 linkRightArmRightHand = { 0,0,0.5};
    glm::vec3 linkLeftArmLeftHand = {0,0,0.5};
    glm::vec3 linkLeftHandLeftArm;
    glm::vec3 linkRightHandRightArm;
    glm::vec3 linkRightHandRightFist;
    glm::vec3 linkLeftHandLeftFist;
    glm::vec3 linkRightFistRightHand;
    glm::vec3 linkLeftFistLeftHand;
    glm::vec3 linkHipLeftThigh;
    glm::vec3 linkHipRightThigh;
    glm::vec3 linkRightThighHip;
    glm::vec3 linkLeftThighHip;
    glm::vec3 linkRightThighRightLeg;
    glm::vec3 linkLeftThighLeftLeg;
    glm::vec3 linkLeftLegLeftThigh;
    glm::vec3 linkRightLegRightThigh;
    glm::vec3 linkLeftLegLeftFoot;
    glm::vec3 linkRightLegRightFoot;
    glm::vec3 linkLeftFootLeftLeg;
    glm::vec3 linkRightFootRightLeg;

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
}

void Humanoid::draw()
{
    body.draw();
}
