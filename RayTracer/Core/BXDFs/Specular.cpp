#include "Specular.hpp"

Specular::Specular() {}

glm::vec3 Specular::GetOutDirection(const glm::vec3& dirIn, const glm::vec3& normal)
{
	return 2.0f * normal - dirIn;
}

glm::vec3 Specular::Evaluate(const glm::vec3& dirIn, const glm::vec3& dirOut)
{
	return glm::vec3(1.0f);
}
