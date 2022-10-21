#pragma once

#include "glm/glm.hpp"

#include "Core/Ray.hpp"

class Camera {
public:

	Camera(const glm::vec3& origin, const glm::vec3& forward, const glm::vec2& screenSize);
	Ray GetViewRay(float u, float v) const;

private:
	glm::vec3 m_Origin;
	glm::vec3 m_Forward;
	glm::vec3 m_Right;
	glm::vec3 m_Up;
	glm::vec2 m_ScreenSize;
	glm::vec3 m_TopLeftFilm;
	float m_AspectRatio;

};