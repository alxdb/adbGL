#include "Shader.hpp"
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void checkShaderError(GLuint shader, GLenum pname);

void checkProgramError(GLuint shader);

namespace adbgl {

Shader::Shader(const std::string &vertex_shader, const std::string &fragment_shader) {
  { // Shader Compilation
    const char *vs_src = vertex_shader.c_str();
    const char *fs_src = fragment_shader.c_str();

    checkGlError();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_src, nullptr);
    glCompileShader(vs);
    checkShaderError(vs, GL_COMPILE_STATUS);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_src, nullptr);
    glCompileShader(fs);
    checkShaderError(fs, GL_COMPILE_STATUS);

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    checkProgramError(program);

    glDetachShader(program, vs);
    glDetachShader(program, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    checkGlError();
  }

  auto get_inputs = [&](GLenum program_interface) -> std::map<std::string, Input> {
    GLint n_inputs;
    std::map<std::string, Input> inputs;
    glGetProgramInterfaceiv(program, program_interface, GL_ACTIVE_RESOURCES, &n_inputs);
    for (GLuint input_id = 0; input_id < n_inputs; input_id++) {
      GLint params[2];
      GLenum props[] = {GL_NAME_LENGTH, GL_TYPE};
      glGetProgramResourceiv(program, program_interface, input_id, 2, props, 2, nullptr, params);

      char name_raw[params[0]];
      glGetProgramResourceName(program, program_interface, input_id, params[0], nullptr, name_raw);
      std::string name(name_raw);

      inputs[name] = Input{input_id, params[1]};
    }
    return inputs;
  };

  attributes = get_inputs(GL_PROGRAM_INPUT);
  uniforms = get_inputs(GL_UNIFORM);
}

template <> void Shader::set_uniform(Shader::Input uniform, const glm::mat4 &value) {
  checkGlError();
  glUseProgram(program);
  glUniformMatrix4fv(uniform.index, 1, GL_FALSE, &value[0][0]);
  checkGlError();
}

template <typename T> void Shader::set_uniform(Shader::Input, const T &) {
  throw std::runtime_error("not implemented");
}

Shader::~Shader() { GL_FUNC(glDeleteProgram(program);) }

} // namespace adbgl

void checkShaderError(GLuint shader, GLenum pname) {
  GLint param;
  glGetShaderiv(shader, pname, &param);
  if (param == GL_FALSE) {
    glGetShaderiv(shader, GL_SHADER_TYPE, &param);
    int logLength = 512;
    GLchar infoLog[logLength];
    glGetShaderInfoLog(shader, logLength, nullptr, infoLog);
    if (param == GL_VERTEX_SHADER) {
      throw std::runtime_error("Vertex shader compilation failed" + std::string(infoLog));
    } else {
      throw std::runtime_error("Fragment shader compilation failed" + std::string(infoLog));
    }
  }
}

void checkProgramError(GLuint shader) {
  GLint param;
  glGetProgramiv(shader, GL_LINK_STATUS, &param);
  if (param == GL_FALSE) {
    int logLength = 512;
    GLchar infoLog[logLength];
    glGetProgramInfoLog(shader, logLength, nullptr, infoLog);
    throw std::runtime_error("Program link error" + std::string(infoLog));
  }
}
