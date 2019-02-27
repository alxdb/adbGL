#include <adbGL.hpp>
#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdexcept>
#include <thread>

int main() {
  using namespace adbgl;
  // Config
  std::string title = "BasicTriangle";
  int width = 800, height = 600;
  // Res
  // clang-format off
  const std::vector<GLfloat> pos_vertices = {
      -1.0f, -1.0f, 0.0f, 1.0f,
       1.0f, -1.0f, 0.0f, 1.0f,
       0.0f,  1.0f, 0.0f, 1.0f
  };

  const std::vector<GLfloat> col_vertices = {
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 1.0f,
  };

  const std::vector<GLfloat> tex_vertices = {
      0.0f, 0.0f,
      1.0f, 0.0f,
      0.5f, 1.0f,
  };
  // clang-format on

  glm::mat4 projection = glm::perspective(glm::radians(35.0f), (float)width / (float)height, 0.1f, 100.0f);

  glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

  glm::mat4 model = glm::mat4(1.0f);

  // Setup
  Window window(width, height, title.c_str(), true);
  window.makeCurrent();

  Shader shader(read_whole_file("shaders/base.vs.glsl"), read_whole_file("shaders/base.fs.glsl"));

  shader.set_uniform(shader.uniforms.get("mvp.model"), model);
  shader.set_uniform(shader.uniforms.get("mvp.view"), view);
  shader.set_uniform(shader.uniforms.get("mvp.projection"), projection);

  VertexBuffer pos_vbo(pos_vertices, GL_STATIC_DRAW);
  VertexBuffer col_vbo(col_vertices, GL_STATIC_DRAW);
  VertexBuffer tex_vbo(tex_vertices, GL_STATIC_DRAW);

  Texture texture("resources/UV_Grid.jpg");

  VertexArray vao;
  vao.set_attribute_pointer(pos_vbo, shader.attributes.get("pos"), attribute_types::vec4_float);
  vao.set_attribute_pointer(col_vbo, shader.attributes.get("col"), attribute_types::vec4_float);
  vao.set_attribute_pointer(tex_vbo, shader.attributes.get("tex"), attribute_types::vec2_float);

  // Render
  vao.bind();
  texture.bind();
  shader.use();

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
