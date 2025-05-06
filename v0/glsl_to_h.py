import os

output_name = "shader_source.h"
output_define_name = output_name.replace('.', '_').upper()

print(f"glsl_to_h.py: Converting shader files into text constants in {output_name} header file")

if not os.path.exists(output_name):
    with open(output_name, 'x') as output:
        pass

with open(output_name, 'w') as output:
    output.write(f"#ifndef {output_define_name}\n#define {output_define_name}\n")
    shader_dirs = os.listdir("./shaders")
    for directory in shader_dirs:
        shaders = os.listdir("./shaders/" + directory)
        for shader in shaders:
            name = shader.replace(".", "_")
            with open("./shaders/" + directory + '/' + shader, 'r') as shader_file:
                text = shader_file.read()
            raw_text = text.replace('\n', '\\n')
            output.write("const char* " + name + "_text = \"" + raw_text + "\";\n")
    output.write("#endif\n")
    output.truncate()