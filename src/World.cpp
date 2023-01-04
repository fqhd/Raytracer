#include "World.h"
#include "Utils.h"
#include "Lambertian.h"
#include <iostream>

void World::Add(const std::shared_ptr<Hittable>& obj)
{
	if(m_Objects.size() > 20){
		std::cout << "Cannot add more objects" << std::endl;
	}else{
		m_Objects.push_back(obj);
	}
}

glm::vec3 World::GetRayColor(const Ray& ray, int depth) const
{
	if (depth <= 0) {
		return glm::vec3(0.0f);
	}

	HitRecord record;
	if (HitWorld(ray, record)) {
		Ray scattered;
		glm::vec3 attenuation(0.0f);
		if (record.Material->Scatter(ray, record, attenuation, scattered)) {
			return attenuation * GetRayColor(scattered, depth - 1);
		}
		return glm::vec3(0.0f);
	}

	glm::vec3 unitDir = glm::normalize(ray.Direction);
	float t = 0.5f * (unitDir.y + 1.0f);
	return (1.0f - t) * glm::vec3(1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

bool World::HitWorld(const Ray& ray, HitRecord& record) const
{
	HitRecord temp;
	float closestSoFar = 1000.0f;
	bool hitAnything = false;

	for (auto& obj : m_Objects) {
		if (obj->Hit(ray, 0.001f, closestSoFar, temp)) {
			hitAnything = true;
			closestSoFar = temp.T;
			record = temp;
		}
	}

	return hitAnything;
}

void World::Clear()
{
	m_Objects.clear();
}