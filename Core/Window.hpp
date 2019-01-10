//
// Created by Alexander Davidson Bryan on 19/06/2018.
//

#ifndef ADBGL_WINDOW_HPP
#define ADBGL_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
private:
	GLFWwindow * window;
	static int instances;

	static void resize(GLFWwindow *, int, int);
public:
	Window(int width, int height, const char * title, bool center = true);
	~Window();
	void makeCurrent();
	bool shouldClose() {
		return glfwWindowShouldClose(window) == 1;
	}
	void update() {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
};


#endif //ADBGL_WINDOW_HPP
