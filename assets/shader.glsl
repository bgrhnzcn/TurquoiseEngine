#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;
layout(location = 2) in vec3 aTex;

uniform mat4 u_transform;
uniform vec4 u_color;

out vec4 baseColor;

void main()
{
	vec4 newPos = u_transform * vec4(aPos, 1.0);
	gl_Position = newPos;
	baseColor = u_color;
};
