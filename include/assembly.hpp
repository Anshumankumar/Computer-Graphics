#ifndef ASSEMBLY_HPP
#define ASSEMBLY_HPP

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "object.hpp"
#include "scene.hpp"

class Assembly
{
    public:
    std::string name;
    std::map<std::string,Object> objectMap;
    Assembly(std::string yamlFile);
    ~Assembly();
    Object * mainObj; 
    virtual void createHierarchy(YAML::Node parts);
    virtual void draw();
    virtual void bendBack(){};
    virtual void bendFront(){};
    virtual void walk(){};
    virtual void rotateArm(glm::vec3 left,glm::vec3 right){};
    virtual  void rotateHand(double left,double right){};
    virtual  void translate(glm::vec3 del);

};

#endif
