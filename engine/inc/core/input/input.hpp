#ifndef INPUT_HPP
#define INPUT_HPP

#include "core/input/key_code.hpp"
#include "core/input/key_event.hpp"
#include <GLFW/glfw3.h>
#include <array>

namespace trq
{

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

} // namespace trq

#endif // !INPUT_HPP
