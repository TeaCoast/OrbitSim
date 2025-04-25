cmake_minimum_required(VERSION 3.20.0)

project(OrbitSim)

add_executable(${PROJECT_NAME} ../glad.c main.cpp)

add_library(GLFW3 STATIC IMPORTED)
set_target_properties(GLFW3 PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../../libraries/glfw3.lib )
target_link_libraries(${PROJECT_NAME} GLFW3)

add_library(GLM STATIC IMPORTED)
set_target_properties(GLM PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../../libraries/glm.lib )
target_link_libraries(${PROJECT_NAME} GLM)

target_include_directories(${PROJECT_NAME} PRIVATE ../include/ )