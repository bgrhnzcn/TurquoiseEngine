#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "glad/glad.h"
#include "mat4.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include <string>
#include <string_view>
#include <unordered_map>

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
	int setUniform(std::string name, const T& value)
	{
		int uniformLocation = 0;
		if (!uniformCache_.contains(name))
		{
			uniformLocation =
				glGetUniformLocation(this->handler_, name.c_str());
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
	void setUniformImpl(int location, const lib::Vec2 value) const;
	void setUniformImpl(int location, const lib::Vec3 value) const;
	void setUniformImpl(int location, const lib::Vec4 value) const;
	void setUniformImpl(int location, const lib::Mat4& value) const;

  private:
	const std::string name_;
	::GLuint handler_;
	std::unordered_map< std::string, int > uniformCache_;
};

#endif
