#include "Core/Shapes/Sphere.hpp"

Sphere::Sphere(const glm::vec3& origin, std::shared_ptr<BXDF> bxdf, float radius)
	: Shape(origin, bxdf), m_Radius(radius) {}

bool Sphere::Intersect(const Ray& ray, SurfaceInteraction& outInteraction) const {
	glm::vec3 relativePos = ray.m_Origin - m_Origin;
	float a = glm::dot(ray.m_Direction, ray.m_Direction);
	float b = glm::dot(ray.m_Direction, relativePos);
	float c = glm::dot(relativePos, relativePos) - m_Radius * m_Radius;

	float discriminant = b * b - a * c;

	if (discriminant < 0) return false;

	float t = (-b - sqrt(discriminant)) / a;

	if (t < 0) return false;

	outInteraction.m_Position = t * ray.m_Direction + ray.m_Origin;
	outInteraction.m_Normal = glm::normalize(outInteraction.m_Position - m_Origin);
	outInteraction.m_Distance = t;
	outInteraction.m_Bxdf = m_Bxdf;

	return true;

}

bool Sphere::Intersect(const Ray& ray) const
{
	glm::vec3 relativePos = ray.m_Origin - m_Origin;
	float a = glm::dot(ray.m_Direction, ray.m_Direction);
	float b = glm::dot(ray.m_Direction, relativePos);
	float c = glm::dot(relativePos, relativePos) - m_Radius * m_Radius;

	float discriminant = b * b - a * c;

	if (discriminant < 0) { return false; }
	float t = (-b - sqrt(discriminant)) / a;

	if (t < 0) { return false; }

	return true;
}
