/*
 *Assignment 4
 *@author Anshuman Kumar
 */

#include <chrono>
#include <thread>
#include "env.hpp"

GLuint shaderProgram;

Env * currentObject;
Object * currentObject2;
Assembly* robo;

void initBufferGL()
{
    std::string vertex_shader_file("../shaders/assign3_vshader.glsl");
    std::string fragment_shader_file("../shaders/assign3_fshader.glsl");

    std::vector<GLuint> shaderList;
    shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
    shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

    shaderProgram = csX75::CreateProgramGL(shaderList);
    glUseProgram( shaderProgram );
    
}

void renderGL()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // currentObject->draw();

}
int main(int argc, char** argv)
{
    std::cout << "Assignment1\n";
    if (!glfwInit())
    {
        std::cerr << "Unable to start GLFW\n";
        return 1;
    }
    
    GLFWwindow* window = glfwCreateWindow(640, 640, "OpenGL Assignment4", NULL, NULL);

    glfwSetErrorCallback(myglf::error_callback);

    if(! window)
    {
        std::cerr <<"ERROR:could not open window\n";
        glfwTerminate ();
        return 1;
    }
    glfwMakeContextCurrent (window);
    glewExperimental = GL_TRUE;
    glewInit  ();
    const GLubyte* renderer = glGetString (GL_RENDERER);
    const GLubyte* version = glGetString (GL_VERSION);
    std::cout << "Renderer: " << renderer <<"\n";
    std::cout << "GL Version: " << version <<"\n";
    glfwSetKeyCallback(window, myglf::key_callback);
    glfwSetMouseButtonCallback(window, myglf::mouse_button_callback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetFramebufferSizeCallback(window, myglf::framebuffer_size_callback);
    myglf::initGL();
    initBufferGL();
    
    double target_frame_rate = 30.0;
    double frame_time = 1.0 / target_frame_rate;
    double frame_start, draw_time;
    int sleep_time_ms;
    
    Env env(1);
    currentObject = &env;
    while(!glfwWindowShouldClose(window))
    {
      frame_start = glfwGetTime();

      renderGL();
      env.draw();
      glfwPollEvents();

      draw_time = glfwGetTime() - frame_start;

      sleep_time_ms = int(1000.0*(frame_time - draw_time));
      if( sleep_time_ms > 0.0 )
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time_ms));
      }

      glfwSwapBuffers(window);

    }
    glfwTerminate();
    return 0;
}

