import os

print("shader_to_header.h: Converting shader files into text constants in shaders.h header file")

if not os.path.exists("shaders.h"):
    with open("shaders.h", 'x') as shaders_h:
        pass

with open("shaders.h", 'w') as shaders_h:
    shaders_h.write("#ifndef SHADERS_H\n#define SHADERS_H\n")
    shader_dirs = os.listdir("./shaders")
    for directory in shader_dirs:
        shaders = os.listdir("./shaders/" + directory)
        for shader in shaders:
            name = shader.replace(".", "_")
            with open("./shaders/" + directory + '/' + shader, 'r') as shader_file:
                text = shader_file.read()
            raw_text = text.replace('\n', '\\n')
            shaders_h.write("const char* " + name + "_text = \"" + raw_text + "\";\n")
    shaders_h.write("#endif\n")
    shaders_h.truncate()
