#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc, char * argv[])
{
    if(!glfwInit())
    {
        std::fprintf(stderr, "ERROR, CANNOT INITIALIZE GLFW\n");
        return -1;
    }
    else
    {
        std::printf("GLFW initialized\n");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    GLFWwindow* window = glfwCreateWindow(800, 600, "SuperCraft", nullptr, nullptr);
    if(window == NULL)
    {
        std::fprintf(stderr, "ERROR, CANNOT CREATE GLFW WINDOW\n");
        glfwTerminate();
        return -1;
    }
    else
    {
        std::printf("GLFW window created\n");
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::fprintf(stderr, "ERROR, CANNOT INITIALIZE GLAD\n");
        glfwTerminate();
        return -1;
    }
    else
    {
        std::printf("GLAD initialized\n");
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    while(!glfwWindowShouldClose(window))
    {
        //Check inputs
    processInput(window);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    glfwTerminate();
    return 0;
}