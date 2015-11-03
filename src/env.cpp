#include <env.hpp>
#include <iostream>

extern int l1,l2,l3;

int bezierCameraToggle = 1;

#define NO_OF_FRAME 10.0
void renderGL();
int writeImage(int frameNo , unsigned char *data , int width, int height);

Env::Env(int a):spotLight("../textures/spotLight.jpg")
{
    addObject();
    robo = currentRobo->second;
    currentObject2 = currentRobo->second->mainObj;
    env.readfile("../models/cube.raw");
    env.changeTexImage("../textures/outside_texture.jpg");
    spotLight.readfile("../models/spotLight.raw");
    spotLight.startlight();
    bezierCamera.readfile("../models/bezierCamera.raw");

    initCam();

    numObjectsInEnv = roboArray.size() + 2; // one spotlight, one bezierCamera
    currObjIndx = 0;
    
    glLineWidth(3.5);
    glEnable(GL_LINE_SMOOTH);
    // glPointSize(4.5);

    bezierCurve.setDrawMode(GL_LINE_STRIP);
    bezierControlVertices.setDrawMode(GL_LINE_STRIP);
    // bezierCurve.setBufferUsage(GL_DYNAMIC_DRAW);
}

void Env::draw()
{
    for (auto &obj:roboArray)
    {
        obj.second->draw();
    }
    env.draw();
    spotLight.draw();

    if(bezierCameraToggle) {
      bezierCamera.draw();
      bezierCurve.draw();
      bezierControlVertices.draw();
    }
}

void Env::addObject()
{
    Humanoid *robo1 = new Humanoid("../models/humanoid.yaml");
    robo1->translate({-1.5,-1.4,2});
    R2D2 *robo2 = new R2D2("../models/r2d2.yaml");
    robo2->translate({1.5,-1.4,2});
    spotLight.translate(0,-3.4,0);
    spotLight.rotate(-M_PI/6,-M_PI/6,0);
    bezierCamera.translate(0, -1.5, 2);
    bezierCamera.resize(2.5, 2.5, 2.5);
    roboArray[robo1->name] = robo1;
    roboArray[robo2->name] = robo2;
    currentRobo = roboArray.begin();
    glm::vec3 vec = {0,0,0};
    addChild(robo1->mainObj,vec,vec);
    addChild(robo2->mainObj,vec,vec);
    addChild(&env,vec,vec);
    addChild(&spotLight,vec,vec);
    addChild(&bezierCamera,vec,vec);
    addChild(&bezierCurve,vec,vec);
    addChild(&bezierControlVertices,vec,vec);
}

void Env::swap()
{
    currObjIndx++;
    currObjIndx %= numObjectsInEnv;
    
    if (currObjIndx < roboArray.size()) {
      ++currentRobo;
      if (currentRobo == roboArray.end()) {
        currentRobo = roboArray.begin();
      }
      robo = currentRobo->second;
      currentObject2 = currentRobo->second->mainObj;
    }

    if (currObjIndx == roboArray.size()) {
      currentObject2 = &bezierCamera;
    }

    if (currObjIndx == roboArray.size() + 1) {
      currentObject2 = &spotLight;
    }
}

void Env::createViewMat()
{
    glm::mat4 projectionMat;
    glm::mat4 cRotationMat;
    glm::mat4 lookatMat;
    cRotationMat = glm::rotate(glm::mat4(1.0f), cRot[1], glm::vec3(0.0f,1.0f,0.0f));
    cRotationMat = glm::rotate(cRotationMat, cRot[0], glm::vec3(1.0f,0.0f,0.0f));
    cRotationMat = glm::rotate(cRotationMat, cRot[2], glm::vec3(0.0f,0.0f,1.0f));
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
    cPos[0] += delx;
    cPos[1] += dely;
    cPos[2] += delz;
    createViewMat();
}
void Env::rotate(float delx, float dely, float delz)
{
    cRot[0] += delx;
    cRot[1] += dely;
    cRot[2] += delz;
    //        cPos = {0,0,0};
    createViewMat();
}

void Env::moveNext()
{
    translate(cpdel[0],cpdel[1],cpdel[2]);
    rotate(crdel[0],crdel[1],crdel[2]);
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
        rnode["name"] = robo.second->name;
        for (auto &obj:robo.second->objectMap)
        {
            rnode["assembly"].push_back(obj.second.getNode());
        }
        node["light1"] = l1;
        node["light2"] = l2;
        node["light3"] = l3;
        YAML::Node camera;
        camera["x"] = cPos[0];
        camera["y"] = cPos[1];
        camera["z"] = cPos[2];
        camera["rx"] = cRot[0];
        camera["ry"] = cRot[1];
        camera["rz"] = cRot[2];
        node["camera"] = camera;
        node["frame"].push_back(rnode);
        node["keyFrameNo"] = frameNo;
    }
    mainNode["frames"].push_back(node);
    std::ofstream fout("../keyframes.yaml");
    fout << mainNode;
}

