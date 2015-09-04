#include "gl_framework.hpp"
#include "object.hpp"

#define MODE_INSPECTION 1
#define MODE_MODELLING 2

int mode = MODE_MODELLING; 
extern Object* currentObject;

namespace myglf
{
    void initGL(void)
    {
        //Set framebuffer clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        //Set depth buffer furthest depth
        glClearDepth(1.0);
        //Set depth test to less-than
        glDepthFunc(GL_LESS);
        //Enable depth testing
        glEnable(GL_DEPTH_TEST);
        std::cout << "Current Mode is: MODELLING\n";
    }

    void error_callback(int error, const char* description)
    {
        std::cerr<<description<<std::endl;
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
        else if (key == GLFW_KEY_M  && action == GLFW_PRESS)
        {
            currentObject->reset();
            std::cout << "Current Mode: Modelling\n";
            mode = MODE_MODELLING;
        }
        else if (key == GLFW_KEY_I && action == GLFW_PRESS)
        {
            std::cout << "Current Mode: Inspection\n";
            mode = MODE_INSPECTION;
        }
        else if (key == GLFW_KEY_F && action == GLFW_PRESS)
        {
            currentObject->zIncrease();
        }
        else if (key == GLFW_KEY_B && action == GLFW_PRESS)
        {
            currentObject->zDecrease();
        }
        else if (key == GLFW_KEY_K && action == GLFW_PRESS)
        {
            currentObject->savefile();
        }
        else if (key == GLFW_KEY_L && action == GLFW_PRESS)
        {
            currentObject->readfile();
        }
        else if (key == GLFW_KEY_R && action == GLFW_PRESS)
            currentObject->reset();

        else if (mode == MODE_MODELLING)
            std::cout << "Current Mode: MODELLING\n";
        else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
            currentObject->rotate(0, -0.1,0);
        else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
            currentObject->rotate(0, +0.1,0);
        else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
            currentObject->rotate(-0.1,0.0,0);
        else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
            currentObject->rotate(0.1,0 ,0);
        else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
            currentObject->rotate(0,0,-0.1);
        else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
            currentObject->rotate(0,0,0.1);
        else if (key == GLFW_KEY_W && action == GLFW_PRESS)
            currentObject->translate(0, -0.05,0);
        else if (key == GLFW_KEY_S && action == GLFW_PRESS)
            currentObject->translate(0,0.05,0);
        else if (key == GLFW_KEY_A && action == GLFW_PRESS)
            currentObject->translate(-0.05,0.0,0);
        else if (key == GLFW_KEY_D && action == GLFW_PRESS)
            currentObject->translate(0.05,0 ,0);
        else if (key == GLFW_KEY_Z && action == GLFW_PRESS)
            currentObject->translate(0,0,-0.05);
        else if (key == GLFW_KEY_X && action == GLFW_PRESS)
            currentObject->translate(0,0,0.05);
    }

    void mouse_button_callback(GLFWwindow* window, int button, int action,
            int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            if (mode == MODE_INSPECTION) 
            {
                std::cout << "Current Mode: INSPECTION\n";
                return;
            }
            if (glfwGetKey (window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            {
                currentObject->pop();
            }
            else
            {
                double xpos,ypos;
                glfwGetCursorPos (window,&xpos,&ypos);
                currentObject->updateXY(window,xpos,ypos);
                currentObject->push();
            }
        }
    }
    void framebuffer_size_callback(GLFWwindow* window, int width,
            int height)
    { 
        glViewport(0, 0, width, height);
    }
}
