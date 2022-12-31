#pragma once
#include "glm/glm.hpp"

struct SphereData {
    glm::vec3 position;
    float radius;
};

struct CameraData {
    glm::vec3 position;
    float focusDistance;
    float ratio;
    glm::vec3 lowerLeftColor;
    glm::vec3 horizontal;
    glm::vec3 vertical;
};

struct SceneData {
	int numSpheres;
    int width;
    int height;
	CameraData camData;
	SphereData spheres[100];
};
