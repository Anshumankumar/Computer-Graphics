/*
 *Assignment 1
 *@author Anshuman Kumar
 */


#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "object.hpp"
#include "scene.hpp"
GLuint shaderProgram;

//Scene scene1(3);
Object * currentObject;

void initBufferGL()
{
    std::string vertex_shader_file("../shaders/assign1_vshader.glsl");
    std::string fragment_shader_file("../shaders/assign1_fshader.glsl");

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
    GLFWwindow* window = glfwCreateWindow  (640, 640,
            "OpenGL Assignment1", NULL , NULL);
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
    Object object1;
    currentObject = &object1;
    Object object2;
    Object object3;
    Object object4;
    object2.readfile("humanoid_body.raw");
   // currentObject->readfile("test.raw");
    object3.readfile("humanoid_arm.raw");
    object4.readfile("humanoid_arm.raw");
    glm::vec3 vec1 = {0.0,0,0}; 
    glm::vec3 vec2 = {-0.1,0,0}; 
    glm::vec3 vec3 = {0.1,0,0}; 
    glm::vec3 vec4 = {0.3,0.0,0.0}; 
    glm::vec3 vec5 = {-0.3,0,0}; 
  //  currentObject->updateCentroid(vec4);
    currentObject->addChild(&object2,vec1,vec1);
    object2.addChild(&object4,vec4,vec2);
    object2.addChild(&object3,vec5,vec3);
    object4.rotate(0,M_PI/4,0);
    object3.rotate(0,-M_PI/4,0);
    //scene1.parseFile("myscene.scn");
    while(!glfwWindowShouldClose(window))
    {
        renderGL();
        currentObject->draw();
        glfwPollEvents();
        glfwSwapBuffers(window);
        
    }
    glfwTerminate();
    return 0;
}

