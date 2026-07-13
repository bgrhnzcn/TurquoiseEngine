#ifndef MESH_HPP
#define MESH_HPP

#include "core/asset/mesh_data.hpp"
#include "core/resources/handle.hpp"
#include "core/resources/resource_pool.hpp"
#include <cstdint>

namespace trq
{

class Mesh
{
  public: // Default
	Mesh() = default;
	Mesh(const MeshData& data);

  public: // Copy
	Mesh(const Mesh& other)					   = delete;
	auto operator=(const Mesh& other) -> Mesh& = delete;

  public: // Move
	Mesh(Mesh&& data) noexcept;
	auto operator=(Mesh&& other) noexcept -> Mesh&;

  public: // Destructer
	~Mesh();

  public:
	auto draw() -> void;
	auto drawWireframe() -> void;

  private:
	std::uint32_t vao_;
	std::uint32_t vbo_;
	std::uint32_t ebo_;
	std::size_t elemCount_;
};

using MeshHandle  = Handle< Mesh >;
using MeshStorage = ResourcePool< Mesh >;

} // namespace trq

#endif // !MESH_HPP
