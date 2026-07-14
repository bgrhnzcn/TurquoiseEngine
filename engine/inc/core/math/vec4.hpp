#ifndef VEC4_HPP
#define VEC4_HPP

#include <cassert>
#include <format>

namespace trq
{

struct Vec4
{
	float x, y, z, w;

	inline constexpr Vec4();
	inline constexpr Vec4(float val);
	inline constexpr Vec4(float x, float y, float z, float w);

	inline constexpr auto operator[](int index) -> float&;
	inline constexpr auto operator[](int index) const -> const float&;
	inline constexpr auto operator+(const Vec4 other) const -> Vec4;
	inline constexpr auto operator-(const Vec4 other) const -> Vec4;
	inline constexpr auto operator*(const Vec4 other) const -> Vec4;
	inline constexpr auto operator/(const Vec4 other) const -> Vec4;
	inline constexpr auto operator+(const float other) const -> Vec4;
	inline constexpr auto operator-(const float other) const -> Vec4;
	inline constexpr auto operator*(const float other) const -> Vec4;
	inline constexpr auto operator/(const float other) const -> Vec4;
};

inline constexpr Vec4::Vec4() : x(0), y(0), z(0), w(0)
{
}

inline constexpr Vec4::Vec4(float val) : x(val), y(val), z(val), w(val)
{
}

inline constexpr Vec4::Vec4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{
}


inline constexpr auto Vec4::operator[](int index) -> float&
{
	assert(index >= 0 && index < 4
		   && "You can't access bigger index than 3 in Vec4.");
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	default:
		return x;
	}
}

inline constexpr auto Vec4::operator[](int index) const -> const float&
{
	assert(index >= 0 && index < 4
		   && "You can't access bigger index than 3 in Vec4.");
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	default:
		return x;
	}
}

inline constexpr auto Vec4::operator+(const Vec4 other) const -> Vec4
{
	return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

inline constexpr auto Vec4::operator-(const Vec4 other) const -> Vec4
{
	return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

inline constexpr auto Vec4::operator*(const Vec4 other) const -> Vec4
{
	return Vec4(x * other.x, y * other.y, z * other.z, w * other.w);
}

inline constexpr auto Vec4::operator/(const Vec4 other) const -> Vec4
{
	return Vec4(x / other.x, y / other.y, z / other.z, w / other.w);
}

inline constexpr auto Vec4::operator+(const float other) const -> Vec4
{
	return Vec4(x + other, y + other, z + other, w + other);
}

inline constexpr auto Vec4::operator-(const float other) const -> Vec4
{
	return Vec4(x - other, y - other, z - other, w - other);
}

inline constexpr auto Vec4::operator*(const float other) const -> Vec4
{
	return Vec4(x * other, y * other, z * other, w * other);
}

inline constexpr auto Vec4::operator/(const float other) const -> Vec4
{
	const float inv = 1.0f / other;
	return Vec4(x * inv, y * inv, z * inv, w * inv);
}

} // namespace trq

template <>
struct std::formatter< trq::Vec4 >
{
	constexpr auto parse(auto& ctx)
	{
		return ctx.begin();
	}

	auto format(const trq::Vec4& vec, auto& ctx) const
	{
		return std::format_to(ctx.out(),
							  "{{\"X\":{},\"Y\":{},\"Z\":{},\"W\":{}}}", vec.x,
							  vec.y, vec.z, vec.w);
	}
};
#endif // !VEC4_HPP
