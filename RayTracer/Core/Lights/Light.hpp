#pragma once

#include "glm/glm.hpp"

#include "Core/SurfaceInteraction.hpp"

class Light {
public:
	Light(const glm::vec3& color)
		: m_Color(color) {}

	virtual glm::vec3 CalculateIrradiance(const SurfaceInteraction& interaction) const = 0;
	virtual Ray GetShadowRay(const SurfaceInteraction& interaction) const = 0;
public:
	glm::vec3 m_Color;
};

