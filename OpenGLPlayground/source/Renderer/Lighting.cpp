#include "Lighting.h"

Lighting::Lighting(const glm::vec3& lightPosition, const glm::vec3& lightColor)
	: m_LightPosition(lightPosition)
{
	m_Ambient = m_AmbientStrength * lightColor;
}
