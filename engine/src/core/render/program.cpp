#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>

#include "core/render/program.hpp"
#include "core/render/shader.hpp"
#include "core/util/logger.hpp"
#include <glad/gl.h>

using Logger = ktp::Logger;

namespace trq
{

Program::Program(::GLuint vertexHandler, ::GLuint fragmentHandler,
				 std::string_view name)
	: name_(name)
{
	const Logger& log = Logger::getLogger("Shader");

	handler_ = ::glCreateProgram();

	if (handler_ == 0)
	{
		log.error("Program {} creation failed. Check the reason.", name_);
		std::exit(1);
	}

	::glAttachShader(handler_, vertexHandler);
	::glAttachShader(handler_, fragmentHandler);

	::glLinkProgram(handler_);
	log.info("Program {} succesfully linked.", name_);
}

void Program::use()
{
	::glUseProgram(handler_);
}

::GLuint Program::nativeHandler() const
{
	return handler_;
}

void Program::setUniformImpl(int location, const int value) const
{
	::glUniform1i(location, value);
}

void Program::setUniformImpl(int location, const float value) const
{
	::glUniform1f(location, value);
}

void Program::setUniformImpl(int location, const bool value) const
{
	::glUniform1i(location, (int)value);
}

void Program::setUniformImpl(int location, const Vec2 value) const
{
	::glUniform2f(location, value.x, value.y);
}

void Program::setUniformImpl(int location, const Vec3 value) const
{
	::glUniform3f(location, value.x, value.y, value.z);
}

void Program::setUniformImpl(int location, const Vec4 value) const
{
	::glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Program::setUniformImpl(int location, const Mat4& value) const
{
	::glUniformMatrix4fv(location, 1, GL_FALSE, &value.col1.x);
}

} // namespace trq
