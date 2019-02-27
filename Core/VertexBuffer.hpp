//
// Created by alxdb on 10/01/19.
//

#ifndef ADBGL_VERTEXBUFFER_HPP
#define ADBGL_VERTEXBUFFER_HPP

#include "Util.hpp"

#include <GL/glew.h>
#include <vector>

namespace adbgl {
class VertexBuffer {
  friend class VertexArray;

private:
  GLuint id = 0;

public:
  VertexBuffer() { GL_FUNC(glCreateBuffers(1, &id);) }

  template <typename T> VertexBuffer(const std::vector<T> &data, GLenum usage) : VertexBuffer() {
    buffer_data(data, usage);
  }

  template <typename T> void buffer_data(const std::vector<T> &data, GLenum usage) {
    GL_FUNC(glNamedBufferData(id, data.size() * sizeof(T), data.data(), usage);)
  }

  ~VertexBuffer() { GL_FUNC(glDeleteBuffers(1, &id);) }
};

} // namespace adbgl

#endif // ADBGL_VERTEXBUFFER_HPP
