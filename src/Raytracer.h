#pragma once
#include "World.h"
#include "Camera.h"
#include "Image.h"
#include "ComputeShader.h"
#include "SceneData.h"

class Raytracer {
public:

	Raytracer(int width, int height, const glm::vec3& camPos, const glm::vec3& lookAt, float fov, float aperture, float focusDistance);
	void Draw();

	/*
		This function is depricated. It causes bugs due to compute time timeout, and doesn't support more than a few hundred spheres.
	*/
	void DrawGPU();

	int m_Width = 0;
	int m_Height = 0;
	int m_PixelWidth = 0;
	Camera Camera;
	World World;
	Image Canvas;

private:

	void UpdateGPUData();

	std::unique_ptr<ComputeShader> m_GPU;
	std::unique_ptr<SceneData> m_GPUData;

};

