#ifndef SHADERS_H
#define SHADERS_H
const char* triangle_frag_text = "#version 330 core\nout vec4 FragColor;\n  \nin vec4 color; \n\nvoid main()\n{\n    FragColor = vec4(color);\n}";
const char* triangle_vert_text = "#version 330 core\nlayout (location = 0) in vec3 a_pos;\nlayout (location = 1) in vec3 a_col;\n\nout vec4 color;\n\nvoid main()\n{\n    color = vec4(a_col, 1.0);\n    gl_Position = vec4(a_pos, 1.0);\n}";
#endif
