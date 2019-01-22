//
// Created by alxdb on 10/01/19.
//

#ifndef ADBGL_VERTEXBUFFER_HPP
#define ADBGL_VERTEXBUFFER_HPP


#include <GL/glew.h>
#include <vector>
#include "Util.hpp"

class VertexBuffer {
	friend class VertexArray;

private:
	GLuint id = 0;
public:
	VertexBuffer() {
		GL_FUNC(glCreateBuffers(1, &id);)
	}

	template<typename T>
	void buffer_data(std::vector<T> data, GLenum usage) {
		GL_FUNC(glNamedBufferData(id, data.size() * sizeof(T), data.data(), usage);)
	};
};


#endif //ADBGL_VERTEXBUFFER_HPP
