#pragma once
#include "glm/glm.hpp"
#include "Ray.h"
#include <vector>
#include "Sphere.h"
#include <memory>

class Raytracer;

class World {
public:

	friend class Raytracer;

	glm::vec3 GetRayColor(const Ray& ray, int depth = 10) const;
	void Add(const std::shared_ptr<Hittable>& obj);
	void Clear();

private:

	bool HitWorld(const Ray& ray, HitRecord& record) const;
	std::vector<std::shared_ptr<Hittable>> m_Objects;


};

