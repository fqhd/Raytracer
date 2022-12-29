#pragma once
#include "glm/glm.hpp"
#include "Ray.h"
#include <vector>
#include "Sphere.h"
#include <memory>

class World {
public:

	glm::vec3 GetRayColor(const Ray& ray, int depth = 50) const;
	void AddSphere(const glm::vec3& position, float radius, const std::shared_ptr<Material>& material);
	void Clear();

private:

	bool HitWorld(const Ray& ray, HitRecord& record) const;

	std::vector<std::unique_ptr<Sphere>> m_Objects;

};

