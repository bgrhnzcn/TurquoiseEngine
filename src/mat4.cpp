#include "mat4.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include <cmath>
#include <print>

Mat4::Mat4()
	: col1(1, 0, 0, 0), col2(0, 1, 0, 0), col3(0, 0, 1, 0), col4(0, 0, 0, 1)
{
}

Mat4::Mat4(Vec4 col1, Vec4 col2, Vec4 col3, Vec4 col4)
	: col1(col1), col2(col2), col3(col3), col4(col4)
{
}

Mat4 Mat4::identity()
{
	return {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
}

float* Mat4::getData() { return &(this->col1.x); }

void Mat4::print() const
{
	std::println("{} {} {} {}\n{} {} {} {}\n{} {} {} {}\n{} {} {} {}\n", col1.x,
				 col2.x, col3.x, col4.x, col1.y, col2.y, col3.y, col4.y, col1.z,
				 col2.z, col3.z, col4.z, col1.w, col2.w, col3.w, col4.w);
}

Mat4 Mat4::Scale(const Vec3& values)
{
	Mat4 result;

	result.col1.x = values.x;
	result.col2.y = values.y;
	result.col3.z = values.z;

	return result;
}

Mat4 Mat4::Translate(const Vec3& values)
{
	Mat4 result;

	result.col4.x = values.x;
	result.col4.y = values.y;
	result.col4.z = values.z;

	return result;
}

Mat4 Mat4::Rotate(float angle, const Vec3& axis)
{
	Mat4 result;
	float radian = angle * (M_PI / 180.0f);
	float c		 = std::cos(radian);
	float s		 = std::sin(radian);
	float omc	 = 1.0f - c;

	result.col1.x = (axis.x * axis.x * omc) + c;
	result.col1.y = (axis.x * axis.y * omc) + (axis.z * s);
	result.col1.z = (axis.x * axis.z * omc) - (axis.y * s);

	result.col2.x = (axis.x * axis.y * omc) - (axis.z * s);
	result.col2.y = (axis.y * axis.y * omc) + c;
	result.col2.z = (axis.z * axis.y * omc) + (axis.x * s);

	result.col3.x = (axis.x * axis.z * omc) + (axis.y * s);
	result.col3.y = (axis.y * axis.z * omc) - (axis.x * s);
	result.col3.z = (axis.z * axis.z * omc) + c;

	return result;
}
