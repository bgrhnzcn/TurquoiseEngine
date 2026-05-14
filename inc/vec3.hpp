#ifndef VEC3_HPP
#define VEC3_HPP

struct Vec3
{
	float x = 0, y = 0, z = 0;

	float dot(const Vec3& other);

	float norm();

	Vec3 normalize();

	Vec3 operator/(const float other);
};

#endif // !VEC3_HPP
