#pragma once
#include <memory>
#include <vector>

#include "Core/Camera.hpp"
#include "Core/Shapes/Shape.hpp"
#include "Core/Lights/Light.hpp"
#include "Core/SurfaceInteraction.hpp"

class Scene {
public:
	Scene();

	bool Intersect(const Ray& ray, SurfaceInteraction& interaction) const;
	bool Intersect(const Ray& ray) const;
	glm::vec3 GetIrradianceFromLights(const SurfaceInteraction& interaction) const;

private:
	std::vector<std::shared_ptr<Shape>> m_Objects;
	std::vector<std::shared_ptr<Light>> m_Lights;
};