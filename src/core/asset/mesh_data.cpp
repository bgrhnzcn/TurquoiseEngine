#include "core/asset/mesh_data.hpp"

auto trq::MeshData::isValid() -> bool
{
	return (!vertices_.empty() && !indices_.empty());
}
