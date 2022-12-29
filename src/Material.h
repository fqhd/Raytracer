#pragma once
#include "Ray.h"
#include "Hittable.h"

struct HitRecord;

class Material {
public:
	virtual const bool Scatter(const Ray& ray, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const = 0;
};

