#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <cstdint>
#include <filesystem>
#include <string>

#include "core/resources/handle.hpp"
#include "core/resources/resource_pool.hpp"

namespace trq
{

struct Texture
{
	std::uint32_t id;
	std::string type;
	std::filesystem::path path;
};

using TextureHandle	 = Handle< Texture >;
using TextureStorage = ResourcePool< Texture >;

} // namespace trq

#endif // !TEXTURE_HPP
