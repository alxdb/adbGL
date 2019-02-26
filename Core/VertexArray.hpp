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

public:
	VertexArray()
	{
		GL_FUNC(glGenVertexArrays(1, &id);)
	}

	void bind()
	{
		GL_FUNC(glBindVertexArray(id);)
	}

	static void unbind()
	{
		GL_FUNC(glBindVertexArray(0);)
	}

	void set_attribute_pointer(VertexBuffer vbo, Shader::Input input,
			GLint size = 4, GLenum type = GL_FLOAT,
			GLsizei stride = 0,
			const GLvoid* offset = nullptr);
};
}

#endif // ADBGL_VERTEXARRAY_HPP
