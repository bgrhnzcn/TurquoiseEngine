#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "core/asset/texture.hpp"
#include "core/resources/handle.hpp"
#include "core/resources/resource_pool.hpp"

namespace trq
{

struct Material
{
	float roughness = 0.0f;
	float metalic	= 0.0f;
	TextureHandle albedo;
	TextureHandle normal;
};

using MaterialHandle  = Handle< Material >;
using MaterialStorage = ResourcePool< Material >;

} // namespace trq

#endif // MATERIAL_HPP
