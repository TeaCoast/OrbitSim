#ifndef SHADERS_H
#define SHADERS_H
const char* triangle_frag_text = "#version 330 core\nout vec4 FragColor;\n  \nin vec3 color; \nin vec2 tex_coord;\n\nuniform sampler2D u_texture1;\nuniform sampler2D u_texture2;\n\nvoid main()\n{\n    FragColor = mix(texture(u_texture1, tex_coord), texture(u_texture2, tex_coord), 0.5) * vec4(color, 1.0);\n}";
const char* triangle_vert_text = "#version 330 core\nlayout (location = 0) in vec3 a_pos;\nlayout (location = 1) in vec3 a_col;\nlayout (location = 2) in vec2 a_tex_coord;\n\nout vec3 color;\nout vec2 tex_coord;\n\nvoid main()\n{\n    color = a_col;\n    tex_coord = a_tex_coord;\n    gl_Position = vec4(a_pos, 1.0);\n}";
#endif
