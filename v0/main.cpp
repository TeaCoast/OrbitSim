#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <cstdint>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.cpp"
#include "shaders.h"

#pragma pack(push, 0)
typedef struct {
    glm::vec3 pos;
    glm::vec3 col;
} TriangleVector;
#pragma pack(pop)

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    int error = 0;
    std::string error_log = "";

    // Prepare glad and glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        error_log += "Failed to create GLFW window";
        error = FAILURE;
        std::cerr << error_log << std::endl;
        glfwTerminate();
        return error;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        error_log += "Failed to initialize GLAD";
        error = FAILURE;
        std::cerr << error_log << std::endl;
        glfwTerminate();
        return error;
    }  

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

    // prepare shaders
    unsigned int shader_program = createShaderProgram(triangle_vert_text, triangle_frag_text, &error, &error_log);
    if (error == FAILURE) {
        std::cerr << "Error creating shader program for triangle shader: \n\n" << error_log << std::endl; 
        return error;
    }

    glUseProgram(shader_program);

    // prepare buffers
    TriangleVector vertices[] = {
        {{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},  // top right
        {{ 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},  // bottom right
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},  // bottom left
        {{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}   // top left 
    };
    
    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TriangleVector), (void*)offsetof(TriangleVector, pos));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TriangleVector), (void*)offsetof(TriangleVector, col));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    // run window
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader_program);

    glfwTerminate();
    return 0;
}

#endif