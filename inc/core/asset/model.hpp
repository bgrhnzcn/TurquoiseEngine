#ifndef MODEL_HPP
#define MODEL_HPP

#include "core/asset/mesh.hpp"
#include "core/render/shader.hpp"
#include "texture.hpp"

#include <vector>

namespace trq
{

class Model
{
  public:
	void Draw(const Shader& shader) const;

  private:
	std::vector< Mesh > meshes_;
	std::vector< Texture > textures_;
};

} // namespace trq

#endif // !MODEL_HPP
