//
// Created by alxdb on 10/01/19.
//

#ifndef ADBGL_VERTEXARRAY_HPP
#define ADBGL_VERTEXARRAY_HPP

#include <GL/glew.h>

#include "Shader.hpp"
#include "Util.hpp"
#include "VertexBuffer.hpp"

namespace adbgl {

class VertexArray {
private:
  GLuint id = 0;

  // Move Semantics
  VertexArray(const VertexBuffer &) = delete;
  VertexArray &operator=(const VertexBuffer &) = delete;
  VertexArray(VertexBuffer &&);
  VertexArray &operator=(const VertexBuffer &&);

public:
  struct AttributePointer {
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    const GLvoid *offset;
  };

  VertexArray() { GL_FUNC(glGenVertexArrays(1, &id);) }

  void bind() { GL_FUNC(glBindVertexArray(id);) }

  static void unbind() { GL_FUNC(glBindVertexArray(0);) }

  void set_attribute_pointer(VertexBuffer &vbo, const Shader::Input &input, const AttributePointer &pointer);

  ~VertexArray() { GL_FUNC(glDeleteVertexArrays(1, &id);) }
};

namespace attribute_types {
constexpr VertexArray::AttributePointer vec4_float{4, GL_FLOAT, GL_FALSE, 0, 0};
constexpr VertexArray::AttributePointer vec2_float{2, GL_FLOAT, GL_FALSE, 0, 0};
} // namespace attribute_types

} // namespace adbgl

#endif // ADBGL_VERTEXARRAY_HPP
