#pragma once

#include <memory>

#include "Core/Ray.hpp"
#include "Core/SurfaceInteraction.hpp"
#include "Core/BXDFs/BXDF.hpp"

class Shape {
public:
	glm::vec3 m_Origin;
	std::shared_ptr<BXDF> m_Bxdf;

	Shape(const glm::vec3& origin, std::shared_ptr<BXDF> bxdf);

	virtual bool Intersect(const Ray& ray, SurfaceInteraction& outInteraction) const = 0;
	virtual bool Intersect(const Ray& ray) const = 0;
};