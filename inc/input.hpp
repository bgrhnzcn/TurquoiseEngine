#ifndef INPUT_HPP
#define INPUT_HPP

#include "GLFW/glfw3.h"
#include "key_event.hpp"
#include <array>

class Input
{
  public:
	static auto inputCallback_(::GLFWwindow* win, int key, int scancode,
							   int action, int mods) -> void;

  private:
	inline static std::array< KeyState, 128 > currentKeyStates{
		KeyState::RELEASE};
	inline static std::array< KeyState, 128 > previousKeyStates{
		KeyState::RELEASE};
};

#endif // !INPUT_HPP
