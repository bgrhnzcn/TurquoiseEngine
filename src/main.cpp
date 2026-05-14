#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstddef>

#include "logger.hpp"
#include "shader.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "vertex.hpp"
#include "mat4.hpp"

Mat4 translate = Mat4::Translate({0,0,0});

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
		case GLFW_KEY_W:
			glClearColor(0, 1, 0, 1);
			break;
		case GLFW_KEY_R:
			glClearColor(1, 1, 1, 1);
			break;
		case GLFW_KEY_UP:
			translate = Mat4::Translate({translate.col4.x,translate.col4.y + 0.1f, translate.col4.z});
			break;
		case GLFW_KEY_DOWN:
			translate = Mat4::Translate({translate.col4.x,translate.col4.y - 0.1f, translate.col4.z});
			break;
		case GLFW_KEY_LEFT:
			translate = Mat4::Translate({translate.col4.x - 0.1f,translate.col4.y, translate.col4.z});
			break;
		case GLFW_KEY_RIGHT:
			translate = Mat4::Translate({translate.col4.x + 0.1f,translate.col4.y, translate.col4.z});
			break;
		case GLFW_KEY_E:
			translate = Mat4::Translate({translate.col4.x, translate.col4.y, translate.col4.z - 0.1f});
			break;
		case GLFW_KEY_Q:
			translate = Mat4::Translate({translate.col4.x, translate.col4.y, translate.col4.z + 0.1f});
			break;
		}
	Logger::info("Key Pressed: {}", key);
}

int main()
{

	int glfw = glfwInit();

	if (glfw == GLFW_FALSE)
	{
		Logger::error("GLFW init failed.");
		exit(1);
	}

	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_REPEAT, GLFW_FALSE);

	GLFWwindow* win = glfwCreateWindow(800, 800, "scope", nullptr, nullptr);

	if (win == nullptr)
	{
		Logger::error("Failed to create window.");
		exit(1);
	}

	glfwMakeContextCurrent(win);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::error("Failed to load OpenGL functions.");
		exit(1);
	}

	glViewport(0, 0, 800, 800);

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

	Shader shader("assets/shader.glsl", "assets/fragment.glsl");

	shader.use();

	float time = 0;
	while (!glfwWindowShouldClose(win))
	{
		time += 0.5;
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();

		auto def = Mat4::identity();
		Vec3 axis = Vec3(1, 1, 0);
		float sin = (std::sin(time / 50) + 1) / 2;
		auto scale = Mat4::Scale({1, 1, 1});
		auto rotate = Mat4::Rotate(time, axis.normalize());
		auto pers = Mat4::Perspective(M_PI / 2, 1, 0.1, 100);

		auto transform = pers * (translate * (rotate * (scale * def)));
		shader.setUniform("u_transform", transform);
		shader.setUniform("u_color", Vec4(1 - sin));

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / 4, GL_UNSIGNED_INT, 0);
		glfwPollEvents();
		glfwSwapBuffers(win);
	}
	glfwTerminate();
	Logger::error("Error.");
	return 0;
}
