#ifndef VEC4_HPP
#define VEC4_HPP

struct Vec4
{
	float x = 0, y = 0, z = 0, w = 0;

	Vec4();
	Vec4(float val);
	Vec4(float x, float y, float z, float w);

	float dot(const Vec4& other) const;
};

#endif // !VEC4_HPP
