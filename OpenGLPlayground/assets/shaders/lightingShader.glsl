#type vertex
#version 460 core 

layout(location = 0) in vec3 a_Positions;
layout(location = 1) in vec2 a_TexCoords;
layout(location = 2) in vec3 a_Normals;

uniform mat4 u_ProjectionView;
uniform mat4 u_Model;
uniform mat3 u_NormalMatrix;

out vec3 v_Normals;
out vec3 v_FragPos;

void main()
{
	v_Normals = u_NormalMatrix * a_Normals;
	v_FragPos = vec3(u_Model * vec4(a_Positions, 1.0f));
	gl_Position = u_ProjectionView * u_Model * vec4(a_Positions, 1.0f);
}

#type fragment
#version 460 core 

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light 
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 o_Color;

in vec3 v_Normals;
in vec3 v_FragPos;

uniform Material u_Material;
uniform Light u_Light;
uniform vec3 u_CameraPos;

void main()
{
	/* Ambient lighting */
	vec3 Ambient = u_Light.ambient * u_Material.ambient; 

	/* Diffuse lighting */
	vec3 normal = normalize(v_Normals);
	vec3 lightDir = normalize(u_Light.position - v_FragPos);		// from the fragment towards the light source
	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 Diffuse = u_Light.diffuse * (u_Material.diffuse * diff);

	/* Specular lighting */
	vec3 viewDir = normalize(u_CameraPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);			// lightDir is negated first => lightSource to fragment vector
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), u_Material.shininess);
	vec3 Specular = u_Light.specular * (spec * u_Material.specular);

	vec3 result = Ambient + Diffuse + Specular;
	o_Color = vec4(result, 1.0f);
}