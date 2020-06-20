#pragma once

#include <string>

#include "glad/glad.h"
#include "glm/glm.hpp"

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
};

