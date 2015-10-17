#ifndef ENV_HPP
#define ENV_HPP

#include "object.hpp"
#include "humanoid.hpp"

extern Robo *robo;
class Env:public Object
{
    glm::vec3 cPos,cUp,cRot;
    int currentRobo = 0;
    std::vector<Robo*> roboArray;
    public:
    Object env;
    void draw()
    {
        for (auto obj:roboArray)
        {
            obj->draw();
        }
        env.draw();

    }
    void addObject()
    {
        std::cout << "HELL0\n";
        Humanoid *robo1 =new Humanoid;
        Humanoid *robo2 =new Humanoid;
        robo1->createHierarchy();
        robo2->createHierarchy();
        robo1->translate({0.0,0,1});
        robo2->translate({-0.5,0,1});
        roboArray.push_back(robo1);
        roboArray.push_back(robo2);
        glm::vec3 vec = {0,0,0};
        addChild(robo1->mainObj,vec,vec);
        addChild(robo2->mainObj,vec,vec);
        addChild(&env,vec,vec);
    }
    void swap()
    {
        currentRobo = (currentRobo +1 )%roboArray.size();
        robo = roboArray[currentRobo];
    }
   
    void createViewMat()
    {
        glm::mat4 projectionMat;
        glm::mat4 cRotationMat;
        glm::mat4 lookatMat;
        cRotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(cRot[0]), glm::vec3(1.0f,0.0f,0.0f));
        cRotationMat = glm::rotate(cRotationMat, glm::radians(cRot[1]), glm::vec3(0.0f,1.0f,0.0f));
        cRotationMat = glm::rotate(cRotationMat, glm::radians(cRot[2]), glm::vec3(0.0f,0.0f,1.0f));
        glm::vec4 c_pos = glm::vec4(cPos, 1.0)*cRotationMat;
        glm::vec4 c_up = glm::vec4(cUp, 1.0)*cRotationMat;
        lookatMat = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));
        projectionMat = glm::frustum(-1.0, 1.0, -1.0, 1.0, 0.5, 5.0);
        viewMat = projectionMat*lookatMat;
        updateViewMat(viewMat);
    }

    void initCam()
    {
        cPos = {0.0,0.0,1.0};
        cRot = {0,0,0};
        cUp = {0,1,0};
        createViewMat();
    }
 
    void translate(float delx , float dely ,float delz)
    {
        std::cout << "here Working\n";
        cPos[0] += 0.1 *delx;
        cPos[1] += 0.1 *dely;
        cPos[2] += delz;
        createViewMat();
    }
    void rotate(float delx, float dely, float delz)
    {
        std::cout << "here Working2\n";
        cRot[0] += 10*delx;
        cRot[1] += 10*dely;
        cRot[2] += 10*delz;
        createViewMat();
    }
    
    Env(int a)
    {
        addObject();
        swap();
        env.readfile("../models/test.raw");
        env.changeTexImage("../Images/texture.jpg");
        initCam();
    }

};
#endif
