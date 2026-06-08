#include "window.hpp"
#include "GLFW/glfw3.h"
#include "input.hpp"
#include "logger.hpp"
#include <exception>

using Logger = ktp::Logger;

Window::Window(std::size_t width, std::size_t height, const std::string& title)
{
	const Logger& log = Logger::getLogger("Window");

	int initRes = ::glfwInit();

	if (initRes == GLFW_FALSE)
	{
		log.error("GLFW context initialization failed.");
		std::terminate();
	}

	::glfwDefaultWindowHints();
	::glfwWindowHint(GLFW_REPEAT, GLFW_FALSE);
	handler_ =
		::glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	if (handler_ == nullptr)
	{
		log.error("Window creation failed.");
		std::terminate();
	}

	::glfwMakeContextCurrent(handler_);
	::glfwSetKeyCallback(handler_, Input::inputCallback_);

	if (!::gladLoadGLLoader((::GLADloadproc)::glfwGetProcAddress))
	{
		log.error("Failed to load OpenGL functions.");
		exit(1);
	}

	::glViewport(0, 0, 800, 800);

	::glClearColor(0.34, 0.34, 0.34, 1);
}

auto Window::nativeHandler() -> ::GLFWwindow*
{
	return handler_;
}

auto Window::shouldClose() -> bool
{
	return ::glfwWindowShouldClose(handler_);
}

auto Window::setClose() -> void
{
	::glfwSetWindowShouldClose(handler_, GLFW_TRUE);
}
