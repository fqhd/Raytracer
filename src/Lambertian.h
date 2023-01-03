#pragma once
#include "Material.h"

class Lambertian : public Material {
public:

	Lambertian(const glm::vec3& color);
	const bool Scatter(const Ray& ray, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const override;

	glm::vec3 Color;

};

