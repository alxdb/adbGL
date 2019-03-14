//
// Created by Alexander Davidson Bryan on 19/06/2018.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

#include "Util.hpp"
#include "Window.hpp"

namespace adbgl {
int Window::instances = 0;

Window::Window(int width, int height, const char *title, bool fullscreen) {
  if (instances == 0 && !glfwInit()) {
    throw std::runtime_error("GLFW failed to initialise");
  }
  instances++;
  // Settings
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 8);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // Window Creation
  if (fullscreen) {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    window = glfwCreateWindow(mode->width, mode->height, title, monitor, nullptr);
  } else {
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  }
  glfwSetWindowSizeCallback(window, resize);
}

void Window::resize(GLFWwindow *, int width, int height) { GL_FUNC(glViewport(0, 0, width, height);) }

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
} // namespace adbgl
