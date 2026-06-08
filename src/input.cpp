#include "input.hpp"
#include "key_event.hpp"
#include "logger.hpp"

using ktp::Logger;

auto Input::inputCallback_(::GLFWwindow* win, int key, int scancode, int action,
						   int mods) -> void
{
	(void)win;
	(void)scancode;
	(void)mods;

	const Logger& logger = Logger::getLogger("Inputs");

	if (key >= 0 && key <= 127)
	{
		if (action == GLFW_PRESS)
			Input::currentKeyStates.at(key) = KeyState::PRESS;
		if (action == GLFW_RELEASE)
			Input::currentKeyStates.at(key) = KeyState::RELEASE;
	}
	logger.debug("Key Pressed: {}", key);
}
