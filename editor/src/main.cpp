#include "core/engine.hpp"
#include "core/util/logger.hpp"
#include <filesystem>

using Logger = ktp::Logger;

#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR ",/"
#endif

int main()
{
	std::filesystem::path root(PROJECT_ROOT_DIR"/assets");
	Logger::getLogger("MAIN").info("Writen Path: {}, Current Path: {}",
		root.string(), std::filesystem::current_path().string());

	trq::Engine eng;
	eng.init(root.string());
	eng.run(root.string());
	return 0;
}
