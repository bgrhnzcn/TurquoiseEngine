#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec3 a_Nor;
layout(location = 2) in vec3 a_Tex;

uniform mat4 u_model;
uniform mat4 u_projection;
out vec4 o_baseColor;

void main()
{
    vec4 newPos = u_projection * u_model * vec4(a_Pos, 1.0);
    gl_Position = newPos;
    o_baseColor = vec4(0.1f, 0.6f, 0.7f, 1.0f);
};
