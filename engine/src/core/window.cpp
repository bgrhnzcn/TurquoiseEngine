#include "core/window.hpp"
#include "GLFW/glfw3.h"
#include "core/input/input.hpp"
#include "core/util/logger.hpp"
#include <exception>

using Logger = ktp::Logger;

namespace trq
{

void APIENTRY openGLDebugCallback(GLenum source, GLenum type, GLuint id,
								  GLenum severity, GLsizei length,
								  const GLchar* message, const void* userParam)
{
	(void)length;
	(void)userParam;

	Logger& log = Logger::getLogger("OpenGL");
	Logger::LogType logLevel;
	std::string sourceText;
	std::string typeText;

	if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
		return;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		sourceText = "API";
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		sourceText = "WindowSystem";
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		sourceText = "ShaderCompiler";
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		sourceText = "ThirdParty";
	case GL_DEBUG_SOURCE_APPLICATION:
		sourceText = "Application";
	default:
		sourceText = "Other";
	}

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		typeText = "Error";
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		typeText = "Deprecated";
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		typeText = "UndefinedBehavior";
	case GL_DEBUG_TYPE_PORTABILITY:
		typeText = "Portability";
	case GL_DEBUG_TYPE_PERFORMANCE:
		typeText = "Performance";
	default:
		typeText = "Other";
	}

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		logLevel = Logger::LogType::ERROR;
	case GL_DEBUG_SEVERITY_MEDIUM:
		logLevel = Logger::LogType::WARNING;
	case GL_DEBUG_SEVERITY_LOW:
		logLevel = Logger::LogType::DEBUG;
	default:
		logLevel = Logger::LogType::INFO;
	}

	log.log(logLevel, "Source: {}, Type: {}, ID: {}, Message: {}", sourceText,
			typeText, id, message);
}

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

#ifdef DEBUG_TAG
	::glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif // DEBUG

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

	if (!::gladLoadGL((::GLADloadfunc)::glfwGetProcAddress))
	{
		log.error("Failed to load OpenGL functions.");
		exit(1);
	}

#ifdef DEBUG_TAG
	::glEnable(GL_DEBUG_OUTPUT);
	::glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	// Register the callback
	::glDebugMessageCallback(openGLDebugCallback, nullptr);

#endif // DEBUG

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

} // namespace trq
