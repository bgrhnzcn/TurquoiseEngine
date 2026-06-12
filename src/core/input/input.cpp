#include "core/input/input.hpp"
#include "core/input/key_code.hpp"
#include "core/input/key_event.hpp"
#include "core/util/logger.hpp"

using ktp::Logger;

namespace trq
{

auto Input::inputCallback_(::GLFWwindow* win, int key, int scancode, int action,
						   int mods) -> void
{
	(void)win;
	(void)scancode;
	(void)mods;

	const Logger& logger = Logger::getLogger("Inputs");

	if (key >= 0 && key < 512)
	{
		if (action == GLFW_PRESS)
		{
			auto code = KeyCode::fromKeycode(key);
			if (code.has_value())
				Input::currentKeyStates.at(key) = KeyState::PRESS;
			else
				logger.warning("Key Pressed: Unkown");
		}
		if (action == GLFW_RELEASE)
		{
			auto code = KeyCode::fromKeycode(key);
			if (code.has_value())
				Input::currentKeyStates.at(key) = KeyState::RELEASE;
			else
				logger.warning("Key Released: Unkown");
		}
	}
}

auto Input::inputUpdate_() -> void
{
	previousKeyStates = currentKeyStates;
}

auto Input::keyPressed(KeyCode key) -> bool
{
	return (currentKeyStates.at(key) == KeyState::PRESS
			&& previousKeyStates.at(key) == KeyState::RELEASE);
}

auto Input::keyReleased(KeyCode key) -> bool
{
	return (currentKeyStates.at(key) == KeyState::RELEASE
			&& previousKeyStates.at(key) == KeyState::PRESS);
}

auto Input::keyDown(KeyCode key) -> bool
{
	return (currentKeyStates.at(key) == KeyState::PRESS);
}

auto Input::keyUp(KeyCode key) -> bool
{
	return (currentKeyStates.at(key) == KeyState::RELEASE);
}

} // namespace trq
