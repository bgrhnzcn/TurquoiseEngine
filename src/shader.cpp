#include "shader.hpp"
#include "glad/glad.h"
#include "logger.hpp"
#include <exception>
#include <filesystem>
#include <string>
#include <string_view>

using Logger = ktp::Logger;

Shader::Shader(const std::string& sourceCode, Shader::Type shaderType,
			   std::string_view name)
	: name_(name), type_(shaderType)
{
	createShader(sourceCode);
}

auto Shader::FromFile(std::filesystem::path sourcePath, Shader::Type shaderType,
					  std::string_view name) -> Shader
{
	std::string sourceCode = Shader::loadShaderFromFile(sourcePath);
	return Shader(sourceCode, shaderType, name);
}

auto Shader::FromSource(const std::string& sourceCode, Shader::Type shaderType,
						std::string_view name) -> Shader
{
	return Shader(sourceCode, shaderType, name);
}

auto Shader::nativeHandler() -> ::GLuint { return handler_; }

auto Shader::loadShaderFromFile(std::filesystem::path path) -> std::string
{
	const Logger& log = Logger::getLogger("Shader");
	std::ifstream shaderStream;
	std::size_t fileSize = std::filesystem::file_size(path);

	std::string shaderSrc(fileSize, 0);
	shaderStream.open(path);

	if (!shaderStream.is_open())
	{
		log.error("Can't open shader file: {}", path.c_str());
		return shaderSrc;
	}

	shaderStream.read(shaderSrc.data(), fileSize);

	return shaderSrc;
}

auto Shader::createShader(const std::string& sourceCode) -> void
{
	const Logger& log = Logger::getLogger("Shader");
	handler_		  = ::glCreateShader(type_);

	if (handler_ == 0)
	{
		log.error("Shader creation failed. Please check possible errors.");
		std::terminate();
	}

	const char* source = sourceCode.c_str();

	::glShaderSource(handler_, 1, &source, nullptr);
	::glCompileShader(handler_);

	::GLint compileStatus{};
	char compileLog[512];
	::glGetShaderiv(handler_, GL_COMPILE_STATUS, &compileStatus);

	if (!compileStatus)
	{
		::glGetShaderInfoLog(handler_, 512, NULL, compileLog);
		log.error("Compiling shader: {} failed: {}", name_, compileLog);
	}
}
