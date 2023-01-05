#pragma once
#include <memory>
#include "SceneData.h"
#include "Image.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <gl/glew.h>
#include "Shader.h"

class GPUGL {
public:

	GPUGL(int width, int height);
	~GPUGL();

    void Run(Image& image, const std::unique_ptr<SceneData>& data);

private:

	void CreateQuad();

	GLFWwindow* m_Window = nullptr;
	std::unique_ptr<Shader> m_Shader = nullptr;

};