#version 410

in vec4 position;

out vec4 _color;

void main() {
    gl_Position = position;
    _color = vec4(1.0, 0.5, 0.1, 1.0);
}
