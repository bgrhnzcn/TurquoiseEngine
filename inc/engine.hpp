#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "window.hpp"
#include <memory>

class Engine
{
  public:
	auto init() -> void;
	auto run() -> void;
	auto shutdown() -> void;
	auto shouldShutdown() -> bool;

  protected:
	virtual auto update() -> void = 0;

  private:
	bool isShutdown_ = false;
	std::unique_ptr<Window> window_;
};

#endif // !ENGINE_HPP
