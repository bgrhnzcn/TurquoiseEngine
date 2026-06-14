#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "core/resources/storage_registry.hpp"
#include "window.hpp"
#include <imgui.h>
#include <memory>

namespace trq
{

class Engine
{
  public:
	Engine() = default;
	Engine(const Engine& other)					   = delete;
	auto operator=(const Engine& other) -> Engine& = delete;

  public:
	auto init() -> void;
	auto run() -> void;
	auto shutdown() -> void;

	[[nodiscard]]
	auto shouldShutdown() -> bool;
	[[nodiscard]]
	auto getRegistry() -> StorageRegistry&;
	[[nodiscard]]
	auto getWindow() -> Window&;

  private:
	bool isShutdown_ = false;
	std::unique_ptr< Window > window_;
	ImGuiContext* imgui_ = nullptr;
	StorageRegistry storageRegistry_;
};

} // namespace trq

#endif // !ENGINE_HPP
