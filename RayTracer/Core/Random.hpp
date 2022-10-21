#pragma once

#include <random>

#include "glm/glm.hpp"

inline float RandomUnitFloat();

glm::vec3 RandomDirInSphere();

glm::vec3 RandomDirInHemisphere(const glm::vec3 normal);

