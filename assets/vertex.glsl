#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;
layout(location = 2) in vec3 aTex;

uniform mat4 u_model;
uniform mat3 u_normal;
uniform vec4 u_color;
uniform vec3 u_cameraDir;
uniform vec3 u_barycentric;

out vec4 vBaseColor;
out vec3 vNor;

void main()
{
	vec4 newPos = u_model * vec4(aPos, 1.0);
	vec3 newNor = u_normal * aNor;
	gl_Position = newPos;
	vBaseColor = u_color;
	vNor = newNor;
};
