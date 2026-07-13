#include "core/asset/model_loader.hpp"
#include "core/util/logger.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <cstdint>
#include <vector>

namespace trq
{

auto ModelLoader::loadModel(std::filesystem::path file)
	-> std::vector< MeshData >
{
	const ktp::Logger& logger = ktp::Logger::getLogger();
	Model model;
	::Assimp::Importer importer;

	const ::aiScene* scene = importer.ReadFile(file.string(), ::aiProcess_Triangulate);

	if (scene == nullptr)
	{
		logger.error("Loading model failed: {}. Returning empty mesh list.",
					 file.string());
		return std::vector< MeshData >();
	}

	std::vector< MeshData > meshes;
	meshes.reserve(scene->mNumMeshes);
	for (std::uint32_t i = 0; i < scene->mNumMeshes; i++)
		meshes.push_back(loadMesh(scene->mMeshes[i]));
	return meshes;
}

auto ModelLoader::loadMesh(aiMesh* mesh) -> MeshData
{
	MeshData data;

	data.vertices_.reserve(mesh->mNumVertices);
	data.indices_.reserve(mesh->mNumFaces * 3);

	auto extractedVertex = [&](std::uint32_t index) -> Vertex
	{
		Vertex vert;

		vert.pos.x = mesh->mVertices[index].x;
		vert.pos.y = mesh->mVertices[index].y;
		vert.pos.z = mesh->mVertices[index].z;

		if (mesh->HasNormals())
		{
			vert.nor.x = mesh->mNormals[index].x;
			vert.nor.y = mesh->mNormals[index].y;
			vert.nor.z = mesh->mNormals[index].z;
		}
		else
			vert.nor = {0.0f};

		if (mesh->HasTextureCoords(0))
		{
			vert.tex.x = mesh->mTextureCoords[0][index].x;
			vert.tex.y = mesh->mTextureCoords[0][index].y;
		}
		else
			vert.tex = {0.0f};

		return vert;
	};

	for (std::uint32_t i = 0; i < mesh->mNumVertices; ++i)
		data.vertices_.push_back(extractedVertex(i));

	auto extractIndex = [&](const aiFace& face) -> void
	{
		for (std::uint32_t j = 0; j < face.mNumIndices; ++j)
			data.indices_.push_back(face.mIndices[j]);
	};

	for (std::uint32_t i = 0; i < mesh->mNumFaces; ++i)
		extractIndex(mesh->mFaces[i]);

	return data;
}

} // namespace trq
