#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "vec2.hpp"
#include "vec3.hpp"
#include <format>

struct Vertex
{
	lib::Vec3 pos;
	lib::Vec3 nor;
	lib::Vec2 tex;
};

template <>
struct std::formatter< Vertex >
{
	constexpr auto parse(auto& ctx) { return ctx.begin(); }

	auto format(const Vertex& vertex, auto& ctx) const
	{
		return std::format_to(
			ctx.out(), "{{\"Position\":{},\"Normal\":{},\"Texture\":{}}}",
			vertex.pos, vertex.nor, vertex.tex);
	}
};

#endif // !VERTEX_HPP
