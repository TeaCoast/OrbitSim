#ifndef SHADER_CPP
#define SHADER_CPP

#ifndef MAIN_CPP
#define MAIN_CPP
#define SHADER_MAIN_CPP
#endif

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define FAILURE 1
#define SUCCESS 0

// helper functions --------------------------------------------------------------------------------------------------------------

std::string readFile(std::string filepath, int* error, std::string* error_log) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        *error_log += "Failed to open file: " + filepath + "\n\n";
        *error = FAILURE;
        return std::string("");
    }

    std::string file_content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    return file_content;
}

std::string _getShaderName(GLenum shader_type, int* error, std::string* error_log) {
    switch (shader_type)
    {
    case GL_VERTEX_SHADER:
        return std::string("vertex");
    case GL_FRAGMENT_SHADER:
        return std::string("fragment");
    }
    *error = FAILURE;
    *error_log += "unknown shader type given: " + std::to_string(shader_type) + "\n\n";
    return std::string("unknown type");
}

void _validateShaderCompilation(unsigned int shader, GLenum shader_type, int* error, std::string* error_log) {
    // determine if shader compilation succeeded
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success) {
        return;
    }
    
    // get length of info log
    int max_length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

    // get info log
    char* info_log = (char*)calloc(max_length, sizeof(char));
    glGetShaderInfoLog(shader, max_length, NULL, info_log);

    std::cout << "length: " << std::to_string(max_length) << std::endl;
    std::cout << info_log << std::endl;
    
    int error_shader_name = 0;
    std::string shader_name = _getShaderName(shader_type, &error_shader_name, error_log);
    *error = FAILURE;
    *error_log += shader_name + " shader compilation failed: \n" + info_log + "\n\n";

    free(info_log);
}

void _validateShaderLinking(unsigned int shader_program, int* error, std::string* error_log) {
    // determine if shader compilation succeeded
    int success;
    glGetShaderiv(shader_program, GL_LINK_STATUS, &success);
    if (success) {
        return;
    }

    // get length of info log
    int max_length;
    glGetShaderiv(shader_program, GL_INFO_LOG_LENGTH, &max_length);

    // get info log
    char* info_log = (char*)calloc(max_length, sizeof(char));
    glGetShaderInfoLog(shader_program, max_length, NULL, info_log);
    
    std::string custom_error_log = " shader linking failed: \n";
    *error = FAILURE;
    *error_log += custom_error_log + info_log + "\n\n";

    free(info_log);
}

// public functions --------------------------------------------------------------------------------------------------------------

unsigned int loadShader(const char* shader_content, GLenum shader_type, int* error, std::string* error_log) {
    //std::cout << "You did something wrong 1" << std::endl;
    unsigned int shader = glCreateShader(shader_type);
    //std::cout << "You did something wrong 2" << std::endl;
    glShaderSource(shader, 1, &shader_content, NULL);
    glCompileShader(shader);

    _validateShaderCompilation(shader, shader_type, error, error_log);

    return shader;
}

unsigned int loadShaderFile(std::string filepath, GLenum shader_type, int* error, std::string* error_log) {
    std::string shader_content = readFile(filepath, error, error_log);
    if (*error == FAILURE) {
        return 0;
    }
    unsigned int shader = loadShader(shader_content.c_str(), shader_type, error, error_log);
    return shader;
}

unsigned int linkShaders(unsigned int* shaders, int n, int* error, std::string* error_log) {
    unsigned int shader_program;
    shader_program = glCreateProgram();
    for (int i = 0; i < n; i++) {
        glAttachShader(shader_program, shaders[i]);
    }
    glLinkProgram(shader_program);

    _validateShaderLinking(shader_program, error, error_log);

    for (int i = 0; i < n; i++) {
        glDeleteShader(shaders[i]);
    }

    return shader_program;
}

unsigned int createShaderProgram(const char* vert_source, const char* frag_source, int* error, std::string* error_log) {
    unsigned int shaders[2];
    shaders[0] = loadShader(vert_source, GL_VERTEX_SHADER, error, error_log);
    shaders[1] = loadShader(frag_source, GL_FRAGMENT_SHADER, error, error_log);
    if (*error == FAILURE) {
        return 0;
    }
    
    unsigned int shader_program = linkShaders(shaders, 2, error, error_log);
    if (*error == FAILURE) {
        return 0;
    }

    return shader_program;
}

unsigned int createShaderProgramFromFiles(const char* vert_path, const char* frag_path, int* error, std::string* error_log) {
    unsigned int shaders[2];
    shaders[0] = loadShaderFile(vert_path, GL_VERTEX_SHADER, error, error_log);
    shaders[1] = loadShaderFile(frag_path, GL_FRAGMENT_SHADER, error, error_log);
    if (*error == FAILURE) {
        return 0;
    }
    
    unsigned int shader_program = linkShaders(shaders, 2, error, error_log);
    if (*error == FAILURE) {
        return 0;
    }

    return shader_program;
}

// testing -----------------------------------------------------------------------------------------------------------------

#include "shaders.h"

#ifdef SHADER_MAIN_CPP
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
    
    unsigned int shader_program = createShaderProgram(triangle_vert_text, triangle_frag_text, &error, &error_log);
    if (error == FAILURE) {
        std::cerr << "Error creating shader program for triangle shader: \n\n" << error_log << std::endl; 
        return error;
    }

    glDeleteProgram(shader_program);
    glfwTerminate();

    std::cout << "The program completed successfully!" << std::endl;

    return 0;
}
#endif

#endif