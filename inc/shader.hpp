#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <filesystem>
#include <string>
#include <string_view>

class Shader
{
  public:
	enum Type
	{
		FRAGMENT = GL_FRAGMENT_SHADER,
		VERTEX	 = GL_VERTEX_SHADER
	};

  public:
	[[nodiscard]]
	static auto FromFile(std::filesystem::path sourcePath, Shader::Type shaderType,
						 std::string_view name) -> Shader;
	[[nodiscard]]
	static auto FromSource(const std::string& sourceCode, Shader::Type shaderType,
						std::string_view name) -> Shader;

	public:
	auto nativeHandler() -> ::GLuint;

  private:
	[[nodiscard]]
	static auto loadShaderFromFile(std::filesystem::path path) -> std::string;

  private:
	Shader(const std::string& sourceCode, Shader::Type shaderType,
		   std::string_view name);

  private:
	auto createShader(const std::string& sourceCode) -> void;

  private:
	const std::string name_;
	const Shader::Type type_;
	::GLuint handler_;
};

#endif // !SHADER_HPP
