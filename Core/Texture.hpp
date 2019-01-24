#include <string>
#include <sstream>
#include <GL/glew.h>

#include "Util.hpp"

class Texture {
private:
	GLuint handle;
public:
	Texture(std::string filename);

	void bind() {
		GL_FUNC(glBindTexture(GL_TEXTURE_2D, handle);)
	}

	static void unbind() {
		GL_FUNC(glBindTexture(GL_TEXTURE_2D, 0);)
	}
};
