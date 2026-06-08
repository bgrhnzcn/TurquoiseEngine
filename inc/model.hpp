#ifndef MODEL_HPP
#define MODEL_HPP

#include "mesh.hpp"
#include "shader.hpp"
#include "vec2.hpp"
#include "vec3.hpp"

#include <filesystem>
#include <string_view>
#include <vector>

class Model
{
  public:
	Model(const std::filesystem::path& file);
	Model(Model&&)				   = default;
	Model(const Model&)			   = default;
	Model& operator=(Model&&)	   = default;
	Model& operator=(const Model&) = default;
	~Model()					   = default;

  public:
	void Draw(const Shader& shader) const;

  private:
	//Mesh m_mesh;

	void loadModel(const std::filesystem::path& path);
	void parseModel(std::string_view content);
	void fillBuffers(const std::vector< lib::Vec3 >& positions,
					 const std::vector< lib::Vec3 >& normals,
					 const std::vector< lib::Vec2 >& textures);
};

#endif // !MODEL_HPP
