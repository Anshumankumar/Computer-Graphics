#ifndef GL_FRAMEWORK_HPP
#define GL_FRAMEWORK_HPP

//Libraries for window mangement and keys
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace myglf
{
    void initGL(void);
    void error_callback(int error, const char* description);
    void key_callback(GLFWwindow* window, int key, int scancode,
            int action, int mods);
    void mouse_button_callback(GLFWwindow* window, int button, 
            int action, int mods);
    void framebuffer_size_callback(GLFWwindow* window, int width, 
            int height);
}


#endif 
