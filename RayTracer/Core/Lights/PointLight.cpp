#include "Core/Lights/PointLight.hpp"

PointLight::PointLight(const glm::vec3& position, const glm::vec3& color) 
	: Light(color), m_Position(position) {
}

glm::vec3 PointLight::CalculateIrradiance(const SurfaceInteraction& interaction) const
{
	glm::vec3 pointToLight = m_Position - interaction.m_Position;
	return glm::clamp(glm::vec3(glm::dot(interaction.m_Normal, glm::normalize(pointToLight))), 0.0f, 1.0f) * m_Color;
}

Ray PointLight::GetShadowRay(const SurfaceInteraction& interaction) const
{
	return Ray(interaction.m_Position, m_Position - interaction.m_Position);
}
