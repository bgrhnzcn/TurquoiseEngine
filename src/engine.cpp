#include "engine.hpp"
#include "time.hpp"
#include "window.hpp"

auto Engine::init() -> void
{
	window_ = Window(800u, 600u, "GameTitle");
}

auto Engine::run() -> void
{
	while (!window_.shouldClose())
	{
		// TODO: Create renderer and move render specific (OpenGL or Vulkan)
		// codes to there.
		lib::Time::tick();
		::glClear(GL_COLOR_BUFFER_BIT);

		// auto def	   = lib::Mat4::Identity();
		// lib::Vec3 axis = lib::Vec3(1, 1, 0);
		//  float sin = (std::sin(time / 50) + 1) / 2;
		// auto scale	= lib::Mat4::Scale({0.5f, 0.5f, 0.5f});
		// auto rotate = lib::Mat4::Rotate(time, lib::normalize(axis));
		// auto pers	= lib::Mat4::Perspective(std::numbers::pi / 2, 1, 0.1,
		// 100);

		// auto model	= (translate * (rotate * (scale * def)));
		// auto normal = model;
		// shaderFill.use();
		// shaderFill.setUniform("u_model", model);
		// shaderFill.setUniform("u_perspective", pers);
		// shaderFill.setUniform("u_normal", normal);
		// shaderFill.setUniform("u_cameraDir", lib::Vec3(0, 0, -1));
		//::glBindVertexArray(vao);

		//::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// shaderFill.setUniform("u_color", lib::Vec4(0.4, 0.3, 0.8, 1));
		//::glEnable(GL_POLYGON_OFFSET_FILL);
		//::glPolygonOffset(1.0f, 1.0f);
		//::glDrawElements(GL_TRIANGLES, sizeof(indices) / 4, GL_UNSIGNED_INT,
		//: 0); :glDisable(GL_POLYGON_OFFSET_FILL);

		//::glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// shaderFill.setUniform("u_color", lib::Vec4(0, 0, 0, 1));
		//::glDrawElements(GL_TRIANGLES, sizeof(indices) / 4, GL_UNSIGNED_INT,
		//: 0); :glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		this->update();
		::glfwSwapBuffers(window_.nativeHandler());
		::glfwPollEvents();
	}
}

auto Engine::shutdown() -> void
{
	isShutdown_ = true;
	window_.setClose();
}

auto Engine::shouldShutdown() -> bool
{
	return isShutdown_;
}
