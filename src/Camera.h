#pragma once
#include "glm/glm.hpp"
#include "Ray.h"

class Camera {
public:
	Camera(
		const glm::vec3& lookFrom, const glm::vec3& lookAt,
		int width, int height, float fov, float aperture, float focusDistance);
	Ray GetScreenRay(float x, float y) const;

	void Update();

	glm::vec3 Position;
	glm::vec3 Direction;
	float FocusDistance = 0.0f;
	float Fov = 0.0f;
	float Aperture = 0.0f;

	int Width = 0;
	int Height = 0;
	float Ratio = 0.0f;
	float LensRadius = 0.0f;
	glm::vec3 LowerLeftCorner;
	glm::vec3 Horizontal;
	glm::vec3 Vertical;
	glm::vec3 U;
	glm::vec3 V;
	glm::vec3 W;

private:

};

