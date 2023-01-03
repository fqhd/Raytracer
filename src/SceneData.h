#pragma once
#include "glm/glm.hpp"

struct SphereData {
    glm::vec4 position;
    float radius;
};

struct CameraData {
    glm::vec4 position;
    glm::vec4 lowerLeftCorner;
	glm::vec4 horizontal;
	glm::vec4 vertical;
	glm::vec4 w;
	glm::vec4 u;
	glm::vec4 v;
	float lensRadius;
};

struct SceneData {
    int width;
    int height;
	int samplesPerPixel;
	CameraData camera;
};
