//
// Created by alxdb on 09/01/19.
//

#ifndef ADBGL_SHADER_HPP
#define ADBGL_SHADER_HPP

#include <string>
#include <GL/glew.h>
#include <map>

class Shader {
private:
	GLuint program;
public:
	struct Input {
		GLuint index;
		GLint type;
	};

	std::map<std::string, Input> attributes;
	std::map<std::string, Input> uniforms;

	Shader(const std::string &vertex_shader_file, const std::string &fragment_shader_file);

	void use() { glUseProgram(program); }

	template<typename T>
	void set_uniform(Input, const T &);

	~Shader();
};


#endif //ADBGL_SHADER_HPP
