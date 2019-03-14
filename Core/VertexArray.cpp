//
// Created by alxdb on 10/01/19.
//

#include "VertexArray.hpp"

namespace adbgl {

void VertexArray::set_attribute_pointer(VertexBuffer &vbo, const Shader::Input &input, const AttributePointer &pointer) {
  bind();
  glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
  checkGlError();
  glEnableVertexAttribArray(input.index);
  checkGlError();
  glVertexAttribPointer(input.index, pointer.size, pointer.type, pointer.normalized, pointer.stride, pointer.offset);
  checkGlError();
  unbind();
}

} // namespace adbgl
