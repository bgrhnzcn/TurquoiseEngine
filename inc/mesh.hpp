#ifndef MESH_HPP
#define MESH_HPP

#include "shader.hpp"
#include "texture.hpp"
#include "vertex.hpp"

#include <cstdint>
#include <vector>

class Mesh
{
  public:
	Mesh();
	Mesh(Mesh&&)				 = default;
	Mesh(const Mesh&)			 = default;
	Mesh& operator=(Mesh&&)		 = default;
	Mesh& operator=(const Mesh&) = default;
	~Mesh()						 = default;

  public:
	void Draw(const Shader& shader) const;
	void setupMesh(const std::vector< Vertex >& vertices,
				   const std::vector< std::uint32_t >& indices,
				   const std::vector< Texture > textures);

  private:
	std::vector< Vertex > m_vertices;
	std::vector< std::uint32_t > m_indices;
	std::vector< Texture > m_textures;
};

#endif // !MESH_HPP
