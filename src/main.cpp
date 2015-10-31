/*
 *Assignment 1
 *@author Anshuman Kumar
 */

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

GLFWwindow ** window2;
void renderGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    currentObject->draw();
    glfwPollEvents();
    glfwSwapBuffers(*window2);


}
int main(int argc, char** argv)
{
    std::cout << "Assignment 4\n";
    if (!glfwInit())
    {
        std::cerr << "Unable to start GLFW\n";
        return 1;
    }
    GLFWwindow* window = glfwCreateWindow  (640, 640,
            "OpenGL Assignment4", NULL , NULL);
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
    glfwSetFramebufferSizeCallback(window, 
            myglf::framebuffer_size_callback);
    myglf::initGL();
    initBufferGL();

    Env env(1);
    currentObject = &env;

    window2 = &window;
    while(!glfwWindowShouldClose(window))
    {

        renderGL();
    }
    glfwTerminate();
    return 0;
}

