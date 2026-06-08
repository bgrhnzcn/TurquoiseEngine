#ifndef WINDOW_HPP
#define WINDOW_HPP

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format off
#include <cstddef>
#include <string>


class Window
{
  public:
	Window(std::size_t width, std::size_t height, const std::string& title);

  public:
	auto nativeHandler() -> ::GLFWwindow*;
	auto shouldClose() -> bool;
	auto setClose() -> void;

  private:

  private:
	::GLFWwindow* handler_;
};

#endif // !WINDOW_HPP
