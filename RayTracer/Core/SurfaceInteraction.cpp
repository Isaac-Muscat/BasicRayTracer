#include <cassert>

#include "Core/SurfaceInteraction.hpp"


const float SurfaceInteraction::OUT_RAY_NORMAL_OFFSET = 0.00001f;

SurfaceInteraction::SurfaceInteraction()
	: m_Position(0), m_Normal(0), m_Distance(0), 
	m_Attenuation(0), m_InDir(0), m_OutRay() {}

void SurfaceInteraction::ComputeInteraction() {
	m_OutRay.m_Origin = m_Position + m_Normal * OUT_RAY_NORMAL_OFFSET;
	m_OutRay.m_Direction = m_Bxdf->GetOutDirection(m_InDir, m_Normal);
	m_Attenuation = m_Bxdf->Evaluate(m_InDir, m_OutRay.m_Direction);
}