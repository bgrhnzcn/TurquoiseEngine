#ifndef MESH_HPP
#define MESH_HPP

#include <cstdint>
#include "core/asset/mesh_data.hpp"

namespace trq
{

class Mesh
{
  public:
	Mesh() = default;
	Mesh(const MeshData& data);

  public:
	auto draw() -> void;
	auto drawWireframe() -> void;

  private:
	std::uint32_t vbo;
};

} // namespace trq

#endif // !MESH_HPP
