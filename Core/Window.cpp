//
// Created by Alexander Davidson Bryan on 19/06/2018.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "Window.hpp"
#include "Util.hpp"

int Window::instances = 0;

Window::Window(int width, int height, const char * title, bool center) {
	if (instances == 0 && !glfwInit()) {
		throw std::runtime_error("GLFW failed to initialise");
	}
	instances++;
	// Settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Window Creation
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwSetWindowSizeCallback(window, resize);
	if (center) {
		const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowPos(window, (mode->width - width) / 2, (mode->height - height) / 2);
	}
}

void Window::resize(GLFWwindow *, int width, int height) {
	GL_FUNC(glViewport(width, height, 0, 0);)
}

void Window::makeCurrent() {
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("GLEW failed to initialise");
	}
}

Window::~Window() {
	glfwDestroyWindow(window);
	instances--;
	if (instances == 0) {
		glfwTerminate();
	}
}
