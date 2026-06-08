#version 330 core

in vec4 baseColor;
in vec3 vNor;

out vec4 FragColor;

void main()
{
	FragColor = vec4(vNor, 1.f);
};

