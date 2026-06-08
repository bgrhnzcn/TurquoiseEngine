#include "shader.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>

#include "glad/glad.h"
#include "logger.hpp"
#include "program.hpp"

using Logger = ktp::Logger;

Program::Program(::GLuint vertexHandler, ::GLuint fragmentHandler,
				 std::string_view name)
	: name_(name)
{
	const Logger& log = Logger::getLogger("Shader");

	handler_ = glCreateProgram();

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

void Program::use() { ::glUseProgram(handler_); }

::GLuint Program::nativeHandler() const { return handler_; }

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

void Program::setUniformImpl(int location, const lib::Vec2 value) const
{
	::glUniform2f(location, value.x, value.y);
}

void Program::setUniformImpl(int location, const lib::Vec3 value) const
{
	::glUniform3f(location, value.x, value.y, value.z);
}

void Program::setUniformImpl(int location, const lib::Vec4 value) const
{
	::glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Program::setUniformImpl(int location, const lib::Mat4& value) const
{
	::glUniformMatrix4fv(location, 1, GL_FALSE, &value.col1.x);
}
