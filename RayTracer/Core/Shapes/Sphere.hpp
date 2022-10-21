#pragma once

#include "Core/Shapes/Shape.hpp"

class Sphere : public Shape {
public:
	float m_Radius;

	Sphere(const glm::vec3& origin, std::shared_ptr<BXDF> bxdf, float radius);

	bool Intersect(const Ray& ray, SurfaceInteraction& outInteraction) const override;
	bool Intersect(const Ray& ray) const override;
};