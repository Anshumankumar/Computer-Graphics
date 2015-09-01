#ifndef SCENE_HPP
#define SCENE_HPP
#include "object.hpp"

class Scene
{
    Object* objectArray;
        
    public:
    Scene(int noOfObjects);
    void parseFile(string filename);

}
#endif
