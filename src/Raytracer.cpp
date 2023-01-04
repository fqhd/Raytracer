#include "Raytracer.h"
#include "Utils.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
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
	}
}

void Raytracer::DrawGPU()
{
	Camera.Update();
	UpdateGPUData();
	m_GPU->Run(Canvas, m_GPUData);
}

void Raytracer::UpdateGPUData()
{
	int numSpheres = (int)glm::min((int)World.Objects.size(), MAX_SPHERES);
	// General Information
	m_GPUData.get()->width = m_Width;
	m_GPUData.get()->height = m_Height;
	m_GPUData.get()->samplesPerPixel = m_PixelWidth * m_PixelWidth;

	// Camera
	m_GPUData.get()->camera.position = Camera.Position;
	m_GPUData.get()->camera.lowerLeftCorner = Camera.LowerLeftCorner;
	m_GPUData.get()->camera.horizontal = Camera.Horizontal;
	m_GPUData.get()->camera.vertical = Camera.Vertical;
	m_GPUData.get()->camera.w = Camera.W;
	m_GPUData.get()->camera.u = Camera.U;
	m_GPUData.get()->camera.v = Camera.V;
	m_GPUData.get()->camera.lensRadius = Camera.LensRadius;

	for(int i = 0; i < MAX_SPHERES; i++){
		m_GPUData.get()->list.spheres[i].visible = 0;
	}

	// Add Sphere Data
	for(int i = 0; i < numSpheres; i++){
		if(Sphere* s = dynamic_cast<Sphere*>(World.Objects[i].get())){
			m_GPUData.get()->list.spheres[i].position = s->Position;
			m_GPUData.get()->list.spheres[i].radius = s->Radius;
			m_GPUData.get()->list.spheres[i].visible = 1;
			if(Lambertian* mat = dynamic_cast<Lambertian*>(s->material.get())){
				m_GPUData.get()->list.spheres[i].material.albedo = mat->Color;
				m_GPUData.get()->list.spheres[i].material.type = 0;
			}else if(Metal* mat = dynamic_cast<Metal*>(s->material.get())){
				m_GPUData.get()->list.spheres[i].material.albedo = mat->Color;
				m_GPUData.get()->list.spheres[i].material.roughness = mat->Roughness;
				m_GPUData.get()->list.spheres[i].material.type = 1;
			}else if(Dielectric* mat = dynamic_cast<Dielectric*>(s->material.get())){
				m_GPUData.get()->list.spheres[i].material.ir = mat->RefractionIndex;
				m_GPUData.get()->list.spheres[i].material.type = 2;
			}
		}
	}
}