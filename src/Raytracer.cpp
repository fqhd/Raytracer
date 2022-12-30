#include "Raytracer.h"
#include <iostream>
#include <memory>

Raytracer::Raytracer(int width, int height, const glm::vec3& camPos, const glm::vec3& lookAt, float fov, float aperture, float focusDistance, int raysPerPixel)
	: Camera(camPos, lookAt, width, height, fov, aperture, focusDistance), Canvas(width, height),
	m_Width(width), m_Height(height)
{
	m_PixelWidth = (int)sqrt(raysPerPixel);
	m_GPU = std::make_unique<ComputeShader>(m_Width, m_Height);
}

void Raytracer::Draw()
{
	Camera.Update();
	for (int y = 0; y < m_Height; y++) {
		for (int x = 0; x < m_Width; x++) {
			glm::vec3 color(0.0f);
			for (int i = 0; i < m_PixelWidth; i++) {
				for (int j = 0; j < m_PixelWidth; j++) {
					Ray r = Camera.GetScreenRay(x + j / (float)m_PixelWidth, y + i / (float)m_PixelWidth);
					color += World.GetRayColor(r);
				}
			}

			float scale = 1.0f / (float)(m_PixelWidth * m_PixelWidth);
			color.r = sqrt(scale * color.r);
			color.g = sqrt(scale * color.g);
			color.b = sqrt(scale * color.b);

			Pixel p;
			p.R = (unsigned char)(color.r * 255);
			p.G = (unsigned char)(color.g * 255);
			p.B = (unsigned char)(color.b * 255);

			Canvas.SetPixel(x, y, p);
		}
#ifdef _DEBUG
		std::cout << "Progress: " << (y / (float)m_Height) * 100.0f << "%" << std::endl;
#endif
	}
}

void Raytracer::DrawGPU() {
	m_GPU->Run(Canvas);
}