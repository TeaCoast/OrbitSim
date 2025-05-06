#ifndef SHADER_SOURCE_H
#define SHADER_SOURCE_H
const char* triangle_frag_text = "#version 330 core\nout vec4 FragColor;\n\nin vec2 tex_coord;\n\nuniform sampler2D u_texture1;\nuniform sampler2D u_texture2;\n\nvoid main()\n{\n    FragColor = mix(texture(u_texture1, tex_coord), texture(u_texture2, tex_coord), 0.5);\n    // FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n}";
const char* triangle_vert_text = "#version 330 core\nlayout (location = 0) in vec3 a_pos;\nlayout (location = 1) in vec2 a_tex_coord;\n\nout vec2 tex_coord;\n\nuniform mat4 u_model;\nuniform mat4 u_view;\nuniform mat4 u_proj;\n\nvoid main()\n{\n    tex_coord = a_tex_coord;\n    gl_Position = u_proj * u_view * u_model * vec4(a_pos, 1.0);\n}";
#endif
