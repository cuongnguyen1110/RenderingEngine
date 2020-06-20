#pragma once

#include <memory>
#include <mutex>
#include <vector>

class Mesh;

class MeshLoader
{
public:
	static MeshLoader* GetInstance();
	static void DestroyInstance();

	void Init();
	std::shared_ptr<Mesh> LoadMesh(std::string fileName);
	void SetWorkingDir(std::string wdir);

private:
	MeshLoader() {};
	~MeshLoader() {};

	static std::mutex mLock;
	static MeshLoader* mInstance;

	std::vector<std::shared_ptr<Mesh>> mMeshArray;
	std::string mWorkingDir;
};

