#include "vec3.hpp"
#include <cmath>

float Vec3::dot(const Vec3& other)
{
	return ((this->x * other.x) + (this->y * other.y) + (this->z * other.z));
}

float Vec3::norm()
{
	return std::sqrt(this->dot(*this));
}

Vec3 Vec3::normalize()
{
	return *this / this->norm();
}

Vec3 Vec3::operator/(const float other)
{
	if (other == 0)
		return *this;
	return {this->x / other, this->y / other, this->z / other};
}
