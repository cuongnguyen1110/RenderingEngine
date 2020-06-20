#include "Texture.h"
#include "GlobalDefine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture()
	:mSize(IMAGE_DEFAULT_SIZE)
	, mBPP(0)
	, mData(nullptr)
	, mID(0)
	, mType(GL_RGBA)
{

}
Texture::Texture(std::string url)
	:mUrl(url)
	, mSize(IMAGE_DEFAULT_SIZE)
	, mBPP(0)
	, mData(nullptr)
	, mID(0)
	, mType(GL_RGBA)
{

}

Texture::~Texture()
{
	ReleasMemRAM();
	UnBind();
}

bool Texture::Init()
{
	if (!mUrl.empty())
	{
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		mData = stbi_load(mUrl.c_str(), &width, &height, &nrChannels, 0);
		if (mData == nullptr)
		{
			printf("Fail to load texture: %s", mUrl.c_str());
			return false;
		}
		else
		{
			mSize = glm::vec2(width, height);
			mBPP = nrChannels * 8;
			if (mBPP == 32)
			{
				mType = GL_RGBA;
			}
			else if (mBPP == 24)
			{
				mType = GL_RGB;
			}
			else
			{
				printf("Unknow Texture compresion type: bpp = %d \n", mBPP);
			}

			return true;
		}
		
	}

	return true;
}

void Texture::ReleasMemRAM()
{
	if (mData)
	{
		stbi_image_free(mData);
		mData = 0;
	}
	
}

void Texture::Bind()
{
	// load and create a texture 
	// -------------------------
	
	glGenTextures(1, &mID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	if (mData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, mType, mSize.x, mSize.y, 0, mType, GL_UNSIGNED_BYTE, mData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::Active()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mID);

}

void Texture::UnBind()
{
	if (mID != 0)
	{
		glDeleteTextures(1, &mID);
		mID = 0;
	}
	
}