#pragma once
#include "World.h"
#include "Camera.h"
#include "Image.h"
#include "ComputeShader.h"
#include "SceneData.h"

enum class Backend {
	CPU,
	Vulkan,
	OpenGL
};

class Raytracer {
public:

	Raytracer(int width, int height, const glm::vec3& camPos, const glm::vec3& lookAt, float fov, float aperture, float focusDistance, Backend backend = Backend::CPU);
	void Draw();
	
	Camera Camera;
	World World;
	Image Canvas;

private:

	void DrawOpenGL();
	void DrawVulkan();
	void DrawCPU();

	void UpdateGPUData();

	std::unique_ptr<ComputeShader> m_GPU;
	std::unique_ptr<SceneData> m_GPUData;
	int m_Width = 0;
	int m_Height = 0;
	int m_PixelWidth = 0;
	Backend m_Backend = Backend::CPU;

};

