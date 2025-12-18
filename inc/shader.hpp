#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"
#include <filesystem>

class Shader
{
  public:
	Shader(std::filesystem::path vertexPath,
		   std::filesystem::path fragmentPath);

  public:
	void use();

  public:
	unsigned int getId() const;

  private:
	std::string loadShaderFromFile(std::filesystem::path path);
	unsigned int createShader(std::filesystem::path path, GLenum type);

  private:
	unsigned int m_Id;
};

#endif
