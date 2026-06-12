#include "core/asset/mesh.hpp"

namespace trq
{

Mesh::Mesh(const MeshData& data)
{
	(void)data;
	// TODO: OpenGL BufferGen.
}

auto Mesh::draw() -> void
{
	// TODO: Draw corretly with shader.
}

auto Mesh::drawWireframe() -> void
{
	// TODO: Debug wireframe draw.
}

} // namespace trq
