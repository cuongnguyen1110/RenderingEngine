#pragma once

#include <memory>
#include <mutex>
#include <vector>

class Texture;

class TextureLoader
{
public:
	static TextureLoader* GetInstance();
	static void DestroyInstance();

	void Init();
	std::shared_ptr<Texture> LoadTexture(std::string fileName);
	void SetWorkingDir(std::string wdir);

private:
	TextureLoader() {};
	~TextureLoader() {};

	static std::mutex mLock;
	static TextureLoader* mInstance;

	std::vector<std::shared_ptr<Texture>> mTextureArray;
	std::string mWorkingDir;
};

