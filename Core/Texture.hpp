#include <string>
#include <sstream>
#include <SOIL/SOIL.h>
#include <GL/glew.h>

#include "Util.hpp"

class Texture {
private:
	GLuint handle;
public:
	Texture(std::string filename) : handle(SOIL_load_OGL_texture(filename.c_str(), 0, 0, 0)) {
		if (handle == 0) {
			std::stringstream err_msg;
			err_msg << "SOIL error: " << SOIL_last_result();
			throw std::runtime_error(err_msg.str());
		}
	}
	void bind() {
		GL_FUNC(glBindTexture(GL_TEXTURE_2D, handle);)
	}

	static void unbind() {
		GL_FUNC(glBindTexture(GL_TEXTURE_2D, 0);)
	}
};
