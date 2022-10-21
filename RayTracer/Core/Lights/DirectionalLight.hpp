#pragma once

#include "Core/Lights/Light.hpp"

class DirectionalLight : public Light
{
public:
	DirectionalLight(const glm::vec3& direction, const glm::vec3& color);

	glm::vec3 CalculateIrradiance(const SurfaceInteraction& interaction) const override;
	Ray GetShadowRay(const SurfaceInteraction& interaction) const override;
public:
	glm::vec3 m_Direction;
};

