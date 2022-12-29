#pragma once
#include "glm/glm.hpp"

class Ray {
public:
	Ray();
	Ray(const glm::vec3& origin, const glm::vec3& direction);
	glm::vec3 At(float T) const;

	glm::vec3 Origin;
	glm::vec3 Direction;
};

