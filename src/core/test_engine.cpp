#include "core/test_engine.hpp"
#include "core/input/input.hpp"
#include "core/input/key_code.hpp"
#include "core/util/logger.hpp"
#include "core/util/time.hpp"

namespace trq
{

auto TestEngine::update() -> void
{
	ktp::Logger& log =
		ktp::Logger::getLogger("Engine").setLogLevel(ktp::Logger::ERROR);
	if (Input::keyPressed(KeyCode::KEY_Q))
		log.info("KeyPress event worked correctly.");

	if (Input::keyReleased(KeyCode::KEY_W))
		log.info("KeyRelease event worked correctly.");

	if (Input::keyDown(KeyCode::KEY_E))
		log.info("KeyDown event worked correctly.");

	if (Input::keyUp(KeyCode::KEY_R) && Time::frameCount % 10 == 0)
		log.info("KeyUp event worked correctly.");

	if (Input::keyReleased(KeyCode::KEY_ESCAPE))
		shutdown();
}

} // namespace trq