void Env::parseFrame(int recordFlag)
{
    unsigned char * iRGB;
    iRGB = new unsigned char [3 * 640 *640];
    glReadBuffer(GL_LEFT);
    glPixelStoref(GL_PACK_ALIGNMENT,2);
    int frameNo = 0;
    initCam();
    YAML::Node mainNode =  YAML::LoadFile("../keyframes.yaml");
    for (auto frame:mainNode["frames"])
    {
        l1 = frame["light1"].as<int>();
        l2 = frame["light2"].as<int>();
        l3 = frame["light3"].as<int>();
        cpdel[0] = -(cPos[0]-frame["camera"]["x"].as<float>())/NO_OF_FRAME; 
        cpdel[1] = -(cPos[1]-frame["camera"]["y"].as<float>())/NO_OF_FRAME; 
        cpdel[2] = -(cPos[2]-frame["camera"]["z"].as<float>())/NO_OF_FRAME; 
        crdel[0] = -(cRot[0]-frame["camera"]["rx"].as<float>())/NO_OF_FRAME; 
        crdel[1] = -(cRot[1]-frame["camera"]["ry"].as<float>())/NO_OF_FRAME; 
        crdel[2] = -(cRot[2]-frame["camera"]["rz"].as<float>())/NO_OF_FRAME; 
        for (auto assembly:frame["frame"])
        {
            Assembly * assem;
            assem = roboArray[assembly["name"].as<std::string>()];
            for (auto object:assembly["assembly"])
            {
                assem->objectMap[object["name"].
                    as<std::string>()].setNext(object,NO_OF_FRAME);
            }
        }
        for (int i =0;i<NO_OF_FRAME;i++)
        {
            frameNo++;
            glfwSetTime(0);
            moveNext();
            for (auto &robots:roboArray)
            {
                robots.second->moveNext();
            }

            renderGL();
            if (recordFlag ==1)
            {       
                glReadPixels(0, 0, 640, 640, GL_RGB, GL_UNSIGNED_BYTE, iRGB);
                writeImage(frameNo,iRGB,640,640);
            }
            while (glfwGetTime() < 1/NO_OF_FRAME){}
            // if (glfwGetTime() < 1/NO_OF_FRAME) { 
            //   std::this_thread::sleep_for(std::chrono::milliseconds( int(1000.0*(1/NO_OF_FRAME - glfwGetTime() )) ));
            // }
        } 
    }
}

void Env::addBezierPoint()

{
  Point point = bezierCamera.getPose();
  point.cx = 1;
  point.cy = 0;
  point.cz = 0;
  
  bezierControlVertices.push(point);
  computeBezierCurve();
}

void Env::removeLastBezierPoint()
{
  bezierControlVertices.pop();
  computeBezierCurve();
}

double nCk(double n, double k)
{
  double r = 1;
  for(double i=1; i<=k; i++) {
    r *= (n+1-i)/i;
  }
  return r;
}

std::vector<double> binomials(double n)
{
  std::vector<double> b;
  for(double k=0; k<=n; k++)
    b.push_back(nCk(n,k));
  return b;
}

void Env::computeBezierCurve()
{
  double kNPS = 3; // points per segment (2 consecutive control points)
  
  // compute Bernstein coefficients (Bernstein[i] = B[i]*Jn[i] as per notation in slides)
  std::vector<glm::vec3> Bernstein;
  PointV BCV = bezierControlVertices.getPointV();
  double n = double(BCV.size() - 1);
  std::vector<double> Jn = binomials(n);

  // std::cout<<"\n Jn = (";
  // for(int j=0; j<Jn.size(); j++) {
  //   std::cout<<Jn[j]<<", ";
  // }
  // std::cout<<")\n";

  glm::vec3 BCP;
  for(int i=0; i<=n; i++ ) {
    BCP = glm::vec3(BCV[i].x, BCV[i].y, BCV[i].z);
    Bernstein.push_back(BCP*float(Jn[i]));
  }
  
  // compute and add points to bezierCurve
  bezierCurve.removeAllPoints();
  Point curveVertex;
  int i;
  glm::vec3 P;
  for(double t=0; t<=1; t += 1./(n*kNPS)) {
    P = glm::vec3(0);
    for(i=0; i<=n; i++ ) {
      P += Bernstein[i]*float(std::pow(t,i)*std::pow(1-t, n-i));
    }
    curveVertex.x = P[0];
    curveVertex.y = P[1];
    curveVertex.z = P[2];
    curveVertex.w = 1;
    curveVertex.cx = 0;
    curveVertex.cy = 1;
    curveVertex.cz = 0;
    curveVertex.ca = 1;
    bezierCurve.push(curveVertex);
  }

}
