#pragma once
#include "Material.h"

class Dielectric : public Material {
public:
	Dielectric(float refractionIndex);
	const bool Scatter(const Ray& ray, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const override;

	float RefractionIndex = 0.0f;

};

