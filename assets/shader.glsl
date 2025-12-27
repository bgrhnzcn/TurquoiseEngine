#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;
layout(location = 2) in vec3 aTex;

uniform mat4 u_transforms;

void main()
{
	vec4 newPos = transforms * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	gl_Position = newPos;
};
