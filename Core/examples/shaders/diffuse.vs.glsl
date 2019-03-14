#version 400

in vec4 pos;
in vec4 nrm;
in vec4 col;
in vec2 tex;

out vec4 vs_nrm;
out vec4 vs_pos;
out vec4 vs_col;
out vec2 vs_tex;

struct MVP {
  mat4 model;
  mat4 view;
  mat4 projection;
};

uniform MVP mvp;

void main() {
  gl_Position = mvp.projection * mvp.view * mvp.model * pos;
  vs_pos = mvp.model * pos;
  vs_nrm = nrm;
  vs_col = col;
  vs_tex = tex;
}
