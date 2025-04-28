cmake_minimum_required(VERSION 3.20.0)

project(orbit_sim)


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


add_executable(${PROJECT_NAME} ../glad.c main.cpp)
add_executable(shader_test ../glad.c shader.cpp)

link_directories(${CMAKE_SOURCE_DIR}/../../libraries/ )
target_link_libraries(${PROJECT_NAME} glfw3)
target_link_libraries(shader_test glfw3)

target_include_directories(${PROJECT_NAME} PRIVATE ../include/ )
target_include_directories(shader_test PRIVATE ../include/ )

find_package(PythonInterp REQUIRED)
find_package(Python REQUIRED)
