#include "Core/Integrator.hpp"
#include "Core/SurfaceInteraction.hpp"


Integrator::Integrator(std::shared_ptr<Camera> camera, int maxDepth)
	: m_Camera(camera), m_MaxDepth(maxDepth)
{
}

glm::vec3 Integrator::GetPixelColor(float u, float v, const Scene& scene)
{
	Ray viewRay = m_Camera->GetViewRay(u, v);
	return glm::clamp(GetIrradiance(viewRay, scene), 0.0f, 1.0f);

}

glm::vec3 Integrator::GetIrradiance(const Ray& cameraRay, const Scene& scene)
{
	Ray currentRay = cameraRay;
	SurfaceInteraction interaction;
	glm::vec3 attenuation(1.0f);

	for (int depth = 0; depth < m_MaxDepth; depth++)
	{
		if (scene.Intersect(currentRay, interaction))
		{
			interaction.ComputeInteraction();
			attenuation *= interaction.m_Attenuation;
			currentRay = interaction.m_OutRay;
		}
		else
		{
			break;
		}
		// This uses direct lighting instead of global illumination.
		/*else if (depth == 0)
		{
			return glm::vec3(0.0f);
		}
		else
		{
			return attenuation * scene.GetIrradianceFromLights(interaction);
		}*/
	}

	return attenuation * GetSkyColor(currentRay);
}

glm::vec3 Integrator::GetSkyColor(const Ray& ray) const
{
	float t = 0.5f * (glm::normalize(ray.m_Direction).y + 1.0f);
	return ((1.0f - t) * glm::vec3(1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f));
}

// GetIrradiance(const Ray& ray)
// Recursive function description:
// Parameters:			ray
// Needs access to:		objects and lights
// 
// Body:
// Get Hittable
// 
// if Light Source return its color
// if Object get ray direction and return bxdf(inray, outray) * GetIrradiance
// if specular object get reflected ray and return GetIrradiance
// if Transparent object get reflect/refracted ray and return GetIrradiance