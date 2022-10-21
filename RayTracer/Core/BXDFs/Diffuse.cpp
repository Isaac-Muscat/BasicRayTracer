#include "Diffuse.hpp"

Diffuse::Diffuse(const glm::vec3 color)
	: m_Color(color) {
}

glm::vec3 Diffuse::GetOutDirection(const glm::vec3& dirIn, const glm::vec3& normal)
{
	return RandomDirInHemisphere(normal);
}

glm::vec3 Diffuse::Evaluate(const glm::vec3& dirIn, const glm::vec3& dirOut)
{
	return m_Color;
}
