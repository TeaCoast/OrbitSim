#ifndef MODELS_CPP
#define MODELS_CPP

#include <iostream>
#include <cstdint>
#include <cmath>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.cpp"
#include "camera.cpp"
#include "shader_source.h"

class TriangleShader {
    public:
  
    #pragma pack(push, 0)
    typedef struct {
        glm::vec3 pos;
        glm::vec2 tex_coord;
    } Vertex;
    #pragma pack(pop)

    typedef struct {
        int model;
        int view;
        int proj;
        int textures[2];
    } UniformIDs;

    unsigned int shader_program;
    UniformIDs u_IDs;

    TriangleShader(int* error, std::string* error_log) {
        shader_program = createShaderProgram(triangle_vert_text, triangle_frag_text, error, error_log);
        if (*error != SUCCESS) {
            *error_log += "Error creating shader program for triangle shader ^^^ \n";
            return;
        }

        useProgram();
    
        u_IDs.model = glGetUniformLocation(shader_program, "u_model");
        u_IDs.view = glGetUniformLocation(shader_program, "u_view");
        u_IDs.proj = glGetUniformLocation(shader_program, "u_proj");

        for (int i = 0; i < 2; i++)
            u_IDs.textures[i] = glGetUniformLocation(shader_program, (std::string("u_texture") + std::to_string(i + 1)).c_str());
    }

    void useProgram() {
        glUseProgram(shader_program);
    }

    void bindAttribPointers() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }

    void setView(glm::mat4 matrix) {
        glUniformMatrix4fv(u_IDs.view, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    void setProj(glm::mat4 matrix) {
        glUniformMatrix4fv(u_IDs.proj, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    void setModel(glm::mat4 matrix) {
        glUniformMatrix4fv(u_IDs.model, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void bindTexture(int slot, unsigned int texture_id) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, texture_id);
    }

    void clean() {
        glDeleteProgram(shader_program);
    }
};

// prepare buffers
TriangleShader::Vertex vertices[] = {
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
    
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
    
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
    
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
    
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
    
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}}
};

class BoxWrapper {
    public:

    TriangleShader shader;
    std::vector<glm::vec3> cube_positions;

    unsigned int VBO, VAO;
    unsigned int textures[2];

    BoxWrapper(TriangleShader &shader, std::vector<glm::vec3> cube_positions, int* error, std::string* error_log) : shader(shader) {
        this->cube_positions = cube_positions;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
    
        glBindVertexArray(VAO);    
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        shader.bindAttribPointers();

        processImages(error, error_log);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);

        if (*error != SUCCESS) {
            *error_log += "Failed to initialize BoxWrapper class: ^^^";
        }
    }

    void processImages(int* error, std::string* error_log) {
        const char* texture_paths[2] = {"v0/assets/container.jpg", "v0/assets/awesomeface.png"};
        GLenum format[2] = {GL_RGB, GL_RGBA};
        glGenTextures(2, textures);
        int widths[2], heights[2], nr_channels[2];
        stbi_set_flip_vertically_on_load(true);
        for (int i = 0; i < 2; i++) {
            glBindTexture(GL_TEXTURE_2D, textures[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            unsigned char* data = stbi_load(texture_paths[i], &widths[i], &heights[i], &nr_channels[i], 0);
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widths[i], heights[i], 0, format[i], GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                *error_log += "Failed to load texture: ";
                *error_log += texture_paths[i];
                *error = FAILURE;
                return;
            }
            stbi_image_free(data);
    
            glUniform1i(shader.u_IDs.textures[i], i);
        }
    }

    void runFrame(Camera* camera, int width, int height) {
        shader.useProgram();
        shader.bindTexture(0, textures[0]);
        shader.bindTexture(1, textures[1]);
        glBindVertexArray(VAO);
        
        //u.model = glm::mat4(1.0f);
        //u.model = glm::rotate(u.model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        //camera_pos.x = sin(glfwGetTime()) * radius;
        //camera_pos.y = 0;
        //camera_pos.z = cos(glfwGetTime()) * radius;
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        glm::mat4 view = camera->getView();

        shader.setView(view);
        shader.setProj(proj);

        for(unsigned int i = 0; i < cube_positions.size(); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cube_positions[i]);
            float angle = 20.0f * i; 
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            if (i % 3 == 0) {
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            }
            shader.setModel(model);
        
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }

    void clean() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
};

#endif