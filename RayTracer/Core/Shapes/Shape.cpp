#include "Shape.hpp"

Shape::Shape(const glm::vec3& origin, std::shared_ptr<BXDF> bxdf)
	: m_Origin(origin), m_Bxdf(bxdf) {}
