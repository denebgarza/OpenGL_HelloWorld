#include "ShaderLoader.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace Core;

ShaderLoader::ShaderLoader(void) {}
ShaderLoader::~ShaderLoader(void) {}

std::string ShaderLoader::ReadShader(char *fileName) {

	std::string shaderCode;
	std::ifstream file(fileName, std::ios::in);

	if (!file.good()) {
		std::cout << "Can't read file " << fileName << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();

	return shaderCode;

}

GLuint ShaderLoader::CreateShader(GLenum shaderType, std::string source, char *shaderName) {
	
	int compileResult = 0;
	GLuint shader = glCreateShader(shaderType);
	const char *shaderCodePtr = source.c_str();
	const int shaderCodeSize = source.size();

	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_FALSE) {
		std::cout << "ERROR compiling shader " << shaderName << std::endl;
		return 0;
	}

	return shader;

}

GLuint ShaderLoader::CreateProgram(char *vertexShaderFilename, char *fragmentShaderFilename) {
	std::string vertexShaderCode = ReadShader(vertexShaderFilename);
	std::string fragmentShaderCode = ReadShader(fragmentShaderFilename);

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, "VertexShader");
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "FragmentShader");

	int linkResult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_FALSE) {
		std::cout << "ERROR linking shaders" << std::endl;
		return 0;
	}

	return program;

}