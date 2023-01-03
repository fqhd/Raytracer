#pragma once
#include "glm/glm.hpp"
#include "Ray.h"
#include <vector>
#include "Sphere.h"
#include <memory>

class World {
public:

	glm::vec3 GetRayColor(const Ray& ray, int depth = 50) const;
	void Add(const std::shared_ptr<Hittable>& obj);
	void Clear();

	std::vector<std::shared_ptr<Hittable>> Objects;

private:

	bool HitWorld(const Ray& ray, HitRecord& record) const;


};

