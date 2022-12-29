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
	float m_Aperture = 0.0f;

private:

	int m_Width = 0;
	int m_Height = 0;
	float m_Ratio = 0.0f;
	float m_LensRadius = 0.0f;
	glm::vec3 m_LowerLeftCorner;
	glm::vec3 m_Horizontal;
	glm::vec3 m_Vertical;
	glm::vec3 m_U;
	glm::vec3 m_V;
	glm::vec3 m_W;
};

