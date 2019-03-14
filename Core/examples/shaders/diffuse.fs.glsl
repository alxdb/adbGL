#version 400

in vec4 vs_pos;
in vec4 vs_nrm;
in vec4 vs_col;
in vec2 vs_tex;

out vec4 frag_col;

uniform sampler2D tex_samp;
uniform vec4 light_pos;

// Assumes normalized normals
void main() {
  float diffuse = dot(vs_nrm, normalize(light_pos - vs_pos));
  // frag_col = diffuse * vs_col * texture(tex_samp, vs_tex);
  frag_col = vs_col;
}
