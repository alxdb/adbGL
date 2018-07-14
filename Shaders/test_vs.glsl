#version 410

in vec4 position;
in mat4 test;
in vec4 color;

out vec4 _color;

void main() {
    gl_Position = test * position;
    _color = color;
}
