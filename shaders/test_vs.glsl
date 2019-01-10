#version 410

in vec4 pos;

out vec4 v_col;

void main() {
    gl_Position = pos;
    v_col = vec4(1.0, 0.5, 0.1, 1.0);
}
