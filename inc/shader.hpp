#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"
#include "mat4.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include <filesystem>
#include <string>
#include <unordered_map>

class Shader
{
  public:
	Shader(std::filesystem::path vertexPath,
		   std::filesystem::path fragmentPath);

  public:
	void use();

  public:
	unsigned int getId() const;

  public:
	template<typename T>
	int setUniform(std::string name, const T& value)
	{
		int uniformLocation = 0;
		if (!m_uniformCache.contains(name))
		{
			uniformLocation = glGetUniformLocation(this->m_Id, name.c_str());
			if (uniformLocation == -1)
				return -1;
			m_uniformCache.insert_or_assign(name, uniformLocation);
		}
		setUniformImpl(m_uniformCache.at(name), value);
		return 0;
	}

  private:
	std::string loadShaderFromFile(std::filesystem::path path);
	unsigned int createShader(std::filesystem::path path, GLenum type);

  private:
	void setUniformImpl(int location, const int& value) const;
	void setUniformImpl(int location, const float& value) const;
	void setUniformImpl(int location, const bool& value) const;
	void setUniformImpl(int location, const Vec2& value) const;
	void setUniformImpl(int location, const Vec3& value) const;
	void setUniformImpl(int location, const Vec4& value) const;
	void setUniformImpl(int location, const Mat4& value) const;

  private:
	unsigned int m_Id;
	std::unordered_map< std::string, int > m_uniformCache;
};

#endif
