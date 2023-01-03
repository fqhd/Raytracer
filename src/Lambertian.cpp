#include "Lambertian.h"
#include "Utils.h"

Lambertian::Lambertian(const glm::vec3& color)
	: Color(color)
{}

const bool Lambertian::Scatter(const Ray& ray, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const
{
	glm::vec3 scatterDirection = record.Normal + randomUnitVector();
	if (nearZero(scatterDirection)) {
		scatterDirection = record.Normal;
	}
	scattered = Ray(record.Point, scatterDirection);
	attenuation = Color;
	return true;
}