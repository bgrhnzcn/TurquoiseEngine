#include "core/util/time.hpp"
#include <chrono>

namespace trq
{

auto Time::tick() -> void
{
	prevTimePoint_	   = currTimePoint_;
	currTimePoint_	   = std::chrono::steady_clock::now();
	deltaTimeDuration_ = currTimePoint_ - prevTimePoint_;
	currTime_		   = currTimePoint_.time_since_epoch().count();
	deltaTime_		   = deltaTimeDuration_.count();
	if (deltaTime > 0.33)
		deltaTime_ = 0.33;
	frameCount_++;
}

} // namespace trq
