#pragma once
#include "World.h"
#include "Camera.h"
#include "Image.h"
#include "ComputeShader.h"
#include "SceneData.h"

class Raytracer {
public:

	Raytracer(int width, int height, const glm::vec3& camPos, const glm::vec3& lookAt, float fov, float aperture, float focusDistance);
	void DrawCPU();
	void DrawGPU();
	
	Camera Camera;
	World World;
	Image Canvas;

private:

	void UpdateGPUData();

	std::unique_ptr<ComputeShader> m_GPU;
	std::unique_ptr<SceneData> m_GPUData;
	int m_Width = 0;
	int m_Height = 0;
	int m_PixelWidth = 0;

};

