#pragma once

#include "Core/Lights/Light.hpp"

class PointLight : public Light 
{
public:
	PointLight(const glm::vec3& position, const glm::vec3& color);

	glm::vec3 CalculateIrradiance(const SurfaceInteraction& interaction) const override;
	Ray GetShadowRay(const SurfaceInteraction& interaction) const override;
public:
	glm::vec3 m_Position;
};

