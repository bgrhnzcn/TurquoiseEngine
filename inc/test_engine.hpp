#ifndef TEST_ENGINE_HPP
#define TEST_ENGINE_HPP

#include "engine.hpp"

class TestEngine : public Engine
{
	auto update() -> void override;
};

#endif // !TEST_ENGINE_HPP
