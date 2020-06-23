#pragma once
#include "glm/glm.hpp"
#include "glad/glad.h"
#include <string>
class Texture
{
public:
	Texture();
	Texture(std::string url);
	~Texture();

	bool Init();
	void Bind();
	void Active();
	void ReleasMemRAM();
	void UnBind();

	inline std::string GetName() { return mUrl; }
	inline glm::vec2 GetSize() { return mSize; }
	inline GLuint GetID() { return mID; }
private:
	glm::vec2 mSize;
	unsigned char mBPP;
	std::string mUrl;
	unsigned char* mData;

	GLuint mID;
	GLuint mType;
};

