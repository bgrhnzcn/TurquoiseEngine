#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "window.hpp"

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
	bool isShutdown_;
	Window window_;
};

#endif // !ENGINE_HPP
