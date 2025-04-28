#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_col;

out vec4 color;

void main()
{
    color = vec4(a_col, 1.0);
    gl_Position = vec4(a_pos, 1.0);
}