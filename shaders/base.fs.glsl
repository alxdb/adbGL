#version 400

in vec4 vs_col;

out vec4 frag_col;

void main() {
    frag_col = vs_col;
}
