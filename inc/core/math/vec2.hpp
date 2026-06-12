
#ifndef VEC2_HPP
#define VEC2_HPP

#include <cassert>
#include <format>

namespace trq
{

struct Vec2
{
	float x, y;

	inline constexpr Vec2();
	inline constexpr Vec2(float val);
	inline constexpr Vec2(float x, float y);

	inline constexpr float& operator[](int index);
	inline constexpr const float& operator[](int index) const;
	inline constexpr Vec2 operator+(const Vec2 other) const;
	inline constexpr Vec2 operator-(const Vec2 other) const;
	inline constexpr Vec2 operator*(const Vec2 other) const;
	inline constexpr Vec2 operator/(const Vec2 other) const;
	inline constexpr Vec2 operator+(const float other) const;
	inline constexpr Vec2 operator-(const float other) const;
	inline constexpr Vec2 operator*(const float other) const;
	inline constexpr Vec2 operator/(const float other) const;
};

inline constexpr Vec2::Vec2() : x(0), y(0)
{
}
inline constexpr Vec2::Vec2(float val) : x(val), y(val)
{
}
inline constexpr Vec2::Vec2(float x, float y) : x(x), y(y)
{
}

inline constexpr float& Vec2::operator[](int index)
{
	assert(index >= 0 && index < 2
		   && "You can't access bigger index than 1 in Vec2.");
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	default:
		return x;
	}
}

inline constexpr const float& Vec2::operator[](int index) const
{
	assert(index >= 0 && index < 2
		   && "You can't access bigger index than 1 in Vec2.");
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	default:
		return x;
	}
}

inline constexpr Vec2 Vec2::operator+(const Vec2 other) const
{
	return Vec2(x + other.x, y + other.y);
}

inline constexpr Vec2 Vec2::operator-(const Vec2 other) const
{
	return Vec2(x - other.x, y - other.y);
}

inline constexpr Vec2 Vec2::operator*(const Vec2 other) const
{
	return Vec2(x * other.x, y * other.y);
}

inline constexpr Vec2 Vec2::operator/(const Vec2 other) const
{
	return Vec2(x / other.x, y / other.y);
}

inline constexpr Vec2 Vec2::operator+(const float other) const
{
	return Vec2(x + other, y + other);
}

inline constexpr Vec2 Vec2::operator-(const float other) const
{
	return Vec2(x - other, y - other);
}

inline constexpr Vec2 Vec2::operator*(const float other) const
{
	return Vec2(x * other, y * other);
}

inline constexpr Vec2 Vec2::operator/(const float other) const
{
	float inv = 1.0f / other;
	return Vec2(x * inv, y * inv);
}

} // namespace trq

template <>
struct std::formatter< trq::Vec2 >
{
	constexpr auto parse(auto& ctx)
	{
		return ctx.begin();
	}

	auto format(const trq::Vec2& vec, auto& ctx) const
	{
		return std::format_to(ctx.out(), "{{\"X\":{},\"Y\":{}}}", vec.x, vec.y);
	}
};

#endif // !VEC2_HPP
