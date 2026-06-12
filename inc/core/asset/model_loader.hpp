#ifndef MODEL_LOADER
#define MODEL_LOADER

#include "core/asset/model.hpp"
#include "mesh_data.hpp"
#include <assimp/scene.h>
#include <filesystem>

namespace trq
{

class ModelLoader
{
  public:
	static auto loadModel(std::filesystem::path file)
		-> std::vector< MeshData >;

  private:
	static auto loadMesh(aiMesh* mesh) -> MeshData;
};

} // namespace trq

#endif // !MODEL_LOADER
