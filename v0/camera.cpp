#ifndef CAMERA_CPP
#define CAMERA_CPP

#ifndef MAIN_CPP
#define MAIN_CPP
#define CAMERA_MAIN_CPP
#endif

#include <iostream>
#include <cstdint>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// class -----------------------------------------------------------------------------------
class Camera {
    private:
        float yaw;
        float pitch;

        float lastX = 400;
        float lastY = 300;
    public:
        glm::vec3 pos;
        float lin_speed = 2.5f;
        float rot_speed = 90.0f;
        float sensitivity = 0.1f;
        glm::vec3 front;
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        Camera(glm::vec3 pos, float yaw = -90.0f, float pitch = 0.0f) {
            this->pos = pos;
            this->yaw = yaw;
            this->pitch = pitch;
        }

        glm::mat4 getView() {
            return glm::lookAt(pos, pos + front, up);
        }
    
        void processInput(GLFWwindow *window, float delta_time) {
            float lin_delta = lin_speed * delta_time;
            float rot_delta = rot_speed * delta_time;

            glm::vec3 direction;
            direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            direction.y = sin(glm::radians(pitch));
            direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            front = glm::normalize(direction);

            glm::vec3 xz_forward = glm::vec3(cos(glm::radians(yaw)), 0.f, sin(glm::radians(yaw)));
            
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                pos += lin_delta * xz_forward;
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                pos -= lin_delta * xz_forward;
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                pos -= glm::normalize(glm::cross(front, up)) * lin_delta;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                pos += glm::normalize(glm::cross(front, up)) * lin_delta;
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
                pos += lin_delta * up;
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                pos -= lin_delta * up;
            
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
                pitch += rot_delta;
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
                pitch -= rot_delta;
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
                yaw -= rot_delta;
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
                yaw += rot_delta;
    
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }
    
        void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos;
            lastX = xpos;
            lastY = ypos;
            
            xoffset *= sensitivity;
            yoffset *= sensitivity;
        
            yaw += xoffset;
            pitch += yoffset; 
            
            if(pitch > 89.0f)
              pitch = 89.0f;
            if(pitch < -89.0f)
              pitch = -89.0f;
            
        }
};


// test -------------------------------------------------------------------------------------
#ifdef CAMERA_MAIN_CPP
int main() {
    Camera camera = Camera(glm::vec3(0.0f, 1.0f, 3.0f));
    
    return 0;
}
#endif

#endif