#include <glad/glad.h>
#include <compileShader.hpp>

const char * vertexShaderSource{"#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0"};
const char * fragmentShaderSource{"#version 330 core\n"
    "out vec4 FragColor;\n"

    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0"};

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
    GLFWwindow* window{glfwCreateWindow(800, 600, "SuperCraft", nullptr, nullptr)};
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
    float vertices[]{-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    unsigned int shaderProgram{compileShader(vertexShaderSource, fragmentShaderSource)};
    glUseProgram(shaderProgram);
    while(!glfwWindowShouldClose(window))
    {
        //Check inputs
        processInput(window);
        //Rendering code
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //Check and call events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}