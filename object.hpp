#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <GL/glew.h>
#include <stdlib.h>
#include <deque>
#include <fstream>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define MAX_SIZE_X 1.0f
#define MAX_SIZE_Y 1.0f
#define MAX_SIZE_Z 1.0f

#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

class Object
{
    float currentZ,currentX,currentY;
    float xrot,yrot,zrot,xtln,ytln,ztln;
    glm::vec4 currentPosition;
    glm::vec4 *trianglePoint;
    glm::vec4 *triangleColor;
    glm::vec3 centroid;
    int triangleArraySize;
    std::deque<glm::vec4> pointStack;
    std::deque<glm::vec4> colorStack;
    GLuint vbo, vao;
    GLuint uModelViewMatrix;
    glm::mat4 transMatrix;
    public:
    Object();
    void updateXY(GLFWwindow *window, double X, double Y);
    void push();
    void pop();
    void zIncrease();
    void zDecrease();
    glm::vec4 getPoint();
    glm::vec4 getColor();
    void createTriangles();
    void createConTriangles();
    void initVboVao();
    void setVboVao();
    void draw();
    void savefile();
    void readfile();
    void parseline(std::string temp,glm::vec4 &cPoint,
                glm::vec4 &cColor);
    void rotate(float  delx, float dely, float delz);
    void translate(float  delx, float dely, float delz);
    void createMat();
    void reset();
};

#endif
