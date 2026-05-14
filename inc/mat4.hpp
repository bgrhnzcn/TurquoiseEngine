#ifndef MAT4_HPP
#define MAT4_HPP

#include "vec3.hpp"
#include "vec4.hpp"

struct Mat4
{
	Vec4 col1;
	Vec4 col2;
	Vec4 col3;
	Vec4 col4;

	Mat4();
	Mat4(float value);
	Mat4(Vec4 col1, Vec4 col2, Vec4 col3, Vec4 col4);

	static Mat4 identity();

	static Mat4 Scale(const Vec3& values);
	static Mat4 Translate(const Vec3& values);
	static Mat4 Rotate(float angle, const Vec3& axis);
	static Mat4 Perspective(float fov, float aspectRatio, float near, float far);

	Mat4 operator*(const Mat4& other);
	float* getData();
	Vec4 getRow(unsigned int index);
	void print() const;
};

#endif // !MAT4_HPP
