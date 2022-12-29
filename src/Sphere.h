#pragma once
#include "Hittable.h"

class Sphere : public Hittable {
public:

	Sphere(const glm::vec3& position, float radius, const std::shared_ptr<Material>& material);
	const bool Hit(const Ray& ray, float tmin, float tmax, HitRecord& record) const override;

private:

	glm::vec3 m_Position;
	float m_Radius = 0.0f;
	std::shared_ptr<Material> m_Material = nullptr;

};
