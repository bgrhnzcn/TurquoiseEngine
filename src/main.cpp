
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "core/math/mat4.hpp"
#include "core/math/vec3.hpp"
#include "core/test_engine.hpp"
#include "core/util/logger.hpp"

using Logger = ktp::Logger;

trq::Mat4 translate = trq::Mat4::Translate({0, 0, 0});

int main()
{
	const Logger& log = Logger::getLogger();

	trq::TestEngine eng;
	eng.init();
	eng.run();
	::glfwTerminate();
	log.error("Error.");
	return 0;
}
