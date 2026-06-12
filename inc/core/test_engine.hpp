#ifndef TEST_ENGINE_HPP
#define TEST_ENGINE_HPP

#include "core/engine.hpp"

namespace trq
{

class TestEngine : public Engine
{
	auto update() -> void override;
};

} // namespace trq

#endif // !TEST_ENGINE_HPP
