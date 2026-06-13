#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "core/math/mat4.hpp"
#include "core/math/vec2.hpp"
#include "core/math/vec3.hpp"
#include "core/math/vec4.hpp"
#include <glad/gl.h>
#include <string>
#include <string_view>
#include <unordered_map>

namespace trq
{

class Program
{
  public:
	Program(::GLuint vertexHandler, ::GLuint fragmentHandler,
			std::string_view name);

  public:
	void use();
	::GLuint nativeHandler() const;

  public:
	template < typename T >
	int setUniform(const std::string& name, const T& value)
	{
		int uniformLocation = 0;
		if (!uniformCache_.contains(name))
		{
			uniformLocation =
				::glGetUniformLocation(this->handler_, name.c_str());
			if (uniformLocation == -1)
				return -1;
			uniformCache_.insert_or_assign(name, uniformLocation);
		}
		setUniformImpl(uniformCache_.at(name), value);
		return 0;
	}

  private:
	void setUniformImpl(int location, const int value) const;
	void setUniformImpl(int location, const float value) const;
	void setUniformImpl(int location, const bool value) const;
	void setUniformImpl(int location, const trq::Vec2 value) const;
	void setUniformImpl(int location, const trq::Vec3 value) const;
	void setUniformImpl(int location, const trq::Vec4 value) const;
	void setUniformImpl(int location, const trq::Mat4& value) const;

  private:
	const std::string name_;
	::GLuint handler_;
	std::unordered_map< std::string, int > uniformCache_;
};

} // namespace trq

#endif
