#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

namespace trq
{

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

} // namespace trq

#endif // !TEXTURE_HPP
