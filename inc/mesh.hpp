#ifndef MESH_HPP
#define MESH_HPP

#include "texture.hpp"
#include "vertex.hpp"

#include <cstdint>
#include <vector>

class Mesh
{
  public:
	Mesh();
	Mesh(std::vector< Vertex >&& vertices,
		 std::vector< std::uint32_t >&& indices,
		 std::vector< Texture >&& textures);
	Mesh(Mesh&&)				 = default;
	Mesh(const Mesh&)			 = default;
	Mesh& operator=(Mesh&&)		 = default;
	Mesh& operator=(const Mesh&) = default;
	~Mesh()						 = default;

  private:
	std::vector< Vertex > vertices_;
	std::vector< std::uint32_t > indices_;
	std::vector< Texture > textures_;
};

#endif // !MESH_HPP
