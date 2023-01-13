#type vertex
#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_ProjectionView;
uniform mat4 u_Model;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_ProjectionView * u_Model * vec4(a_Position, 1.0f);
}


#type fragment
#version 460 core

out vec4 o_Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	o_Color = texture(u_Texture, v_TexCoord);
}