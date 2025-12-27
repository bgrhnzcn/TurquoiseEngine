#ifndef MAT4_HPP
#define MAT4_HPP

#include "vec3.hpp"
#include "vec4.hpp"

struct Mat4 {
	Vec4 col1;
	Vec4 col2;
	Vec4 col3;
	Vec4 col4;

	Mat4();
	Mat4(Vec4 col1, Vec4 col2, Vec4 col3, Vec4 col4);

	static Mat4 identity();

	static Mat4 Scale(const Vec3& values);
	static Mat4 Translate(const Vec3& values);
	static Mat4 Rotate(float angle, const Vec3& axis);

	Mat4 operator*(const Mat4& other)
	{
		Mat4 result;


		return result;
	}

	float *getData();
	void print() const;
};

#endif // !MAT4_HPP
