
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "key_code.hpp"
#include "time.hpp"
#include "window.hpp"
// clang-format on
#include <cmath>
#include <cstddef>
#include <numbers>
#include <print>
#include <span>
#include <vector>

#define KATIP_IMPLEMENTATION
#include "logger.hpp"
#undef KATIP_IMPLEMENTATION

#include "mat4.hpp"
#include "math.hpp"
#include "program.hpp"
#include "shader.hpp"

#include "vec3.hpp"
#include "vec4.hpp"
#include "vertex.hpp"

using Logger = ktp::Logger;

lib::Mat4 translate = lib::Mat4::Translate({0, 0, 0});

int main()
{
	const Logger& log = Logger::getLogger();

	constexpr std::size_t size = KeyCode::size();
	log.debug("Constant evaluated size of enum: {}", size);

	log.debug("deltaTime: {}", lib::Time::deltaTime);

	Window win(800u, 600u, "Test");

	Vertex vertices[] = {
		// FRONT FACE (Normal: 0, 0, 1)
		{{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // Bottom-Left
		{{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}, // Bottom-Right
		{{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},	 // Top-Right
		{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}, // Top-Left

		// BACK FACE (Normal: 0, 0, -1)
		{{0.5f, -0.5f, -0.5f},
		 {0.0f, 0.0f, -1.0f},
		 {0.0f, 0.0f}}, // Bottom-Left
		{{-0.5f, -0.5f, -0.5f},
		 {0.0f, 0.0f, -1.0f},
		 {1.0f, 0.0f}}, // Bottom-Right
		{{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}}, // Top-Right
		{{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},  // Top-Left

		// LEFT FACE (Normal: -1, 0, 0)
		{{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
		{{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
		{{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

		// RIGHT FACE (Normal: 1, 0, 0)
		{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
		{{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
		{{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

		// TOP FACE (Normal: 0, 1, 0)
		{{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		{{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
		{{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
		{{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

		// BOTTOM FACE (Normal: 0, -1, 0)
		{{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
		{{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
		{{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
		{{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}}};

	unsigned int indices[] = {
		0,	1,	2,	2,	3,	0,	// Front
		4,	5,	6,	6,	7,	4,	// Back
		8,	9,	10, 10, 11, 8,	// Left
		12, 13, 14, 14, 15, 12, // Right
		16, 17, 18, 18, 19, 16, // Top
		20, 21, 22, 22, 23, 20	// Bottom
	};

	log.info("vertex size: {}", sizeof(Vertex));
	log.info("pos: {}", offsetof(Vertex, pos));
	log.info("nor: {}", offsetof(Vertex, nor));
	log.info("tex: {}", offsetof(Vertex, tex));
	log.info("Vertices: {}", std::span< Vertex >(vertices, vertices + 24));

	::GLuint vao;
	::glGenVertexArrays(1, &vao);
	::glBindVertexArray(vao);

	::GLuint vbo;
	::glGenBuffers(1, &vbo);
	::glBindBuffer(GL_ARRAY_BUFFER, vbo);
	::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices,
				   GL_STATIC_DRAW);

	::GLuint ebo;
	::glGenBuffers(1, &ebo);
	::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices,
				   GL_STATIC_DRAW);

	::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	::glEnableVertexAttribArray(0);

	::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
							(::GLvoid*)offsetof(Vertex, nor));
	::glEnableVertexAttribArray(1);

	::glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
							(::GLvoid*)offsetof(Vertex, tex));
	::glEnableVertexAttribArray(2);

	log.warning("{}", "test");

	log.error("{}", log);

	Shader simple_vert =
		Shader::FromFile("assets/vertex.glsl", Shader::VERTEX, "simple_vert");
	Shader simple_frag = Shader::FromFile("assets/fragment.glsl",
										  Shader::FRAGMENT, "simple_frag");

	Program shaderFill(simple_vert.nativeHandler(), simple_frag.nativeHandler(),
					   "simple_shader");

	float time = 0;
	while (!win.shouldClose())
	{
		time += 0.5;
		glClear(GL_COLOR_BUFFER_BIT);

		auto def	   = lib::Mat4::Identity();
		lib::Vec3 axis = lib::Vec3(1, 1, 0);
		// float sin = (std::sin(time / 50) + 1) / 2;
		auto scale	= lib::Mat4::Scale({0.5f, 0.5f, 0.5f});
		auto rotate = lib::Mat4::Rotate(time, lib::normalize(axis));
		auto pers	= lib::Mat4::Perspective(std::numbers::pi / 2, 1, 0.1, 100);

		auto model	= (translate * (rotate * (scale * def)));
		auto normal = model;
		shaderFill.use();
		shaderFill.setUniform("u_model", model);
		shaderFill.setUniform("u_perspective", pers);
		shaderFill.setUniform("u_normal", normal);
		shaderFill.setUniform("u_cameraDir", lib::Vec3(0, 0, -1));
		::glBindVertexArray(vao);

		::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		shaderFill.setUniform("u_color", lib::Vec4(0.4, 0.3, 0.8, 1));
		::glEnable(GL_POLYGON_OFFSET_FILL);
		::glPolygonOffset(1.0f, 1.0f);
		::glDrawElements(GL_TRIANGLES, sizeof(indices) / 4, GL_UNSIGNED_INT, 0);
		::glDisable(GL_POLYGON_OFFSET_FILL);

		::glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		shaderFill.setUniform("u_color", lib::Vec4(0, 0, 0, 1));
		::glDrawElements(GL_TRIANGLES, sizeof(indices) / 4, GL_UNSIGNED_INT, 0);
		::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		::glfwPollEvents();

		::glfwSwapBuffers(win.nativeHandler());
	}
	::glfwTerminate();
	log.error("Error.");
	return 0;
}
