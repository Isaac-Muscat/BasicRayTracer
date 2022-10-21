#pragma once
#include <memory>

#include "glm/glm.hpp"

#include "Core/BXDFs/BXDF.hpp"
#include "Core/Ray.hpp"

class SurfaceInteraction {
	static const float OUT_RAY_NORMAL_OFFSET;
public:
	glm::vec3 m_Position;
	glm::vec3 m_Normal;
	float m_Distance;
	glm::vec3 m_InDir;
	Ray m_OutRay;
	glm::vec3 m_Attenuation;
	std::shared_ptr<BXDF> m_Bxdf;

	SurfaceInteraction();

	void ComputeInteraction();
};