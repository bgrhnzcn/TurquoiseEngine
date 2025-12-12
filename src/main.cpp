#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

void callback(GLFWwindow *win, int key, int scancode, int action, int mods) {
  (void)win;
  (void)scancode;
  (void)mods;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
    glfwSetWindowShouldClose(win, GLFW_TRUE);
  if (action == GLFW_PRESS)
    std::cout << "key pressed: " << key << std::endl;
}

struct Vec3
{
	float x, y, z;
};

int main() {

  int glfw = glfwInit();

  if (glfw == GLFW_FALSE) {

    std::cout << "GLFW init failed." << std::endl;
    exit(1);
  }

  /*
  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  if (monitor == nullptr) {
    std::cout << "GLFW can't find Window." << std::endl;
    exit(1);
  }
  */

  glfwDefaultWindowHints();

  GLFWwindow *win = glfwCreateWindow(800, 600, "scope", nullptr, nullptr);

  if (win == nullptr)
    std::cerr << "Failed to create window." << std::endl;

  glfwSetKeyCallback(win, callback);

  while (!glfwWindowShouldClose(win)) {
    glfwPollEvents();
  }

	Vec3 vertices[3] = {{1, 1, 0},{0, 1, 0},{2, 1, 0}};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(vbo, 3 * sizeof(Vec3), &vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

  return 0;
}
