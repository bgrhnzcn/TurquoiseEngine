#include "time.hpp"
#include <chrono>

namespace lib
{
auto lib::Time::tick() -> void
{
	prevTime_  = currTime_;
	currTime_  = std::chrono::steady_clock::now();
	deltaTime_ = currTime_ - prevTime_;
	frameCount_++;
}
} // namespace lib
