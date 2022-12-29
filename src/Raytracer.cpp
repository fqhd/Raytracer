#include "Raytracer.h"

Raytracer::Raytracer(int width, int height, const glm::vec3& camPos, const glm::vec3& lookAt, float fov, float aperture, float focusDistance, int raysPerPixel)
	: Camera(camPos, lookAt, glm::vec3(0.0f, 1.0f, 0.0f), width, height, fov, aperture, focusDistance), Canvas(width, height),
	m_Width(width), m_Height(height)
{
	m_PixelWidth = (int)sqrt(raysPerPixel);
}

void Raytracer::Draw()
{
	for (int y = 0; y < m_Height; y++) {
		for (int x = 0; x < m_Width; x++) {
			glm::vec3 color(0.0f);
			for (int i = 0; i < m_PixelWidth; i++) {
				for (int j = 0; j < m_PixelWidth; j++) {
					Ray r = Camera.GetScreenRay(x + j / (float)m_PixelWidth, y + i / (float)m_PixelWidth);
					color += World.GetRayColor(r);
				}
			}

			float scale = 1.0 / (float)(m_PixelWidth * m_PixelWidth);
			color.r = sqrt(scale * color.r);
			color.g = sqrt(scale * color.g);
			color.b = sqrt(scale * color.b);

			Pixel p;
			p.R = (unsigned char)(color.r * 255);
			p.G = (unsigned char)(color.g * 255);
			p.B = (unsigned char)(color.b * 255);

			Canvas.SetPixel(x, y, p);
		}
	}
}