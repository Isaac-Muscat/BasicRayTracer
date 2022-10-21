#pragma once

#include "Core/BXDFs/BXDF.hpp"
class Dielectric :
	public BXDF
{
public:
	Dielectric();

	glm::vec3 GetOutDirection(const glm::vec3& dirIn, const glm::vec3& normal) override;
	glm::vec3 Evaluate(const glm::vec3& dirIn, const glm::vec3& dirOut) override;
};

