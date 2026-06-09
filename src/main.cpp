
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#define KATIP_IMPLEMENTATION
#include "logger.hpp"
#undef KATIP_IMPLEMENTATION

#include "mat4.hpp"
#include "vec3.hpp"
#include "test_engine.hpp"

using Logger = ktp::Logger;

lib::Mat4 translate = lib::Mat4::Translate({0, 0, 0});

int main()
{
	const Logger& log = Logger::getLogger();

	TestEngine eng;
	eng.init();
	eng.run();
	::glfwTerminate();
	log.error("Error.");
	return 0;
}
