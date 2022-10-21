#include "Random.hpp"

inline float RandomUnitFloat()
{
	static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
	static std::mt19937 generator;
	return dist(generator);
}

glm::vec3 RandomDirInSphere()
{
	glm::vec3 dir(0.0f);
	do {
		dir = 2.0f * (glm::vec3(RandomUnitFloat(), RandomUnitFloat(), RandomUnitFloat()) - 0.5f);

	} while (dir.length() > 1);
	return glm::normalize(dir);
}

glm::vec3 RandomDirInHemisphere(const glm::vec3 normal)
{
	glm::vec3 dir(0.0f);
	do {
		dir = 2.0f * (glm::vec3(RandomUnitFloat(), RandomUnitFloat(), RandomUnitFloat()) - 0.5f);

	} while (glm::dot(normal, dir) < 0 && dir.length() > 1);

	return glm::normalize(dir);
}

