#include "Ray.h"

Ray::Ray()
{
	Origin = glm::vec3(0.0f);
	Direction = glm::vec3(0.0f, 0.0f, -1.0f);
}

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
{
	Origin = origin;
	Direction = direction;
}

glm::vec3 Ray::At(float T) const
{
	return Origin + Direction * T;
}