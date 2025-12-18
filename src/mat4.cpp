#include "mat4.hpp"
#include <print>

Mat4 Mat4::identity()
{
	return {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
}

void Mat4::print() const
{
	std::println("{} {} {} {}\n{} {} {} {}\n{} {} {} {}\n{} {} {} {}\n",
			  col1.x, col2.x, col3.x, col4.x,
			  col1.y, col2.y, col3.y, col4.y,
			  col1.z, col2.z, col3.z, col4.z,
			  col1.w, col2.w, col3.w, col4.w);
}
