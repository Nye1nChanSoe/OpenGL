#type vertex
#version 460 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec3 a_Color;

out vec3 v_Color;

uniform mat4 u_ProjectionView;
uniform mat4 u_Model;

void main()
{
	v_Color = a_Color;
	gl_Position = u_ProjectionView * u_Model * vec4(a_Position, 0.0f, 1.0f);
}


#type fragment
#version 460 core

out vec4 o_Color;

in vec3 v_Color;

void main()
{
	o_Color = vec4(v_Color, 1.0f);
}