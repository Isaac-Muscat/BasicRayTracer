#pragma once

#include "glm/glm.hpp"

#include "Core/Ray.hpp"

class BXDF {
public:

	virtual glm::vec3 GetOutDirection(const glm::vec3& dirIn, const glm::vec3& normal) = 0;
	virtual glm::vec3 Evaluate(const glm::vec3& dirIn, const glm::vec3& dirOut) = 0;
};