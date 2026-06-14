#include "core/engine.hpp"
#include "core/util/logger.hpp"

using Logger = ktp::Logger;

int main()
{
	trq::Engine eng;
	eng.init();
	eng.run();
	return 0;
}
