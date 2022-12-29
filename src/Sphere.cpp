#include "Sphere.h"
#include "Utils.h"

Sphere::Sphere(const glm::vec3& position, float radius, const std::shared_ptr<Material>& material)
	: m_Position(position), m_Radius(radius), m_Material(material) {}

const bool Sphere::Hit(const Ray& ray, float tmin, float tmax, HitRecord& record) const
{
	glm::vec3 oc = ray.Origin - m_Position;

	float a = lengthSquared(ray.Direction);
	float half_b = glm::dot(oc, ray.Direction);
	float c = lengthSquared(oc) - m_Radius * m_Radius;
	float discriminant = half_b * half_b - a * c;

	if (discriminant < 0.0f) {
		return false;
	}
	float sqrtd = sqrt(discriminant);

	float root = (-half_b - sqrtd) / a;
	if (root < tmin || tmax< root) {
		root = (-half_b + sqrtd) / a;
		if (root < tmin || tmax < root)
			return false;
	}

	record.T = root;
	record.Point = ray.At(record.T);
	record.Normal = (record.Point- m_Position) / m_Radius;
	record.Material = m_Material;
	glm::vec3 outwardNormal = (record.Point - m_Position) / m_Radius;
	record.setFaceNormal(ray, outwardNormal);
	return true;
}
