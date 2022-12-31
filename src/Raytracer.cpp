#include "Raytracer.h"
#include <iostream>
#include <memory>

Raytracer::Raytracer(int width, int height, const glm::vec3& camPos, const glm::vec3& lookAt, float fov, float aperture, float focusDistance, int raysPerPixel)
	: Camera(camPos, lookAt, width, height, fov, aperture, focusDistance), Canvas(width, height),
	m_Width(width), m_Height(height)
{
	m_PixelWidth = (int)sqrt(raysPerPixel);
	m_GPU = std::make_unique<ComputeShader>(m_Width, m_Height);
	m_GPUData = std::make_unique<SceneData>();
	
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
#ifndef NDEBUG
		std::cout << "Progress: " << (y / (float)m_Height) * 100.0f << "%" << std::endl;
#endif
	}
}

void Raytracer::DrawGPU()
{
	UpdateGPUData();
	m_GPU->Run(Canvas, m_GPUData);
}

void Raytracer::UpdateGPUData()
{
	m_GPUData.get()->width = m_Width;
	m_GPUData.get()->height = m_Height;

	// Update Camera
	Camera.Update();
	m_GPUData.get()->camData.position = Camera.Position;
	m_GPUData.get()->camData.horizontal = Camera.Horizontal;
	m_GPUData.get()->camData.vertical = Camera.Vertical;
	m_GPUData.get()->camData.focusDistance = Camera.FocusDistance;
	m_GPUData.get()->camData.lowerLeftColor = Camera.LowerLeftCorner;
	m_GPUData.get()->camData.ratio = Camera.Ratio;

	// Update Spheres TODO: Update with actual world.objects array
	m_GPUData.get()->numSpheres = 1;
	m_GPUData.get()->spheres[0].position = glm::vec3(0.0f, 0.0f, -3.0f);
	m_GPUData.get()->spheres[0].radius = 0.5f;
}