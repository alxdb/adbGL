//
// Created by alxdb on 10/01/19.
//

#include "VertexArray.hpp"

void VertexArray::set_attribute_pointer(VertexBuffer vbo, GLuint index, GLint size, GLenum type, GLsizei stride,
                                        const GLvoid * offset) {
	checkGlError();
	bind();
	glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	unbind();
	checkGlError();
}
