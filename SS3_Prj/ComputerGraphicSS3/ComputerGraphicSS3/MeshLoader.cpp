#include "MeshLoader.h"

#include "Mesh.h"
#include "QuadMesh2D.h"
#include "GlobalDefine.h"
MeshLoader* MeshLoader::mInstance = nullptr;
std::mutex MeshLoader::mLock;
void MeshLoader::Init()
{
	LoadMesh("QuadMesh2D");
}

MeshLoader* MeshLoader::GetInstance()
{
	if (mInstance == nullptr)
	{
		mLock.lock();
		if (mInstance == nullptr)
		{
			mInstance = new MeshLoader();
		}
		mLock.unlock();
	}

	return mInstance;
}

void MeshLoader::DestroyInstance()
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

std::shared_ptr<Mesh> MeshLoader::LoadMesh(std::string fileName)
{
	for (std::shared_ptr<Mesh> mesh : mMeshArray)
	{
		if (mesh->GetName() == fileName)
		{
			return mesh;
		}
	}

	std::shared_ptr<Mesh> mesh = nullptr;
	if (fileName == "QuadMesh2D")
	{
		// position  = (0,0)
		glm::vec2 pos(SCR_WIDTH/2, SCR_HEIGHT/2);
		glm::vec2 anchor(0.5f, 0.5f); // center of the quad
		mesh = std::make_shared<QuadMesh2D>(pos, IMAGE_DEFAULT_SIZE,anchor);
	}
	else
	{
		mesh = std::make_shared<Mesh>(fileName);
	}
	
	mMeshArray.push_back(mesh);
	return mesh;
	
}


void MeshLoader::SetWorkingDir(std::string wdir)
{
	mWorkingDir = wdir;
}
