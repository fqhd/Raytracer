#include "Shader.h"
#include <iostream>

std::string readFileToString(const std::string& shaderName) {
	std::string shaderCode = "";
	std::string line;
	std::ifstream is;
	is.open(shaderName);
	if(is.fail()){
		std::cout << "Failed to find file: " << shaderName << std::endl;
		is.close();
		return shaderCode;
	}

	while(std::getline(is, line)) {
		shaderCode += line + "\n";
	}

	is.close();
	return shaderCode;
}

Shader::Shader(){
	m_VertexID = glCreateShader(GL_VERTEX_SHADER);
	m_FragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vsCode = readFileToString("shaders/gl.vs");
	std::string fsCode = readFileToString("shaders/gl.fs");

	const char* vs_pointer = vsCode.c_str();
	const char* fs_pointer = fsCode.c_str();

	glShaderSource(m_VertexID, 1, &vs_pointer, 0);
	glShaderSource(m_FragmentID, 1, &fs_pointer, 0);

	GLint vsCompileStatus;
	GLint fsCompileStatus;

	glCompileShader(m_VertexID);
	glGetShaderiv(m_VertexID, GL_COMPILE_STATUS, &vsCompileStatus);
	if(!vsCompileStatus){
		std::cout << "Failed to compile OpenGL vertex shader" << std::endl;
	}

	glCompileShader(m_FragmentID);
	glGetShaderiv(m_FragmentID, GL_COMPILE_STATUS, &fsCompileStatus);
	if(!fsCompileStatus){
		std::cout << "Failed to compile OpenGL fragment shader" << std::endl;
	}

	m_ProgramID = glCreateProgram();
	glAttachShader(m_ProgramID, m_VertexID);
	glAttachShader(m_ProgramID, m_FragmentID);
	glLinkProgram(m_ProgramID);
	glValidateProgram(m_ProgramID);

	glUseProgram(m_ProgramID);
}

Shader::~Shader(){
	glDetachShader(m_ProgramID, m_VertexID);
	glDetachShader(m_ProgramID, m_FragmentID);
	glDeleteShader(m_VertexID);
	glDeleteShader(m_FragmentID);
	glDeleteProgram(m_ProgramID);
}

void Shader::loadUniform(const std::string& name, const glm::vec3& vec){
	glUniform3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &vec.x);
}

void Shader::loadUniform(const std::string& name, const glm::mat4& matrix){
	glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::loadUniform(const std::string& name, float f){
	glUniform1f(glGetUniformLocation(m_ProgramID, name.c_str()), f);
}

void Shader::loadUniform(const std::string& name, int i){
	glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), i);
}

void Shader::loadUniform(const std::string& name, bool b){
	int value = (int)b;
	glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
}