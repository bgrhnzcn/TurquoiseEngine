#include "test_engine.hpp"
#include "input.hpp"
#include "key_code.hpp"
#include "logger.hpp"
#include "time.hpp"

auto TestEngine::update() -> void
{
	const ktp::Logger& log = ktp::Logger::getLogger();
	if (Input::keyPressed(KeyCode::KEY_Q))
		log.info("KeyPress event worked correctly.");

	if (Input::keyReleased(KeyCode::KEY_W))
		log.info("KeyRelease event worked correctly.");

	if (Input::keyDown(KeyCode::KEY_E))
		log.info("KeyDown event worked correctly.");

	if (Input::keyUp(KeyCode::KEY_R) && lib::Time::frameCount % 10 == 0)
		log.info("KeyUp event worked correctly.");

	if (Input::keyReleased(KeyCode::KEY_ESCAPE))
		shutdown();
}
