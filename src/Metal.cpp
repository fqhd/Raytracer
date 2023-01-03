#include "Metal.h"
#include "Utils.h"


Metal::Metal(const glm::vec3& color, float roughness)
	: Color(color)
{
	Roughness = glm::clamp(roughness, 0.0f, 1.0f);
}

const bool Metal::Scatter(const Ray& ray, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const
{
	glm::vec3 reflected = glm::reflect(ray.Direction, record.Normal);
	scattered = Ray(record.Point, reflected + randomInUnitSphere() * Roughness);
	attenuation = Color;
	return glm::dot(scattered.Direction, record.Normal) > 0.0f;
}