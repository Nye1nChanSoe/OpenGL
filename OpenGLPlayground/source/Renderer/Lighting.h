#pragma once

#include "glm/glm.hpp"

class Lighting
{
public:
	Lighting(const glm::vec3& lightPosition, const glm::vec3& lightColor = {1.0f, 1.0f, 1.0f});

	const glm::vec3& GetLightPosition() const { return m_LightPosition; }
	void SetLightPosition(const glm::vec3& lightPosition) { m_LightPosition = lightPosition; }

	const glm::vec3& GetAmbientLight() const { return m_Ambient; }
	void SetAmbientLight(const glm::vec3& ambient) { m_Ambient = ambient; }

	const glm::vec3& GetDiffuseLight() const { return m_Diffuse; }
	void SetDiffuseLight(const glm::vec3& diffuse) { m_Diffuse = diffuse; }

	const glm::vec3& GetSpecularLight() const { return m_Ambient; }
	void SetSpecularLight(const glm::vec3& specular) { m_Ambient = specular; }

private:
	glm::vec3 m_Ambient;
	glm::vec3 m_Diffuse;
	glm::vec3 m_Specular;

	glm::vec3 m_LightPosition; 

	float m_AmbientStrength = 0.1f;
	float m_SpecularStrength = 0.5f;
};
