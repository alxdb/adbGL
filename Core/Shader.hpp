//
// Created by alxdb on 09/01/19.
//

#ifndef ADBGL_SHADER_HPP
#define ADBGL_SHADER_HPP

#include <GL/glew.h>
#include <map>
#include <string>

#include "Util.hpp"

namespace adbgl {

class Shader {
private:
  GLuint program;

  Shader(const Shader &) = delete;
  Shader &operator=(const Shader &) = delete;
  Shader(Shader &&);
  Shader &operator=(const Shader &&);

public:
  struct Input {
    GLuint index;
    GLint type;
  };

  struct Attributes : private std::map<std::string, Input> {
    using std::map<std::string, Input>::operator=;

    Input get(std::string name) {
      try {
        return at(name);
      } catch (std::exception e) {
        throw std::out_of_range("no attribute named " + name + " found");
      }
    }
  };

  using Uniforms = Attributes;

  Attributes attributes;
  Uniforms uniforms;

  Shader(const std::string &vertex_shader_file, const std::string &fragment_shader_file);

  void use() { GL_FUNC(glUseProgram(program);) }

  template <typename T> void set_uniform(Input, const T &);

  ~Shader() { GL_FUNC(glDeleteProgram(program);) }
};

} // namespace adbgl

#endif // ADBGL_SHADER_HPP
