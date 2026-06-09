#ifndef INPUT_HPP
#define INPUT_HPP

#include "GLFW/glfw3.h"
#include "key_code.hpp"
#include "key_event.hpp"
#include <array>

class Input
{
  public:
	static auto inputCallback_(::GLFWwindow* win, int key, int scancode,
							   int action, int mods) -> void;
	static auto inputUpdate_() -> void;
	static auto keyPressed(KeyCode key) -> bool;
	static auto keyReleased(KeyCode key) -> bool;
	static auto keyDown(KeyCode key) -> bool;
	static auto keyUp(KeyCode key) -> bool;

  private:
	inline static std::array< KeyState, 512 > currentKeyStates{
		KeyState::RELEASE};
	inline static std::array< KeyState, 512 > previousKeyStates{
		KeyState::RELEASE};
};

#endif // !INPUT_HPP
