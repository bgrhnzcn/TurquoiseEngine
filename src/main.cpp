#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <iostream>

void callback(GLFWwindow *win, int key, int scancode, int action, int mods) {
  (void)win;
  (void)scancode;
  (void)mods;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
    glfwSetWindowShouldClose(win, GLFW_TRUE);
  if (action == GLFW_PRESS)
		switch (key) {
			case GLFW_KEY_Q:
				glClearColor(1, 0, 0, 1);
				break;
			case GLFW_KEY_W:
				glClearColor(0, 1, 0, 1);
				break;
			case GLFW_KEY_E:
				glClearColor(0, 0, 1, 1);
				break;
			case GLFW_KEY_R:
				glClearColor(1, 1, 1, 1);
				break;
		}
    std::cout << "key pressed: " << key << std::endl;
}

struct Vec3 {
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
	glfwWindowHint(GLFW_REPEAT, GLFW_FALSE);

  GLFWwindow *win = glfwCreateWindow(800, 600, "scope", nullptr, nullptr);

  if (win == nullptr)
	{
		std::cerr << "Failed to create window." << std::endl;
		exit(1);
	}

  glfwMakeContextCurrent(win);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to load OpenGL functions."<< std::endl;
		exit(1);
	}

	glViewport(0, 0, 800, 600);

  glfwSetKeyCallback(win, callback);

	glClearColor(0.34, 0.34, 0.34, 1);
	glClear(GL_COLOR_BUFFER_BIT);

// A simple triangle centered on screen
Vec3 vertices[3] = {
    {-0.5f, -0.5f, 0.0f}, // Bottom Left
    { 0.5f, -0.5f, 0.0f}, // Bottom Right
    { 0.0f,  0.5f, 0.0f}  // Top Center
};
    GLuint vbo;
    glGenBuffers(1, &vbo);
	
	GLuint vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vec3), &vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);


	const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1, 0.5, 0.2, 1);\n"
    "}\0";

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	unsigned int shader = glCreateProgram();
	glAttachShader(shader, vertexShader);
	glAttachShader(shader, fragmentShader);
	glLinkProgram(shader);
	glUseProgram(shader);

  while (!glfwWindowShouldClose(win)) {

		glUseProgram(shader);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	glfwPollEvents();
	glfwSwapBuffers(win);
  }
	glfwTerminate();
  return 0;
}
