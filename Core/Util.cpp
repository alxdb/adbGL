//
// Created by alxdb on 10/01/19.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

std::string read_whole_file(const std::string &filename) {
	std::fstream file(filename);
	if (!file.good()) {
		throw std::runtime_error("could not open/read file: " + filename);
	}
	std::stringstream sstream;
	sstream << file.rdbuf();
	return sstream.str();
}

void checkGlError() {
	std::stringstream glerr;
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		glerr << "glError" << std::endl;
		switch (error) {
			case GL_INVALID_ENUM: {
				glerr << "GL_INVALID_ENUM" << std::endl;
				break;
			}
			case GL_INVALID_VALUE: {
				glerr << "GL_INVALID_VALUE" << std::endl;
				break;
			}
			case GL_INVALID_OPERATION: {
				glerr << "GL_INVALID_OPERATION" << std::endl;
				break;
			}
			case GL_INVALID_FRAMEBUFFER_OPERATION: {
				glerr << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
				break;
			}
			case GL_OUT_OF_MEMORY: {
				glerr << "GL_OUT_OF_MEMORY" << std::endl;
				break;
			}
			default: {
				glerr << "unknown error" << std::endl;
				break;
			}
		}
		checkGlError();
		throw std::runtime_error(glerr.str());
	}
}
