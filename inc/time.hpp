#ifndef TIME_HPP
#define TIME_HPP

#include <GL/glcorearb.h>
#include <chrono>
#include <cstdint>

namespace lib
{
class Time
{
  private:
	inline static std::chrono::time_point< std::chrono::steady_clock >
		currTimePoint_;
	inline static std::chrono::time_point< std::chrono::steady_clock >
		prevTimePoint_;
	inline static std::chrono::duration< float > deltaTimeDuration_;

  private:
	inline static double currTime_			= 0;
	inline static double deltaTime_			= 0;
	inline static std::uint64_t frameCount_ = 0;

  public:
	inline static const double& deltaTime		  = deltaTime_;
	inline static const double& currTime			  = currTime_;
	inline static const std::uint64_t& frameCount = frameCount_;

  public:
	static auto tick() -> void;
};

} // namespace lib

#endif // !TIME_HPP
