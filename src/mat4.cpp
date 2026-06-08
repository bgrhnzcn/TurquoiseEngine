#include "mat4.hpp"
#include "math.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include <numbers>

lib::Mat4::Mat4()
	: col1(1, 0, 0, 0), col2(0, 1, 0, 0), col3(0, 0, 1, 0), col4(0, 0, 0, 1)
{
}

lib::Mat4::Mat4(float value)
	: col1(value), col2(value), col3(value), col4(value)
{
}

lib::Mat4::Mat4(Vec4 col1, Vec4 col2, Vec4 col3, Vec4 col4)
	: col1(col1), col2(col2), col3(col3), col4(col4)
{
}

auto lib::Mat4::Identity() -> Mat4
{
	return {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
}

auto lib::Mat4::getRawData() -> float* { return &(this->col1.x); }

auto lib::Mat4::getRow(unsigned int index) -> Vec4
{
	float* data = getRawData();
	return (Vec4(data[0 + index], data[4 + index], data[8 + index],
				 data[12 + index]));
}

auto lib::Mat4::Scale(const Vec3& values) -> Mat4
{
	Mat4 result;

	result.col1.x *= values.x;
	result.col2.y *= values.y;
	result.col3.z *= values.z;

	return result;
}

auto lib::Mat4::Translate(const Vec3& values) -> Mat4
{
	Mat4 result;

	result.col4.x += values.x;
	result.col4.y += values.y;
	result.col4.z += values.z;

	return result;
}

auto lib::Mat4::Rotate(float angle, const Vec3& axis) -> Mat4
{
	Mat4 result;
	float radian = angle * (std::numbers::pi / 180.0f);
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

auto lib::Mat4::operator*(const Mat4& other) -> Mat4
{
	Mat4 result;
	Vec4 row1 = this->getRow(0);
	Vec4 row2 = this->getRow(1);
	Vec4 row3 = this->getRow(2);
	Vec4 row4 = this->getRow(3);

	result.col1.x = lib::dot(row1, other.col1);
	result.col2.x = lib::dot(row1, other.col2);
	result.col3.x = lib::dot(row1, other.col3);
	result.col4.x = lib::dot(row1, other.col4);

	result.col1.y = lib::dot(row2, other.col1);
	result.col2.y = lib::dot(row2, other.col2);
	result.col3.y = lib::dot(row2, other.col3);
	result.col4.y = lib::dot(row2, other.col4);

	result.col1.z = lib::dot(row3, other.col1);
	result.col2.z = lib::dot(row3, other.col2);
	result.col3.z = lib::dot(row3, other.col3);
	result.col4.z = lib::dot(row3, other.col4);

	result.col1.w = lib::dot(row4, other.col1);
	result.col2.w = lib::dot(row4, other.col2);
	result.col3.w = lib::dot(row4, other.col3);
	result.col4.w = lib::dot(row4, other.col4);

	return result;
}

auto lib::Mat4::Perspective(float fov, float aspectRatio, float near, float far)
	-> Mat4
{
	Mat4 result;

	float tanHalfFov = std::tan(fov / 2);

	result.col1.x = 1 / (aspectRatio * tanHalfFov);
	result.col2.y = 1 / tanHalfFov;

	result.col3.z = -(far + near) / (far - near);
	result.col3.w = -1;

	result.col4.z = -(2 * far * near) / (far - near);

	return result;
}
