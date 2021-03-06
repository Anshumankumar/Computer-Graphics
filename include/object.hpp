#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <GL/glew.h>
#include <stdlib.h>
#include <deque>
#include <fstream>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "utils.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "SOIL.h"
#define MAX_SIZE_X 1.0f
#define MAX_SIZE_Y 1.0f
#define MAX_SIZE_Z 1.0f

#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

class Object
{
    int rotationFlag;
    std::string name;
    float xrot,yrot,zrot,xtln,ytln,ztln;
    float lxtln,lytln,lztln;
    float xscale,yscale,zscale; 
    float currentZ,currentX,currentY;
    glm::vec4 currentPosition;
    PointV  pointArray;
    glm::vec3 centroid;
    int triangleArraySize;
    GLuint vbo, vao, tex;
    GLuint uModelViewMatrix;
    GLuint normalMatrix;
    GLuint viewMatrix;
    std::vector<Object*> childArray;
    protected:
    glm::mat4 transMatrix;
    glm::mat4 normalMat;
    glm::mat4 viewMat;
    glm::mat4 outsideTransform;
    std::string texImage;
    public:
    Object(std::string texImg = "NOTHING");
    void loadImage();
    void changeTexImage(std::string tname);
    void givename(std::string);
    void updateXY(GLFWwindow *window, double X, double Y);
    void push();
    void pop();
    void zIncrease();
    void zDecrease();
    Point getPoint();
    void createTriangles();
    void initVboVao();
    void setVboVao();
    virtual void draw();
    void savefile(std::string tempname = "NOTHING");
    void readfile(std::string tempname = "NOTHING");
    virtual void rotate(float  delx, float dely, float delz);
    virtual void translate(float  delx, float dely, float delz);
    void ltranslate(float  delx, float dely, float delz);
    void resize(float sx,float sy,float sz);
    virtual void createMat();
    virtual void swap(){};
    void reset();
    void applyOutsideTransform(glm::mat4 t);
    void drawPointLines();
    virtual void changeState(int current){};
    void addChild(Object *child,glm::vec3 pP,glm::vec3 cP);
    void updateCentroid(glm::vec3 rPoint);
    void updateViewMat(glm::mat4 mat);
    void startlight();
    int lFlag;
    int texFlag;

};
void printMat(glm::mat4);
#endif
