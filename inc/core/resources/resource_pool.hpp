#ifndef RESOURCE_POOL_HPP
#define RESOURCE_POOL_HPP

#include <cstdint>
#include <vector>

#include "core/asset/mesh.hpp"
#include "core/asset/mesh_data.hpp"
#include "core/asset/texture.hpp"
#include "core/resources/handle.hpp"
#include "core/resources/ipool.hpp"

namespace trq
{

template < typename ResourceType, std::uint32_t Invalid = 0xFFFFFFFF,
		   std::uint32_t InitialSize = 128 >
class ResourcePool : public IPool
{
  public:
	using HandleType = Handle< ResourceType, Invalid >;

  public:
	auto get(HandleType handle) -> ResourceType*;
	auto insert(ResourceType&& entry) -> HandleType;

	ResourcePool();
	ResourcePool(const ResourcePool& other)						   = delete;
	auto operator=(const ResourcePool& other) -> ResourcePool&	   = delete;
	ResourcePool(ResourcePool&& other) noexcept					   = default;
	auto operator=(ResourcePool&& other) noexcept -> ResourcePool& = default;

  private:
	struct Entry
	{
		Entry()									   = default;
		Entry(Entry&&) noexcept					   = default;
		auto operator=(Entry&&) noexcept -> Entry& = default;

		ResourceType entry;
		std::uint32_t generation = 0;
		bool active				 = false;
	};

  private:
	std::vector< Entry > buffer_;
	std::vector< std::uint32_t > freeIndeces_;
};


template < typename ResourceType, std::uint32_t Invalid,
		   std::uint32_t InitialSize >
ResourcePool<ResourceType, Invalid, InitialSize>::ResourcePool()
{
	buffer_.reserve(InitialSize);
	freeIndeces_.reserve(InitialSize);
}

template < typename ResourceType, std::uint32_t Invalid,
		   std::uint32_t InitialSize >
auto ResourcePool< ResourceType, Invalid, InitialSize >::get(HandleType handle)
	-> ResourceType*
{
	if (!handle.isValid())
		return nullptr;

	std::uint32_t index = handle.getIndex();

	if (index >= buffer_.size())
		return nullptr;

	if (!buffer_[index].active || buffer_[index].generation != handle.getGen())
		return nullptr;

	return &buffer_[index].entry;
}

template < typename ResourceType, std::uint32_t Invalid,
		   std::uint32_t InitialSize >
auto ResourcePool< ResourceType, Invalid, InitialSize >::insert(
	ResourceType&& entry) -> HandleType
{
	std::uint32_t index;

	if (freeIndeces_.empty())
	{
		index = static_cast< std::uint32_t >(buffer_.size());
		buffer_.push_back(Entry());
	}
	else
	{
		index = freeIndeces_.back();
		freeIndeces_.pop_back();
	}

	buffer_[index].entry  = entry;
	buffer_[index].active = true;

	return HandleType(index, buffer_[index].generation);
}

using MeshStorage	  = trq::ResourcePool< trq::Mesh, 0xFFFFFFFF >;
using MeshDataStorage = trq::ResourcePool< trq::MeshData, 0xFFFFFFFF >;
using TextureStorage  = trq::ResourcePool< trq::Texture, 0xFFFFFFFF >;

} // namespace trq

#endif // !RESOURCE_POOL_HPP
