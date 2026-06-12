#ifndef MESH_DATA_HPP
#define MESH_DATA_HPP

#include <cstdint>
#include <vector>

#include "core/render/vertex.hpp"

namespace trq
{

class MeshData
{
  public:
	MeshData() noexcept									  = default;
	MeshData(const MeshData&) noexcept					  = default;
	MeshData(MeshData&&) noexcept						  = default;
	auto operator=(MeshData&&) noexcept -> MeshData&	  = default;
	auto operator=(const MeshData&) noexcept -> MeshData& = default;

  public:
	auto isValid() -> bool;

  public:
	std::vector< Vertex > vertices_;
	std::vector< std::uint32_t > indices_;
};

} // namespace trq

#endif // !MESH_DATA_HPP
