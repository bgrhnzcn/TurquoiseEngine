#include "vec4.hpp"

Vec4::Vec4() : x(0), y(0), z(0), w(0) {}
Vec4::Vec4(float val) : x(val), y(val), z(val), w(val) {}
Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

float Vec4::dot(const Vec4& other) const
{
	return ((this->x * other.x) + (this->y * other.y) + (this->z * other.z)
			+ (this->w * other.w));
}
