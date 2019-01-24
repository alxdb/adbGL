#version 400

in vec4 vs_col;
in vec2 vs_tex;

out vec4 frag_col;

uniform sampler2D tex_samp;

void main() {
    frag_col = vs_col * texture(tex_samp, vs_tex);
}
