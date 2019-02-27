//
// Created by alxdb on 10/01/19.
//

#include "VertexArray.hpp"

namespace adbgl {

void VertexArray::set_attribute_pointer(VertexBuffer vbo, Shader::Input input, AttributePointer pointer) {
  checkGlError();
  bind();
  glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
  glEnableVertexAttribArray(input.index);
  glVertexAttribPointer(input.index, pointer.size, pointer.type, pointer.normalized, pointer.stride, pointer.offset);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  unbind();
  checkGlError();
}

} // namespace adbgl
