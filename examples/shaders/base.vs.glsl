#version 400

in vec4 pos;
in vec4 col;

out vec4 vs_col;

struct MVP {
    mat4 model;
    mat4 view;
    mat4 projection;
};

uniform MVP mvp;

void main() {
    gl_Position = mvp.projection * mvp.view * mvp.model * pos;
    vs_col = col;
}
