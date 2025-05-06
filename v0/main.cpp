#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <cstdint>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "shader.cpp"
#include "camera.cpp"
#include "shader_source.h"
#include "models.cpp"

typedef struct {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
} TriangleUniforms;


int width = 800;
int height = 600;
void framebufferSizeCallback(GLFWwindow* window, int new_width, int new_height)
{
    width = new_width;
    height = new_height;
    glViewport(0, 0, width, height);
} 

// camera
float delta_time = 0.0f;
float last_frame = 0.0f;

Camera camera = Camera(glm::vec3(0.0f, 1.0f, 3.0f));
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    camera.processInput(window, delta_time);
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

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
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

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwMaximizeWindow(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSetCursorPosCallback(window, mouseCallback);
    
    // prepare shaders
    TriangleShader shader = TriangleShader(&error, &error_log);
    //unsigned int shader_program = createShaderProgram(triangle_vert_text, triangle_frag_text, &error, &error_log);
    if (error == FAILURE) {
        std::cerr << "Error creating shader program for triangle shader: \n\n" << error_log << std::endl; 
        return error;
    }

    glUseProgram(shader.shader_program);
    glEnable(GL_DEPTH_TEST);

    // prepare textures

    std::vector<glm::vec3> cube_positions = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    /*
    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    */

    BoxWrapper boxes = BoxWrapper(shader, cube_positions, &error, &error_log);
    if (error != SUCCESS) {
        std::cerr << error_log << std::endl;
        return error;
    }
    
    // run window
    while(!glfwWindowShouldClose(window))
    {
        
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        boxes.runFrame(&camera, width, height);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    boxes.clean();
    shader.clean();

    glfwTerminate();
    return 0;
}

#endif