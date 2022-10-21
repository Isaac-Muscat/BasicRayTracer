#include "Core/Ray.hpp"

Ray::Ray()
{
}

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
	: m_Origin(origin), m_Direction(glm::normalize(direction)) {

}