#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader.h>

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
    else if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
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
        std::print("GLFW initialized\n");
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
        std::print("GLFW window created\n");
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
        std::print("GLAD initialized\n");
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    Shader shader("./res/shader.vs", "./res/shader.fs");
    float vertices[]
    {
    // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[]
    {
        0, 1, 3,
        1, 2, 3
    };
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char * data{stbi_load("res/container.jpg", &width, &height, &nrChannels, 0)};
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::print("Texture1 loaded\n");
    }
    else
    {
        std::fprintf(stderr, "Failed to load texture1\n");
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("res/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::print("Texture2 loaded\n");
    }
    else
    {
        std::print(stderr, "Failed to load texture2\n");
    }
    stbi_image_free(data);
    shader.use();
    glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);
    shader.setInt("texture2", 1);
    while(!glfwWindowShouldClose(window))
    {
        //Check inputs
        processInput(window);
        //Rendering code
        glClearColor(0.0f, 0.875f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //Draw triangle
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        shader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //Check and call events and swap buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}