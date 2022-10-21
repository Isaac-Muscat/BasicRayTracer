#include "Core/Lights/DirectionalLight.hpp"

DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color)
	: Light(color), m_Direction(glm::normalize(direction))
{
}

glm::vec3 DirectionalLight::CalculateIrradiance(const SurfaceInteraction& interaction) const
{
	return glm::clamp(glm::vec3(glm::dot(interaction.m_Normal, -m_Direction)), 0.0f, 1.0f) * m_Color;
}

Ray DirectionalLight::GetShadowRay(const SurfaceInteraction& interaction) const
{
	return Ray(interaction.m_Position, -m_Direction);
}
