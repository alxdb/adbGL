//
// Created by Alexander Davidson Bryan on 19/06/2018.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <functional>

template<typename T>
size_t vec_byte_size(std::vector<T> vec) {
	return sizeof(T) * vec.size();
}

std::string readFile(const std::string &filename) {
	std::fstream file(filename, std::ios::in);
	if (!file.is_open()) {
		std::cerr << "could not open file: " << filename << std::endl;
		exit(EXIT_FAILURE);
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	return buffer.str();
}

void checkGlError() {
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << "glError" << std::endl;
		switch (error) {
			case GL_INVALID_ENUM: {
				std::cerr << "GL_INVALID_ENUM" << std::endl;
				break;
			}
			case GL_INVALID_VALUE: {
				std::cerr << "GL_INVALID_VALUE" << std::endl;
				break;
			}
			case GL_INVALID_OPERATION: {
				std::cerr << "GL_INVALID_OPERATION" << std::endl;
				break;
			}
			case GL_INVALID_FRAMEBUFFER_OPERATION: {
				std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
				break;
			}
			case GL_OUT_OF_MEMORY: {
				std::cerr << "GL_OUT_OF_MEMORY" << std::endl;
				break;
			}
			default: {
				std::cerr << "unknown error" << std::endl;
				break;
			}
		}
		checkGlError();
		exit(EXIT_FAILURE);
	} else {
		std::cout << "no gl error" << std::endl;
	}
}

void checkShaderError(GLuint shader, GLenum pname) {
	GLint param;
	glGetShaderiv(shader, pname, &param);
	if (param == GL_FALSE) {
		glGetShaderiv(shader, GL_SHADER_TYPE, &param);
		if (param == GL_VERTEX_SHADER) {
			std::cerr << "vertex shader compilation failed" << std::endl;
		} else {
			std::cerr << "fragment shader compilation failed" << std::endl;
		}
		int logLength = 512;
		GLchar infoLog[logLength];
		glGetShaderInfoLog(shader, logLength, nullptr, infoLog);
		std::cerr << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}
}

void checkProgramError(GLuint shader) {
	GLint param;
	glGetProgramiv(shader, GL_LINK_STATUS, &param);
	if (param == GL_FALSE) {
		std::cerr << "Program link error" << std::endl;
		int logLength = 512;
		GLchar infoLog[logLength];
		glGetProgramInfoLog(shader, logLength, nullptr, infoLog);
		std::cerr << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}
}

int main() {
	GLFWwindow * window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	std::cout << "Setting Apple hints" << std::endl;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window) {
		std::cerr << "failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "glew fail" << std::endl;
		return -1;
	}
	if (glewInit() != GLEW_OK) {
		std::cerr << "glew fail" << std::endl;
		return -1;
	}

	std::cout << "renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "openGL: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLFW: " << glfwGetVersionString() << std::endl;

	/* End of initialisation */

	/* Creating Shaders */
	GLuint shader = glCreateProgram();
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	/* This is necessary, memory comes in std::string and lvalue (addressable value) is given with next assignment
	 * c_str addresses internal memory of std::string
	 */
	std::string vertSrc = readFile("../Shaders/test_vs.glsl");
	std::string fragSrc = readFile("../Shaders/test_fs.glsl");
	const char * vertCStr = vertSrc.c_str();
	const char * fragCStr = fragSrc.c_str();
	glShaderSource(vertShader, 1, &vertCStr, nullptr);
	glCompileShader(vertShader);
	checkShaderError(vertShader, GL_COMPILE_STATUS);
	glShaderSource(fragShader, 1, &fragCStr, nullptr);
	glCompileShader(fragShader);
	checkShaderError(fragShader, GL_COMPILE_STATUS);
	glAttachShader(shader, vertShader);
	glAttachShader(shader, fragShader);
	glLinkProgram(shader);
	checkProgramError(shader);
	glUseProgram(shader);

	/* Get shader Properties */
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	struct attrib {
		GLchar name[32];
		GLint size;
		GLenum type;
		GLuint vbo;
	};

	GLint params = 0;
	glGetProgramiv(shader, GL_ACTIVE_ATTRIBUTES, &params);
	attrib attributes[params];

	GLsizei stride = 0;
	for (int i = 0; i < params; i++) {
		GLint size;
		GLenum type;
		glGenBuffers(1, &attributes[i].vbo);
		glGetActiveAttrib(shader, (GLuint) i, 32, nullptr, &size, &type, attributes[i].name);
		switch (type) {
			case GL_FLOAT_VEC4: {
				attributes[i].size = 4 * size;
				attributes[i].type = GL_FLOAT;
				stride += attributes[i].size * sizeof(float);
				break;
			}
			case GL_FLOAT_MAT4: {
				attributes[i].size = 4 * 4 * size;
				attributes[i].type = GL_FLOAT;
				stride += attributes[i].size * sizeof(float);
				break;

			}
			default: {
				std::cerr << "unsupported shader type " << type << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		std::cout << attributes[i].name << std::endl;
		std::cout << i << std::endl;
		std::cout << glGetAttribLocation(shader, attributes[i].name) << std::endl;
	}

	for (int i = 0; i < params; i++) {
		size_t pointer = 0;
		size_t byteSize;
		switch (attributes[i].type) {
			case GL_FLOAT: {
				byteSize = sizeof(float);
				break;
			}
			default: {
				std::cerr << "unsupported gl type " << attributes[i].type << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		for (int j = i - 1; j >= 0; j--) {
			pointer += attributes[j].size * byteSize;
		}
		glBindBuffer(GL_ARRAY_BUFFER, attributes[i].vbo);
		glVertexAttribPointer((GLuint) i, attributes[i].size, attributes[i].type, GL_FALSE, stride, (GLvoid *) pointer);
//		glVertexAttribPointer((GLuint) i, attributes[i].size, attributes[i].type, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray((GLuint) i);
	}

	/* Buffer Data, this must conform to the shaders defined data structure */
	if (params != 1 || attributes[0].type != GL_FLOAT || attributes[0].size != 4) {
		std::cerr << "unsupported shader" << std::endl;
		exit(EXIT_FAILURE);
	}

	size_t numPoints = 3 * 4;
	auto randFloat = std::bind(std::uniform_real_distribution<float>(-1.0f, 1.0f), std::default_random_engine());

	std::vector<float> points;
	for (size_t i = 0; i < numPoints; i++) {
		points.push_back(randFloat());
		points.push_back(randFloat());
		points.push_back(randFloat());
		points.push_back(1.0f);
	}
//	GLuint VBO;
//	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, attributes[0].vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vec_byte_size(points), points.data(), GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
	glValidateProgram(shader);
	GLint success;
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &success);
	checkGlError();
	if (success == GL_FALSE) {
		std::cerr << "invalid shader" << std::endl;
		GLchar log[512];
		glGetProgramInfoLog(shader, 512, nullptr, log);
		std::cerr << log << std::endl;
	}

	/* Loop until the user closes the window */
	glClearColor(0.4, 0.2, 0.3, 1.0);
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei) numPoints);
		checkGlError();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
