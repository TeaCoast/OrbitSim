#ifndef SHADERS_H
#define SHADERS_H
const char* triangle_frag_text = "#version 330 core\nout vec4 FragColor;\n  \n//uniform vec4 uColor; \n\nvoid main()\n{\n    FragColor = vec4(0.7, 0.7, 0.1, 1.0);\n}";
const char* triangle_vert_text = "#version 330 core\nlayout (location = 0) in vec3 aPos;\n\n// I am a change\n\nvoid main()\n{\n    gl_Position = vec4(aPos, 1.0);\n}";
#endif
