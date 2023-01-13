#type vertex
#version 460 core 

layout(location = 0) in vec3 a_Positions;
layout(location = 1) in vec3 a_TexCoords;
layout(location = 2) in vec3 a_Normals;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material u_Material;

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light u_Light;

uniform mat4 u_ProjectionView;
uniform mat4 u_Model;
uniform mat3 u_NormalMatrix;

uniform vec3 u_CameraPos;

out vec3 v_Color;

void main()
{
	gl_Position = u_ProjectionView * u_Model * vec4(a_Positions, 1.0f);

	vec3 vertexPosition = vec3(u_Model * vec4(a_Positions, 1.0f));
	vec3 Normal = u_NormalMatrix * a_Normals;

	/* Ambient lighting */	
	vec3 Ambient = u_Light.ambient * u_Material.ambient;

	/* Diffuse lighting */	
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(u_Light.position - vertexPosition);
	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 Diffuse = u_Light.diffuse * (diff * u_Material.diffuse);

	/* Specular lighting */	
	vec3 viewDir = normalize(u_CameraPos - vertexPosition);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), u_Material.shininess);
	vec3 Specular = u_Light.specular * (spec * u_Material.specular);

	v_Color = Ambient + Diffuse + Specular;
}


#type fragment
#version 460 core 

out vec4 o_Color;

in vec3 v_Color;

void main()
{
	o_Color = vec4(v_Color, 1.0f);
}