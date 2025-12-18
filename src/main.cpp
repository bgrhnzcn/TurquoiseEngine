#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>
#include <print>

#include "logger.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include "mat4.hpp"

void callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	(void)win;
	(void)scancode;
	(void)mods;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		glfwSetWindowShouldClose(win, GLFW_TRUE);
	if (action == GLFW_PRESS)
		switch (key)
		{
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

int main()
{

	int glfw = glfwInit();

	if (glfw == GLFW_FALSE)
	{

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

	GLFWwindow* win = glfwCreateWindow(800, 600, "scope", nullptr, nullptr);

	if (win == nullptr)
	{
		std::cerr << "Failed to create window." << std::endl;
		exit(1);
	}

	glfwMakeContextCurrent(win);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to load OpenGL functions." << std::endl;
		exit(1);
	}

	glViewport(0, 0, 800, 600);

	glfwSetKeyCallback(win, callback);

	glClearColor(0.34, 0.34, 0.34, 1);

	Vertex vertices[] = {
		// FRONT FACE (Normal: 0, 0, 1)
		{ {-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f} }, // Bottom-Left
		{ { 0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f} }, // Bottom-Right
		{ { 0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f} }, // Top-Right
		{ {-0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f} }, // Top-Left

		// BACK FACE (Normal: 0, 0, -1)
		{ { 0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f} }, // Bottom-Left
		{ {-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f} }, // Bottom-Right
		{ {-0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f} }, // Top-Right
		{ { 0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f} }, // Top-Left

		// LEFT FACE (Normal: -1, 0, 0)
		{ {-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f} },
		{ {-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f} },
		{ {-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f} },
		{ {-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f} },

		// RIGHT FACE (Normal: 1, 0, 0)
		{ { 0.5f, -0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f} },
		{ { 0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f} },
		{ { 0.5f,  0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f} },
		{ { 0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f} },

		// TOP FACE (Normal: 0, 1, 0)
		{ {-0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f} },
		{ { 0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f} },
		{ { 0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f} },
		{ {-0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f} },

		// BOTTOM FACE (Normal: 0, -1, 0)
		{ {-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 0.0f} },
		{ { 0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f} },
		{ { 0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f} },
		{ {-0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}, {0.0f, 1.0f} }
	};

	unsigned int indices[] = {
		0, 1, 2,  2, 3, 0,       // Front
		4, 5, 6,  6, 7, 4,       // Back
		8, 9, 10, 10, 11, 8,     // Left
		12, 13, 14, 14, 15, 12,  // Right
		16, 17, 18, 18, 19, 16,  // Top
		20, 21, 22, 22, 23, 20   // Bottom
	};

	Logger::info("vertex size: {}", sizeof(Vertex));
	Logger::info("pos: {}", offsetof(Vertex, pos));
	Logger::info("nor: {}", offsetof(Vertex, nor));
	Logger::info("tex: {}", offsetof(Vertex, tex));

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices,
				 GL_STATIC_DRAW);

	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
						  (GLvoid*)offsetof(Vertex, nor));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
						  (GLvoid*)offsetof(Vertex, tex));
	glEnableVertexAttribArray(2);

	Logger::warning("{}", "test");

	Mat4 mtx = Mat4::identity();
	mtx.print();

	Shader shader("assets/shader.glsl", "assets/fragment.glsl");

	shader.use();

	int transform = glGetUniformLocation(shader.getId(), "transforms");

	glUniformMatrix4fv(transform, 1, false, &mtx.col1.x);

	while (!glfwWindowShouldClose(win))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / 4, GL_UNSIGNED_INT, 0);
		glfwPollEvents();
		glfwSwapBuffers(win);
	}
	glfwTerminate();
	return 0;
}
