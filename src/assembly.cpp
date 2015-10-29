#include <assembly.hpp>

Assembly::Assembly(std::string yamlFile)
{
    YAML::Node node = YAML::LoadFile(yamlFile);
    name = node["assemb"]["name"].as<std::string>();
    YAML::Node parts = node["assemb"]["parts"];
    createHierarchy(parts);
}

void Assembly::createHierarchy(YAML::Node parts)
{
    glm::vec3 linkPC;
    glm::vec3 linkCP;
    std::string rawFile;
    std::string parent;
    std::string texture;
    std::string name;
    for(auto part:parts)
    {

        name = part["name"].as<std::string>();
        texture = part["texture"].as<std::string>();
        parent = part["parent"].as<std::string>();
        Object object(texture,name);
        objectMap[name] = object;
        objectMap[name].readfile(part["rFile"].as<std::string>());
        YAML::Node vec = part["linkPC"];
        linkPC = {vec[0].as<float>(),vec[1].as<float>(),vec[2].as<float>()};
        vec = part["linkCP"];
        linkCP = {vec[0].as<float>(),vec[1].as<float>(),vec[2].as<float>()};
        if (parent == "none")
        {
            mainObj = &objectMap[name];
        }
        else
        {
            if (objectMap.find(parent) != objectMap.end())
            {
                objectMap[parent].addChild(&objectMap[name],linkPC,linkCP);
                std::cout << object.name << "\n";
                std::cout << linkPC[0] << "\n";
            }
            else
            {
                std::cout << parent <<" doesn't exist\n";
            }
        }

    }
    mainObj->updateCentroid({0.0, 0.0, 0.0});
    mainObj->rotate(-M_PI/2,0,0);

}
