#ifndef MAT4_HPP
#define MAT4_HPP

#include "vec4.hpp"

struct Mat4 {
	Vec4 col1;
	Vec4 col2;
	Vec4 col3;
	Vec4 col4;

	static Mat4 identity();

	void print() const;
};

#endif // !MAT4_HPP
