#include <env.hpp>
void Env::draw()
{
    for (auto obj:roboArray)
    {
        obj->draw();
    }
    env.draw();
    spotLight.draw();
}
void Env::addObject()
{
    Humanoid *robo1;
    robo1 =new Humanoid("../models/humanoid.yaml");
    robo1->translate({-1.5,-1.4,2});
    R2D2 *robo2 =new R2D2("../models/r2d2.yaml");
    robo2->translate({1.5,-1.4,2});
    spotLight.translate(0,-3.4,0);
    spotLight.rotate(-M_PI/6,-M_PI/6,0);
    roboArray.push_back(robo1);
    roboArray.push_back(robo2);
    glm::vec3 vec = {0,0,0};
    addChild(robo1->mainObj,vec,vec);
    addChild(robo2->mainObj,vec,vec);
    addChild(&env,vec,vec);
    addChild(&spotLight,vec,vec);
}
void Env::swap()
{
    currentRobo = (currentRobo +1 )%roboArray.size();
    robo = roboArray[currentRobo];
    currentObject2 = roboArray[currentRobo]->mainObj;
}

void Env::createViewMat()
{
    glm::mat4 projectionMat;
    glm::mat4 cRotationMat;
    glm::mat4 lookatMat;
    cRotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(cRot[1]), glm::vec3(0.0f,1.0f,0.0f));
    cRotationMat = glm::rotate(cRotationMat, glm::radians(cRot[0]), glm::vec3(1.0f,0.0f,0.0f));
    cRotationMat = glm::rotate(cRotationMat, glm::radians(cRot[2]), glm::vec3(0.0f,0.0f,1.0f));
    glm::vec4 c_pos = glm::vec4(cPos, 1.0)*cRotationMat;
    glm::vec4 c_up = glm::vec4(cUp, 1.0);
    glm::vec4 c_view = {0,0,10,1};
    c_view = cRotationMat*c_view;
    lookatMat = glm::lookAt(glm::vec3(c_pos),glm::vec3(c_view),glm::vec3(c_up));
    projectionMat = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
    viewMat = projectionMat*lookatMat;
    updateViewMat(viewMat);
    viewMat = glm::mat4(glm::mat3(viewMat));
}

void Env::initCam()
{
    cPos = {0.0,0.0,0.0};
    cRot = {0,0,0};
    cUp = {0,1,0};
    createViewMat();
}

void Env::translate(float delx , float dely ,float delz)
{
    cPos[0] += 0.1 *delx;
    cPos[1] += 0.1 *dely;
    cPos[2] += delz;
    createViewMat();
}
void Env::rotate(float delx, float dely, float delz)
{
    cRot[0] += 50*delx;
    cRot[1] += 50*dely;
    cRot[2] += 50*delz;
    //        cPos = {0,0,0};
    createViewMat();
}

Env::Env(int a):spotLight("../textures/spotLight.jpg")
{
    addObject();
    swap();
    env.readfile("../models/cube.raw");
    env.changeTexImage("../textures/outside_texture.jpg");
    spotLight.readfile("../models/spotLight.raw");
    spotLight.startlight();
    initCam();
}

void Env::appendYaml(int frameNo)
{
    YAML::Node mainNode;
    if (frameNo != 0)
    {
        mainNode =  YAML::LoadFile("../keyframes.yaml");
    }
    YAML::Node node;
    for (auto &robo:roboArray)
    {
        YAML::Node rnode;
        rnode["name"] = robo->name;
        for (auto &obj:robo->objectMap)
        {
            rnode["objects"].push_back(obj.second.getNode());
        }
        node["frame"].push_back(rnode);
        node["keyFrameNo"] = frameNo;
    }
    mainNode["frames"].push_back(node);
    std::ofstream fout("../keyframes.yaml");
    fout << mainNode;
}

