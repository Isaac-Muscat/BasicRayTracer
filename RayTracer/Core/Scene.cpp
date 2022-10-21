#include "Scene.hpp"

#include "Core/BXDFs/Diffuse.hpp"
#include "Core/Shapes/Sphere.hpp"
#include "Core/Lights/PointLight.hpp"
#include "Core/Lights/DirectionalLight.hpp"
#include "Core/BXDFs/Specular.hpp"

Scene::Scene()
{
	m_Objects.push_back(std::make_shared<Sphere>(glm::vec3(1, 0, -3), std::make_shared<Diffuse>(glm::vec3(0.2f, 0.2f, 0.8f)), 0.5));
	m_Objects.push_back(std::make_shared<Sphere>(glm::vec3(-1, 0, -3), std::make_shared<Diffuse>(glm::vec3(0.2f, 0.8f, 0.2f)), 0.5));
	m_Objects.push_back(std::make_shared<Sphere>(glm::vec3(-2, 1, -3), std::make_shared<Diffuse>(glm::vec3(0.8f, 0.2f, 0.2f)), 0.5));
	m_Objects.push_back(std::make_shared<Sphere>(glm::vec3(-1, 2, -4), std::make_shared<Specular>(), 0.5));
	m_Objects.push_back(std::make_shared<Sphere>(glm::vec3(1, 1, -4), std::make_shared<Specular>(), 0.5));
	m_Objects.push_back(std::make_shared<Sphere>(glm::vec3(2, 1, -3), std::make_shared<Specular>(), 0.5));
	m_Objects.push_back(std::make_shared<Sphere>(glm::vec3(0, -100.5, -1), std::make_shared<Diffuse>(glm::vec3(0.2f, 0.2f, 0.2f)), 100));
	//m_Lights.push_back(std::make_shared<PointLight>(glm::vec3(5, 5, -5), glm::vec3(1.0f)));
	m_Lights.push_back(std::make_shared<DirectionalLight>(glm::vec3(-1, -1, -1), glm::vec3(1.0f)));
	
}

bool Scene::Intersect(const Ray& ray, SurfaceInteraction& interaction) const
{
	SurfaceInteraction currentInteraction, closestInteraction;
	bool hit = false;
	float closestDistance = 999999;
	for (const auto& o : m_Objects) {
		if (o->Intersect(ray, currentInteraction) && currentInteraction.m_Distance < closestDistance) {
			closestInteraction = currentInteraction;
			closestDistance = currentInteraction.m_Distance;
			hit = true;
		}
	}
	if (hit) interaction = closestInteraction;
	return hit;
}

bool Scene::Intersect(const Ray& ray) const
{
	for (const auto& o : m_Objects) {
		if (o->Intersect(ray)) {
			return true;
		}
	}
	return false;
}

glm::vec3 Scene::GetIrradianceFromLights(const SurfaceInteraction& interaction) const
{
	glm::vec3 totalIrradiance(0.0f);
	for (auto& light : m_Lights) {
		Ray shadowRay = light->GetShadowRay(interaction);
		if (!Intersect(shadowRay)) {
			totalIrradiance += light->CalculateIrradiance(interaction);
		}
	}
	return totalIrradiance;
}
