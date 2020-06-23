#include "TextureLoader.h"

#include "../Render/Texture.h"


TextureLoader* TextureLoader::mInstance = nullptr;
std::mutex TextureLoader::mLock;
void TextureLoader::Init()
{
	
}

TextureLoader* TextureLoader::GetInstance()
{
	if (mInstance == nullptr)
	{
		mLock.lock();
		if (mInstance == nullptr)
		{
			mInstance = new TextureLoader();
		}
		mLock.unlock();
	}

	return mInstance;
}

void TextureLoader::DestroyInstance()
{
	if (mInstance)
	{
		mLock.lock();
		if (mInstance)
		{
			delete mInstance;
			mInstance = nullptr;
		}

		mLock.unlock();
	}
}

std::shared_ptr<Texture> TextureLoader::LoadTexture(std::string fileName)
{
	for (std::shared_ptr<Texture> texture : mTextureArray)
	{
		if (texture->GetName() == fileName)
		{
			return texture;
		}
	}

	std::string url = mWorkingDir + fileName;
	std::shared_ptr<Texture> texture = nullptr;
	texture = std::make_shared<Texture>(url);
	mTextureArray.push_back(texture);
	return texture;

}


void TextureLoader::SetWorkingDir(std::string wdir)
{
	mWorkingDir = wdir;
}

