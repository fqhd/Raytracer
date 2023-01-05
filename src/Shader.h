#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader {
public:

	Shader();
	~Shader();

	void loadUniform(const std::string& name, const glm::vec3& vec);
	void loadUniform(const std::string& name, const glm::mat4& matrix);
	void loadUniform(const std::string& name, float f);
	void loadUniform(const std::string& name, int i);
	void loadUniform(const std::string& name, bool b);

private:

	GLuint m_ProgramID = 0;
	GLuint m_VertexID = 0;
	GLuint m_FragmentID = 0;

};

