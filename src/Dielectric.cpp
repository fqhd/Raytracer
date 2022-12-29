#include "Dielectric.h"
#include "Utils.h"

static float reflectance(float cosTheta, float refractionIndex) {
    float r0 = (1.0f - refractionIndex) / (1.0f + refractionIndex);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * pow((1.0f - cosTheta), 5.0f);
}

Dielectric::Dielectric(float refractionIndex)
	: m_RefractionIndex(refractionIndex) {}

const bool Dielectric::Scatter(const Ray& ray, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const
{
    attenuation = glm::vec3(1.0f);
    float refractionRatio = record.frontFace ? (1.0f / m_RefractionIndex) : m_RefractionIndex;

    glm::vec3 unitDir = glm::normalize(ray.Direction);
    float cosTheta = glm::min(glm::dot(-unitDir, record.Normal), 1.0f);
    float sinTheta = glm::sqrt(1.0f - cosTheta * cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0f;
    glm::vec3 direction;

    if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomFloatU()) {
        direction = glm::reflect(unitDir, record.Normal);
    } else {
        direction = glm::refract(unitDir, record.Normal, refractionRatio);
    }

    scattered = Ray(record.Point, direction);
    return true;
}