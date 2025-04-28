#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_col;
layout (location = 2) in vec2 a_tex_coord;

out vec3 color;
out vec2 tex_coord;

void main()
{
    color = a_col;
    tex_coord = a_tex_coord;
    gl_Position = vec4(a_pos, 1.0);
}