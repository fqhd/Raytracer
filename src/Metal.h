#pragma once
#include "glm/glm.hpp"
#include "Material.h"

class Metal : public Material {
public:

	Metal(const glm::vec3& color, float roughness = 0.1f);
	const bool Scatter(const Ray& ray, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const override;


private:

	glm::vec3 m_Color;
	float m_Roughness = 0.1f;

};

