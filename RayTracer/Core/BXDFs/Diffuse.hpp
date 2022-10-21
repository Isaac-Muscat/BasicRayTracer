#pragma once

#include "Core/BXDFs/BXDF.hpp"
#include "Core/Random.hpp"

class Diffuse : public BXDF {
public:
	Diffuse(const glm::vec3 color);

	glm::vec3 GetOutDirection(const glm::vec3& dirIn, const glm::vec3& normal) override;
	glm::vec3 Evaluate(const glm::vec3& dirIn, const glm::vec3& dirOut) override;
private:
	glm::vec3 m_Color;
};

