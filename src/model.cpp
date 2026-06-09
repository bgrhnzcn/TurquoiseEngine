
#include "model.hpp"
#include "logger.hpp"
#include "texture.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vertex.hpp"

#include <charconv>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <numeric>
#include <string_view>
#include <system_error>
#include <vector>

using Logger = ktp::Logger;

Model::Model(const std::filesystem::path& file) { loadModel(file); }

void Model::Draw(const Shader& shader) const { /*m_mesh.Draw(shader);*/
											   (void)shader; }

void Model::loadModel(const std::filesystem::path& path)
{
	std::ifstream file;
	const Logger& log = Logger::getLogger("ModelLoader");

	if (path.extension() != "obj")
	{
		log.warning("Unsupported model file format: {}", path.c_str());
		return;
	}

	file.open(path, std::ios::in | std::ios::binary);

	if (!file.is_open())
	{
		log.warning("It failed when opening model file. Check the path and "
					"permissions: {}",
					path.c_str());
		return;
	}

	const auto fileSize = std::filesystem::file_size(path);
	std::string content(fileSize, 0);

	file.read(content.data(), fileSize);

	parseModel(content);
}

void Model::parseModel(std::string_view content)
{
	std::vector< lib::Vec3 > positions;
	std::vector< lib::Vec3 > normals;
	std::vector< lib::Vec2 > textures;

	std::size_t pos = 0;
	while (pos < content.size())
	{
		std::size_t lineEnd = content.find('\n', pos);
		if (lineEnd == std::string_view::npos)
			lineEnd = content.size();

		std::string_view line = content.substr(pos, lineEnd - pos);

		if (line.starts_with("v "))
		{
			lib::Vec3 vec;
			const char* ptr	   = line.data() + 2;
			const char* endPtr = line.data() + line.size();

			auto res1 = std::from_chars(ptr, endPtr, vec.x);
			if (res1.ec != std::errc{})
				return;

			ptr = res1.ptr;
			while (ptr < endPtr && *ptr == ' ')
				ptr++;

			auto res2 = std::from_chars(ptr, endPtr, vec.y);
			if (res2.ec != std::errc{})
				return;

			ptr = res2.ptr;
			while (ptr < endPtr && *ptr == ' ')
				ptr++;

			auto res3 = std::from_chars(ptr, endPtr, vec.z);
			if (res3.ec != std::errc{})
				return;

			positions.push_back(vec);
		}
		else if (line.starts_with("vn "))
		{
			lib::Vec3 vec;
			const char* ptr	   = line.data() + 3;
			const char* endPtr = line.data() + line.size();

			auto res1 = std::from_chars(ptr, endPtr, vec.x);
			if (res1.ec != std::errc{})
				return;

			ptr = res1.ptr;
			while (ptr < endPtr && *ptr == ' ')
				ptr++;

			auto res2 = std::from_chars(ptr, endPtr, vec.y);
			if (res2.ec != std::errc{})
				return;

			ptr = res2.ptr;
			while (ptr < endPtr && *ptr == ' ')
				ptr++;

			auto res3 = std::from_chars(ptr, endPtr, vec.z);
			if (res3.ec != std::errc{})
				return;

			normals.push_back(vec);
		}
		else if (line.starts_with("vt "))
		{
			lib::Vec2 vec;
			const char* ptr	   = line.data() + 3;
			const char* endPtr = line.data() + line.size();

			auto res1 = std::from_chars(ptr, endPtr, vec.x);
			if (res1.ec != std::errc{})
				return;

			ptr = res1.ptr;
			while (ptr < endPtr && *ptr == ' ')
				ptr++;

			auto res2 = std::from_chars(ptr, endPtr, vec.y);
			if (res2.ec != std::errc{})
				return;

			textures.push_back(vec);
		}
		else if (line.starts_with("f "))
		{
			// Vertex vertex;
			// unsigned int positionIndex;
			// unsigned int textureIndex;
			// unsigned int normalIndex;

			// std::string_view view = line.substr(3);
			//    v/t/n
			//  f 5/1/1 3/2/1 1/3/1
		}
		pos = lineEnd + 1;
	}
}
