#type vertex
#version 460 core

layout(location = 0) in vec3 a_Positions;
layout(location = 1) in vec2 a_TexCoords;

uniform mat4 u_ProjectionView;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_ProjectionView * u_Model * vec4(a_Positions, 1.0f);
}

#type fragment
#version 460 core 

out vec4 o_Color;

uniform vec3 u_LightColor;

void main()
{
	o_Color = vec4(u_LightColor, 1.0f);
}