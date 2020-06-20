#include "Material.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


Material::Material(std::string sharderName)
{
	mVertexShaderFile = "./Shader/" +  sharderName + ".vert.glsl";
	mFragmentShaderFile = "./Shader/" +  sharderName + ".frag.glsl";
}

Material::~Material()
{

}

void Material::BindShader()
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;

	{
		// open files
		vShaderFile.open(mVertexShaderFile);
		fShaderFile.open(mFragmentShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}

	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	//checkCompileErrors(vertex, "VERTEX");
	int  success;
	char infoLog[512];
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		printf("ERROR!!! SHADER::VERTEX::COMPILATION_FAILED : %s\n", mVertexShaderFile.c_str());
		printf("ERROR!!! %s \n", infoLog);
	}

	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		printf("ERROR!!! SHADER::FRAGMENT::COMPILATION_FAILED : %s\n", mFragmentShaderFile.c_str());
		printf("ERROR!!! %s \n", infoLog);
	}

	// shader Program
	mID = glCreateProgram();
	glAttachShader(mID, vertex);
	glAttachShader(mID, fragment);

	glLinkProgram(mID);
	glGetProgramiv(mID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(mID, 512, NULL, infoLog);
		printf("ERROR!!! PROGRAM LINK FAIL : %s\n", mFragmentShaderFile.c_str());
		printf("ERROR!!! %s \n", infoLog);
	}

	//checkCompileErrors(ID, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Material::Active()
{
	glUseProgram(mID);
}