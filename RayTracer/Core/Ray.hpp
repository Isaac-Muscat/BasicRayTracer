#pragma once

#include "glm/glm.hpp"

class Ray {
public:
	glm::vec3 m_Origin{0};
	glm::vec3 m_Direction{0};

	Ray();
	Ray(const glm::vec3& origin, const glm::vec3& direction);
};