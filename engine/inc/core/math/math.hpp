#ifndef MATH_HPP
#define MATH_HPP

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include <cmath>

namespace trq::math
{

// Dot products
inline constexpr float dot(const Vec2 v1, const Vec2 v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}
inline constexpr float dot(const Vec3 v1, const Vec3 v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}
inline constexpr float dot(const Vec4 v1, const Vec4 v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

// Distance Squares
inline constexpr float distanceSqr(const Vec2 v1, const Vec2 v2)
{
	return dot(v2 - v1, v2 - v1);
}
inline constexpr float distanceSqr(const Vec3 v1, const Vec3 v2)
{
	return dot(v2 - v1, v2 - v1);
}
inline constexpr float distanceSqr(const Vec4 v1, const Vec4 v2)
{
	return dot(v2 - v1, v2 - v1);
}

// Distances
inline constexpr float distance(const Vec2 v1, const Vec2 v2)
{
	return std::sqrt(distanceSqr(v1, v2));
}
inline constexpr float distance(const Vec3 v1, const Vec3 v2)
{
	return std::sqrt(distanceSqr(v1, v2));
}
inline constexpr float distance(const Vec4 v1, const Vec4 v2)
{
	return std::sqrt(distanceSqr(v1, v2));
}

// Normalize
inline Vec2 normalize(const Vec2 vec)
{
	return vec * (1.0f / std::sqrt(dot(vec, vec)));
}
inline Vec3 normalize(const Vec3 vec)
{
	return vec * (1.0f / std::sqrt(dot(vec, vec)));
}
inline Vec4 normalize(const Vec4 vec)
{
	return vec * (1.0f / std::sqrt(dot(vec, vec)));
}

// Norm
inline float norm(const Vec2 vec)
{
	return std::sqrt(dot(vec, vec));
}
inline float norm(const Vec3 vec)
{
	return std::sqrt(dot(vec, vec));
}
inline float norm(const Vec4 vec)
{
	return std::sqrt(dot(vec, vec));
}

// Reduce
inline constexpr auto reduce(const Vec2 vec) -> float
{
	return vec.x + vec.y;
}

inline constexpr auto reduce(const Vec3 vec) -> float
{
	return vec.x + vec.y + vec.z;
}

inline constexpr auto reduce(const Vec4 vec) -> float
{
	return vec.x + vec.y + vec.z + vec.w;
}

// Cross
inline constexpr float cross(const Vec2 v1, const Vec2 v2)
{
	return (v1.x * v2.y) - (v1.y * v2.x);
}
inline constexpr Vec3 cross(const Vec3 v1, const Vec3 v2)
{
	return Vec3((v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z),
				(v1.x * v2.y) - (v1.y * v2.x));
}

} // namespace trq::math
#endif // !MATH_HPP
