#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    YAML::Node node = YAML::LoadFile("humanoid.yaml");
    std::ofstream fout("humanoid.yaml");
    cout << node["robo"]["name"] << endl;
    YAML::Node part = node["robo"]["parts"];
    
    cout << node["robo"]["parts"][0]["linkPC"][0]<< endl;
    fout << node;
}

