//
// Created by alxdb on 10/01/19.
//

#ifndef ADBGL_VERTEXARRAY_HPP
#define ADBGL_VERTEXARRAY_HPP


#include <GL/glew.h>

#include "VertexBuffer.hpp"
#include "Util.hpp"

class VertexArray {
private:
	GLuint id = 0;
public:
	VertexArray() {
		checkGlError();
		glGenVertexArrays(1, &id);
		checkGlError();
	};

	void bind() {
		checkGlError();
		glBindVertexArray(id);
		checkGlError();
	}

	static void unbind() {
		checkGlError();
		glBindVertexArray(0);
		checkGlError();
	}

	void set_attribute_pointer(VertexBuffer vbo, GLuint index,
	                           GLint size = 4, GLenum type = GL_FLOAT,
	                           GLsizei stride = 0, const GLvoid * offset = nullptr);
};


#endif //ADBGL_VERTEXARRAY_HPP
