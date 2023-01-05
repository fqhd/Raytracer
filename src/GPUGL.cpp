#include "GPUGL.h"
#include <iostream>

GPUGL::GPUGL(int width, int height)
{

	if(!glfwInit()){
		std::cout << "Failed to initialize GLFW for opengl window" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	m_Window = glfwCreateWindow(width, height, "GPUGL", nullptr, nullptr);
	if(!m_Window){
		std::cout << "Failed to create OpenGL window for opengl context" << std::endl;
		return;
	}

	glfwMakeContextCurrent(m_Window);
	if(glewInit() != GLEW_OK){
		std::cout << "Failed to initialize GLEW" << std::endl;
		return;
	}

	m_Shader = std::make_unique<Shader>();
	CreateQuad();
}

GPUGL::~GPUGL()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void GPUGL::CreateQuad()
{
	GLuint vao;
	GLuint vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);

	float vertices[] = {
		-1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, 1.0f,
		1.0f, -1.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GPUGL::Run(Image& image, const std::unique_ptr<SceneData>& data)
{
	glfwPollEvents();
	UploadSceneData(data);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glReadPixels(0, 0, image.GetWidth(), image.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, image.GetData());
	glfwSwapBuffers(m_Window);
}

void GPUGL::UploadSceneData(const std::unique_ptr<SceneData>& data)
{
	m_Shader->loadUniform("sceneData.width", data.get()->width);
	m_Shader->loadUniform("sceneData.height", data.get()->height);
	m_Shader->loadUniform("sceneData.camera.origin", data.get()->camera.position);
	m_Shader->loadUniform("sceneData.camera.lowerLeftCorner", data.get()->camera.lowerLeftCorner);
	m_Shader->loadUniform("sceneData.camera.horizontal", data.get()->camera.horizontal);
	m_Shader->loadUniform("sceneData.camera.vertical", data.get()->camera.vertical);
	m_Shader->loadUniform("sceneData.camera.w", data.get()->camera.w);
	m_Shader->loadUniform("sceneData.camera.u", data.get()->camera.u);
	m_Shader->loadUniform("sceneData.camera.v", data.get()->camera.v);
	m_Shader->loadUniform("sceneData.camera.lensRadius", data.get()->camera.lensRadius);

	for (int i = 0; i < MAX_SPHERES; i++) {
		std::string sphere = "sceneData.list.spheres[";
		sphere += std::to_string(i);
		sphere += "]";
		m_Shader->loadUniform(sphere + ".material.albedo", data.get()->list.spheres[i].material.albedo);
		m_Shader->loadUniform(sphere + ".material.ir", data.get()->list.spheres[i].material.ir);
		m_Shader->loadUniform(sphere + ".material.roughness", data.get()->list.spheres[i].material.roughness);
		m_Shader->loadUniform(sphere + ".material.type", data.get()->list.spheres[i].material.type);

		m_Shader->loadUniform(sphere + ".center", data.get()->list.spheres[i].position);
		m_Shader->loadUniform(sphere + ".radius", data.get()->list.spheres[i].radius);
		m_Shader->loadUniform(sphere + ".visible", data.get()->list.spheres[i].visible);
	}
}