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

int main() {
	GLFWwindow *window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}


	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cerr << "glew fail" << std::endl;
		return -1;
	}

	/* End of initialisation */

	/* Creating Shaders */
	auto readFile = [](std::string filename) {
		std::fstream file(filename, std::ios::in);
		if (!file.is_open()) {
			std::cerr << "could not open file: " << filename << std::endl;
			exit(EXIT_FAILURE);
		}
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		return buffer.str();
	};

	GLuint shader = glCreateProgram();
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char *vertSrc = readFile("../Shaders/test_vs.glsl").c_str();
	const char *fragSrc = readFile("../Shaders/test_fs.glsl").c_str();
	glShaderSource(vertShader, 1, &vertSrc, nullptr);
	glShaderSource(vertShader, 1, &fragSrc, nullptr);
	glAttachShader(shader, vertShader);
	glAttachShader(shader, fragShader);
	glLinkProgram(shader);
	glCompileShader(shader);

	/* example points */
	size_t numPoints = 5;
	auto randFloat = std::bind(std::uniform_real_distribution<float>(0.0, 1.0), std::default_random_engine());

	std::vector<float> points(numPoints * 3);
	for (int i = 0; i < numPoints * 3; i++) {
		points.push_back(randFloat());
	}

	/* VBO */
	GLuint VBO;
	glGenBuffers(1, &VBO);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}