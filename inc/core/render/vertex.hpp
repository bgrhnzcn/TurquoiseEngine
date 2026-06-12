#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "core/math/vec3.hpp"
#include <format>

namespace trq
{

struct Vertex
{
	Vec3 pos;
	Vec3 nor;
	Vec3 tex;

	auto toString() const -> std::string;
};

} // namespace trq

template <>
struct std::formatter< trq::Vertex >
{
	constexpr auto parse(auto& ctx)
	{
		return ctx.begin();
	}

	auto format(const trq::Vertex& vertex, auto& ctx) const
	{
		return std::format_to(
			ctx.out(), "{{\"Position\":{},\"Normal\":{},\"Texture\":{}}}",
			vertex.pos, vertex.nor, vertex.tex);
	}
};

#endif // !VERTEX_HPP
