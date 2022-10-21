#pragma once

#include <vector>
#include <memory>

#include "core/Scene.hpp"
#include "Core/Camera.hpp"

class Integrator {
public:

	Integrator(std::shared_ptr<Camera> camera, int maxDepth);

	glm::vec3 GetPixelColor(float u, float v, const Scene& scene);
	glm::vec3 GetIrradiance(const Ray& cameraRay, const Scene& scene);
	

private:
	glm::vec3 GetSkyColor(const Ray& ray) const;

	std::shared_ptr<Camera> m_Camera;
	const int m_MaxDepth;
};