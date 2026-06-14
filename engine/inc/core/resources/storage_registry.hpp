#ifndef STORAGE_REGISTRY_HPP
#define STORAGE_REGISTRY_HPP

#include "ipool.hpp"
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace trq
{

class StorageRegistry
{
  private:
	std::unordered_map< std::type_index, std::unique_ptr< IPool > > storages_;

  public:
	template < typename StorageType >
	auto get() -> StorageType&;
};

template < typename StorageType >
auto StorageRegistry::get() -> StorageType&
{
	auto typeIndex = std::type_index(typeid(StorageType));

	auto it = storages_.find(typeIndex);

	if (it == storages_.end())
		storages_[typeIndex] = std::make_unique< StorageType >();

	return static_cast< StorageType& >(*storages_[typeIndex]);
}

} // namespace trq

#endif // !STORAGE_REGISTRY_HPP
