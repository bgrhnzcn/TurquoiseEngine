#ifndef RESOURCE_POOL_HPP
#define RESOURCE_POOL_HPP

#include <cstdint>
#include <optional>
#include <ranges>
#include <vector>

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
	auto get(HandleType handle) -> std::optional< ResourceType& >;
	auto insert(ResourceType&& entry) -> HandleType;
	auto getAllHandles() -> std::vector< HandleType >;

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
ResourcePool< ResourceType, Invalid, InitialSize >::ResourcePool()
{
	buffer_.reserve(InitialSize);
	freeIndeces_.reserve(InitialSize);
}

template < typename ResourceType, std::uint32_t Invalid,
		   std::uint32_t InitialSize >
auto ResourcePool< ResourceType, Invalid, InitialSize >::get(HandleType handle)
	-> std::optional< ResourceType& >
{
	if (!handle.isValid())
		return std::nullopt;

	std::uint32_t index = handle.getIndex();

	if (index >= buffer_.size())
		return std::nullopt;

	if (!buffer_[index].active || buffer_[index].generation != handle.getGen())
		return std::nullopt;

	return buffer_[index].entry;
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

	buffer_[index].entry  = std::move(entry);
	buffer_[index].active = true;

	return HandleType(index, buffer_[index].generation);
}

template < typename ResourceType, std::uint32_t Invalid,
		   std::uint32_t InitialSize >
auto ResourcePool< ResourceType, Invalid, InitialSize >::getAllHandles()
	-> std::vector< HandleType >
{
	return std::views::iota(0u, buffer_.size())
		   | std::views::filter([&](std::uint32_t index) -> bool
								{ return buffer_[index].active; })
		   | std::ranges::views::transform(
			   [&](std::uint32_t index)
			   { return HandleType(index, buffer_[index].generation); })
		   | std::ranges::to< std::vector >();
}

} // namespace trq

#endif // !RESOURCE_POOL_HPP
