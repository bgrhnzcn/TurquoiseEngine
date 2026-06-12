#ifndef MAT4_HPP
#define MAT4_HPP

#include "vec3.hpp"
#include "vec4.hpp"

namespace trq
{

struct Mat4
{
	Vec4 col1;
	Vec4 col2;
	Vec4 col3;
	Vec4 col4;

	Mat4();
	Mat4(float value);
	Mat4(Vec4 col1, Vec4 col2, Vec4 col3, Vec4 col4);

	static auto Identity() -> Mat4;

	static auto Scale(const Vec3& values) -> Mat4;
	static auto Translate(const Vec3& values) -> Mat4;
	static auto Rotate(float angle, const Vec3& axis) -> Mat4;
	static auto Perspective(float fov, float aspectRatio, float near, float far)
		-> Mat4;

	auto inverse() -> Mat4;
	auto transpose() -> Mat4;

	auto operator*(const Mat4& other) -> Mat4;
	auto getRawData() -> float*;
	auto getRow(unsigned int index) -> Vec4;
};

} // namespace trq

template <>
struct std::formatter< trq::Mat4 >
{
	constexpr auto parse(auto& ctx)
	{
		return ctx.begin();
	}

	auto format(const trq::Mat4& vec, auto& ctx) const
	{
		return std::format_to(
			ctx.out(),
			"{{\"Column1\":{},\"Column2\":{},\"Column3\":{},\"Column4\":{}}}",
			vec.col1, vec.col2, vec.col3, vec.col4);
	}
};
#endif // !MAT4_HPP
