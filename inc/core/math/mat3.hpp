#ifndef MAT3_HPP
#define MAT3_HPP

#include "core/math/vec3.hpp"

namespace trq
{

struct Mat3
{
	Vec3 col1;
	Vec3 col2;
	Vec3 col3;

	Mat3();
	Mat3(float value);
	Mat3(Vec3 col1, Vec3 col2, Vec3 col3);

	static Mat3 identity();

	Mat3 inverse();
	Mat3 transpose();

	Mat3 operator*(const Mat3& other);
	float* getData();
	Vec3 getRow(unsigned int index);
	void print() const;
};

} // namespace trq

#endif // !MAT4_HPP
