//
// Created by Alexander Davidson Bryan on 19/06/2018.
//

#ifndef ADBGL_WINDOW_H
#define ADBGL_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
private:
	GLFWwindow * window;
	static int instances;
public:
	Window(int width, int height, const char * title);
	~Window();
	void makeCurrent();
	bool shouldClose() {
		return glfwWindowShouldClose(window) == 1;
	}
	void update() {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	void setClearColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}
};


#endif //ADBGL_WINDOW_H
