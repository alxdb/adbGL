//
// Created by alxdb on 10/01/19.
//

#include "VertexArray.hpp"

namespace adbgl {
void VertexArray::set_attribute_pointer(
		VertexBuffer vbo,
		Shader::Input input,
		GLint size,
		GLenum type,
		GLsizei stride,
		const GLvoid* offset)
{
	GL_FUNC(
			bind();
			glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
			glEnableVertexAttribArray(input.index);
			glVertexAttribPointer(input.index, size, type, GL_FALSE, stride, offset);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			unbind();
	)
}
}
