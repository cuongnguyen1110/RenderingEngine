#include "MeshLoader.h"

#include "../Render/Mesh.h"
#include "../Render/QuadMesh2D.h"
#include "../GlobalDefine.h"
MeshLoader* MeshLoader::mInstance = nullptr;
std::mutex MeshLoader::mLock;


MeshLoader::MeshLoader()
	:mQuadMesh(nullptr)
{

}

MeshLoader::~MeshLoader()
{

}


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
		glm::vec2 pos(0, 0);
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

std::shared_ptr<QuadMesh2D> MeshLoader::GetQuadMesh2D()
{
	if (mQuadMesh == nullptr)
	{
		// position  = (0,0)
		glm::vec2 pos(0, 0);
		glm::vec2 anchor(0.5f, 0.5f); // center of the quad
		mQuadMesh = std::make_shared<QuadMesh2D>(pos, IMAGE_DEFAULT_SIZE, anchor);
		mQuadMesh->Bind();
	}

	return mQuadMesh->Clone();
}


void MeshLoader::SetWorkingDir(std::string wdir)
{
	mWorkingDir = wdir;
}
