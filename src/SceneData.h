#pragma once
#include "glm/glm.hpp"

#define MAX_SPHERES 20

struct MaterialData {
	glm::vec3 albedo;
	float ir;
	float roughness;
	int type;
};

struct SphereData {
	MaterialData material;
    glm::vec3 position;
    float radius;
	int visible;
};

struct CameraData {
    glm::vec3 position;
    glm::vec3 lowerLeftCorner;
	glm::vec3 horizontal;
	glm::vec3 vertical;
	glm::vec3 w;
	glm::vec3 u;
	glm::vec3 v;
	float lensRadius;
};

struct HittableList {
	SphereData spheres[MAX_SPHERES];
};

struct SceneData {
    int width;
    int height;
	CameraData camera;
	HittableList list;
};
