#pragma once
#include "Hittable.h"

class Sphere : public Hittable {
public:

	Sphere(const glm::vec3& position, float radius, const std::shared_ptr<Material>& material);
	const bool Hit(const Ray& ray, float tmin, float tmax, HitRecord& record) const override;

	glm::vec3 Position;
	float Radius = 0.0f;
	std::shared_ptr<Material> material = nullptr;

};
