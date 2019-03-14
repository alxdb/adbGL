#include <adbGL.hpp>
#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdexcept>
#include <thread>

using Coord = std::array<float, 4>;
using TexCoord = std::array<float, 2>;

struct Vertex {
  Coord pos;
  Coord nrm;
  Coord col;
  TexCoord tex;
};

// clang-format off
constexpr float raw_cube_vertices[] = {
  // Pos               // Norm             // Tex
  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
   0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
   0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
   0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
  -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,

  -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
   0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
  -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
  -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

  -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
  -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
  -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

   0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
   0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
   0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
   0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
   0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
   0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
   0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
   0.5f, -0.5f,  0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

  -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
   0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
  -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f
};
// clang-format on

struct CubeVertices {
  std::array<Vertex, 36> vertices;
  constexpr CubeVertices(float size) : vertices() {
    for (size_t i = 0; i < 36; i++) {
      Vertex &vertex = vertices.at(i);
      const float *raw_vertex = raw_cube_vertices + (i * 8);
      vertex.pos = {raw_vertex[0] * size, raw_vertex[1] * size, raw_vertex[2] * size, 1.0f};
      vertex.nrm = {raw_vertex[3], raw_vertex[4], raw_vertex[5], 1.0f};
      vertex.tex = {raw_vertex[6], raw_vertex[7]};
      vertex.col = {0.1f, 0.1f, 0.1f, 1.0f};
    }
  }
};

namespace CubeAttributes {
  const adbgl::VertexArray::AttributePointer pos_ptr =
      adbgl::VertexArray::AttributePointer{4, GL_FLOAT, GL_FALSE, 14, 0};
  const adbgl::VertexArray::AttributePointer nrm_ptr =
      adbgl::VertexArray::AttributePointer{4, GL_FLOAT, GL_FALSE, 14, (const void *)4};
  const adbgl::VertexArray::AttributePointer col_ptr =
      adbgl::VertexArray::AttributePointer{4, GL_FLOAT, GL_FALSE, 14, (const void *)8};
  const adbgl::VertexArray::AttributePointer tex_ptr =
      adbgl::VertexArray::AttributePointer{2, GL_FLOAT, GL_FALSE, 14, (const void *)12};
};

int main() {
  using namespace adbgl;
  // Config
  std::string title = "BasicTriangle";
  int width = 800, height = 600;
  // Res
  CubeVertices cube_vertices(1.0f);

  glm::mat4 projection = glm::perspective(glm::radians(35.0f), (float)width / (float)height, 0.1f, 100.0f);

  glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

  glm::mat4 model = glm::mat4(1.0f);

  // Setup
  Window window(width, height, title.c_str(), true);
  window.makeCurrent();

  Shader shader(read_whole_file("shaders/diffuse.vs.glsl"), read_whole_file("shaders/diffuse.fs.glsl"));

  shader.set_uniform(shader.uniforms.get("mvp.model"), model);
  shader.set_uniform(shader.uniforms.get("mvp.view"), view);
  shader.set_uniform(shader.uniforms.get("mvp.projection"), projection);

  VertexBuffer vbo(cube_vertices.vertices, GL_STATIC_DRAW);
  for (int i = 0; i < 36 * 14; i++) {
    std::cout << ((float *) cube_vertices.vertices.data())[i] << std::endl;
  }

  VertexArray vao;
  checkGlError();
  vao.set_attribute_pointer(vbo, shader.attributes.get("pos"), CubeAttributes::pos_ptr);
  // vao.set_attribute_pointer(vbo, shader.attributes.get("nrm"), CubeAttributes::nrm_ptr);
  vao.set_attribute_pointer(vbo, shader.attributes.get("col"), CubeAttributes::col_ptr);
  // vao.set_attribute_pointer(vbo, shader.attributes.get("tex"), CubeAttributes::tex_ptr);

  // Render
  vao.bind();
  shader.use();
  glClearColor(0.1, 0.1, 0.1, 1.0);
  glEnable(GL_MULTISAMPLE);

  using std::chrono::system_clock;

  system_clock::time_point start = system_clock::now();
  std::chrono::milliseconds render_time_goal(16);

  while (!window.shouldClose()) {

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    view = glm::rotate(view, glm::radians(1.0f), glm::vec3(0.0, 1.0, 0.0));
    shader.set_uniform(shader.uniforms.get("mvp.view"), view);

    system_clock::time_point finished_render = system_clock::now();
    auto render_time = finished_render - start;
    if (render_time < render_time_goal) {
      std::this_thread::sleep_for(render_time_goal - render_time);
      // std::cout << "slept for: " << (render_time_goal - render_time).count() << "ns" << std::endl;
    }

    window.update();
    start = system_clock::now();
  }

  return 0;
}
