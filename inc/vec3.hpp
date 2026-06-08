#ifndef VEC3_HPP
#define VEC3_HPP

#include <cassert>
#include <format>

namespace lib
{

struct Vec3
{
	float x, y, z;

	inline constexpr Vec3();
	inline constexpr Vec3(float val);
	inline constexpr Vec3(float x, float y, float z);

	inline constexpr auto operator[](int index) -> float&;
	inline constexpr auto operator[](int index) const -> const float&;
	inline constexpr auto operator+(const Vec3 other) const -> Vec3;
	inline constexpr auto operator-(const Vec3 other) const -> Vec3;
	inline constexpr auto operator*(const Vec3 other) const -> Vec3;
	inline constexpr auto operator/(const Vec3 other) const -> Vec3;
	inline constexpr auto operator+(const float other) const -> Vec3;
	inline constexpr auto operator-(const float other) const -> Vec3;
	inline constexpr auto operator*(const float other) const -> Vec3;
	inline constexpr auto operator/(const float other) const -> Vec3;

	inline auto normalize() const -> Vec3;
	inline constexpr auto cross(const Vec3 other) const -> Vec3;

	inline auto norm() const -> float;
	inline auto distance(const Vec3 other) const -> float;
	inline constexpr auto distanceSqr(const Vec3 other) const -> float;
	inline constexpr auto dot(const Vec3 other) const -> float;
};

inline constexpr Vec3::Vec3() : x(0), y(0), z(0) {}
inline constexpr Vec3::Vec3(float val) : x(val), y(val), z(val) {}
inline constexpr Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

inline constexpr auto Vec3::operator[](int index) -> float&
{
	assert(index >= 0 && index < 3
		   && "You can't access bigger index than 2 in Vec3.");
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	default:
		return x;
	}
}

inline constexpr auto Vec3::operator[](int index) const -> const float&
{
	assert(index >= 0 && index < 3
		   && "You can't access bigger index than 2 in Vec3.");
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	default:
		return x;
	}
}

inline constexpr auto Vec3::operator+(const Vec3 other) const -> Vec3
{
	return Vec3(x + other.x, y + other.y, z + other.z);
}

inline constexpr auto Vec3::operator-(const Vec3 other) const -> Vec3
{
	return Vec3(x - other.x, y - other.y, z - other.z);
}

inline constexpr auto Vec3::operator*(const Vec3 other) const -> Vec3
{
	return Vec3(x * other.x, y * other.y, z * other.z);
}

inline constexpr auto Vec3::operator/(const Vec3 other) const -> Vec3
{

	return Vec3(x / other.x, y / other.y, z / other.z);
}

inline constexpr auto Vec3::operator+(const float other) const -> Vec3
{
	return Vec3(x + other, y + other, z + other);
}

inline constexpr auto Vec3::operator-(const float other) const -> Vec3
{
	return Vec3(x - other, y - other, z - other);
}

inline constexpr auto Vec3::operator*(const float other) const -> Vec3
{
	return Vec3(x * other, y * other, z * other);
}

inline constexpr auto Vec3::operator/(const float other) const -> Vec3
{
	float inv = 1.0f / other;
	return Vec3(x * inv, y * inv, z * inv);
}

} // namespace lib

template <>
struct std::formatter< lib::Vec3 >
{
	constexpr auto parse(auto& ctx) { return ctx.begin(); }

	auto format(const lib::Vec3& vec, auto& ctx) const
	{
		return std::format_to(ctx.out(), "{{\"X\":{},\"Y\":{},\"Z\":{}}}",
							  vec.x, vec.y, vec.z);
	}
};

#endif // !VEC3_HPP
