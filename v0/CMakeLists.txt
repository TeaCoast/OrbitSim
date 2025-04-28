cmake_minimum_required(VERSION 3.20.0)

project(orbit_sim)

add_executable(${PROJECT_NAME} ../glad.c main.cpp)
add_executable(shader_test ../glad.c shader.cpp)

add_library(GLFW3 STATIC IMPORTED)
set_target_properties(GLFW3 PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../../libraries/glfw3.lib )
target_link_libraries(${PROJECT_NAME} GLFW3)
target_link_libraries(shader_test GLFW3)

add_library(GLM STATIC IMPORTED)
set_target_properties(GLM PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../../libraries/glm.lib )
target_link_libraries(${PROJECT_NAME} GLM)
target_link_libraries(shader_test GLM)

target_include_directories(${PROJECT_NAME} PRIVATE ../include/ )
target_include_directories(shader_test PRIVATE ../include/ )

find_package(PythonInterp REQUIRED)
find_package(Python REQUIRED)

add_custom_target(
    always_run_target ALL
)

add_custom_command(
    TARGET always_run_target
    PRE_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${PYTHON_EXECUTABLE} glsl_to_h.py
    VERBATIM
)