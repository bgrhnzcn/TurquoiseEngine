#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>

#include "glad/glad.h"
#include "logger.hpp"
#include "shader.hpp"

std::string Shader::loadShaderFromFile(std::filesystem::path path)
{
	std::fstream shaderStream(path);
	std::string line;
	std::string shaderSrc;

	while (std::getline(shaderStream, line))
	{
		shaderSrc += line;
		shaderSrc += '\n';
	}
	return shaderSrc;
}

unsigned int Shader::createShader(std::filesystem::path path, GLenum type)
{
	unsigned int shader = glCreateShader(type);
	int compileStatus;
	char errBuff[512];

	std::string shaderSource = loadShaderFromFile(path);

	const char* source = shaderSource.c_str();

	if (shader == 0)
	{
		Logger::error("Error while compiling shader: {}", path.c_str());
	}

	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

	if (!compileStatus)
	{
		glGetShaderInfoLog(shader, 512, NULL, errBuff);
		Logger::error("Compiling file: {} failed: {}", path.c_str(), errBuff);
	}

	return shader;
}

Shader::Shader(std::filesystem::path vertexPath,
			   std::filesystem::path fragmentPath)
{
	unsigned int vertexId	= createShader(vertexPath, GL_VERTEX_SHADER);
	unsigned int fragmentId = createShader(fragmentPath, GL_FRAGMENT_SHADER);

	unsigned int shader = glCreateProgram();

	if (shader == 0)
	{
		std::exit(1);
	}

	glAttachShader(shader, vertexId);
	glAttachShader(shader, fragmentId);

	glLinkProgram(shader);
	Logger::info("Shader succesfully compiled.");

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
	m_Id = shader;
}

void Shader::use() { glUseProgram(m_Id); }

unsigned int Shader::getId() const { return m_Id; }

void Shader::setUniformImpl(int location, const int& value) const
{
	glUniform1i(location, value);
}

void Shader::setUniformImpl(int location, const float& value) const
{
	glUniform1f(location, value);
}

void Shader::setUniformImpl(int location, const bool& value) const
{
	glUniform1i(location, (int)value);
}

void Shader::setUniformImpl(int location, const Vec2& value) const
{
	glUniform2f(location, value.x, value.y);
}

void Shader::setUniformImpl(int location, const Vec3& value) const
{
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::setUniformImpl(int location, const Vec4& value) const
{
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::setUniformImpl(int location, const Mat4& value) const
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &value.col1.x);
}
