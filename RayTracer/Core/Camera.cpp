#include "Core/Camera.hpp"

Camera::Camera(const glm::vec3& origin, const glm::vec3& forward, const glm::vec2& screenSize)
	: m_Origin(origin), m_Forward(glm::normalize(forward)), m_ScreenSize(screenSize), m_Up(glm::vec3(0, 1, 0)) {
	m_AspectRatio = screenSize.x / screenSize.y;
	m_Right = glm::cross(m_Forward, m_Up);
	m_TopLeftFilm = m_Origin + 0.5f * m_Forward + 0.5f * m_Up - 0.5f * m_Right * m_AspectRatio;

}

Ray Camera::GetViewRay(float u, float v) const {
	glm::vec3 endPoint = m_TopLeftFilm - m_Up * v + m_Right * u * m_AspectRatio;
	glm::vec3 dir = endPoint - m_Origin;
	Ray outRay(m_Origin, dir);
	return outRay;
}