#include "Dielectric.hpp"

Dielectric::Dielectric()
{
}

glm::vec3 Dielectric::GetOutDirection(const glm::vec3& dirIn, const glm::vec3& normal)
{
    return glm::vec3();
}

glm::vec3 Dielectric::Evaluate(const glm::vec3& dirIn, const glm::vec3& dirOut)
{
    return glm::vec3(1.0f);
}
