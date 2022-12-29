#pragma once
#include "World.h"
#include "Camera.h"
#include "Image.h"

class Raytracer {
public:

	Raytracer(int width, int height, const glm::vec3& camPos, const glm::vec3& lookAt, float fov, float aperture, float focusDistance, int raysPerPixel);
	void Draw();

	int m_Width = 0;
	int m_Height = 0;
	int m_PixelWidth = 0;
	Camera Camera;
	World World;
	Image Canvas;
};

