#include <string>
#include <SOIL/SOIL.h>
#include <GL/glew.h>

class Texture {
private:
	GLuint handle;
public:
	Texture(std::string filename) : handle(SOIL_load_OGL_texture(filename.c_str(), 0, 0, 0)) {
	}
};
