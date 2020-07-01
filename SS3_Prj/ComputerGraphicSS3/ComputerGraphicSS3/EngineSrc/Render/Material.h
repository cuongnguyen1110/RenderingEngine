#pragma once

#include <string>
#include <type_traits>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"



class Texture;



class Material
{
public:
	

	Material( std::string);
	~Material();

	void BindShader();
	void Active();

	inline unsigned int GetID() { return mID; }

	
private:
	unsigned int mID;
	std::string mVertexShaderFile, mFragmentShaderFile;

	std::string ReadShaderFromFile(std::string fileName);
};

