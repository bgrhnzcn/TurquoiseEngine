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
		currTime_;
	inline static std::chrono::time_point< std::chrono::steady_clock >
		prevTime_;
	inline static std::chrono::duration< float > deltaTime_;
	inline static std::uint64_t frameCount_ = 0;

  public:
	inline static const float& deltaTime = deltaTime_.count();
	inline static const float& currTime	 = currTime_.time_since_epoch().count();
	inline static const float& prevTime	 = prevTime_.time_since_epoch().count();
	inline static const std::uint64_t& frameCount = frameCount_;

  public:
	static auto tick() -> void;
};

} // namespace lib

#endif // !TIME_HPP
