#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "core/resources/storage_registry.hpp"
#include "window.hpp"
#include <memory>

namespace trq
{

class Engine
{
  public:
	auto init() -> void;
	auto run() -> void;
	auto shutdown() -> void;
	auto shouldShutdown() -> bool;
	auto getRegistry() -> StorageRegistry&;

  protected:
	virtual auto update() -> void = 0;

  private:
	bool isShutdown_ = false;
	std::unique_ptr< Window > window_;
	StorageRegistry storageRegistry_;
};

} // namespace trq

#endif // !ENGINE_HPP
