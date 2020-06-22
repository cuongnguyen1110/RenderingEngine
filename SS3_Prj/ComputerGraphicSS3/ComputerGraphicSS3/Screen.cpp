#include "Screen.h"
#include "Page.h"
#include "Image.h"
#include "MeshLoader.h"
#include "TextureLoader.h"
#include "TachometerPage.h"

Screen* Screen::mIstance = nullptr;
std::mutex Screen::mLock;

Screen* Screen::GetIstance()
{
	if (mIstance == nullptr)
	{
		mLock.lock();
		if (mIstance == nullptr)
		{
			mIstance = new Screen();
		}
		mLock.unlock();
	}
	return mIstance;
};

void Screen::DestroyInstance()
{
	if (mIstance)
	{
		mLock.lock();
		if (mIstance)
		{
			delete mIstance;
			mIstance = nullptr;
		}

		mLock.unlock();
	}
}

bool Screen::InitScreen()
{
	MeshLoader::GetInstance()->SetWorkingDir("/MeshData/");
	TextureLoader::GetInstance()->SetWorkingDir("./Textures/");

	std::shared_ptr<Page> root = std::make_shared<Page>("RootPage");
	mListPage.push_back(root);

	auto tachometer = std::make_shared<TachometerPage>();
	root->AddNode(tachometer);
	

	for (std::shared_ptr<Page> page : mListPage)
	{
		page->Init();
	}

	mRootPage = root;

	return true;
}

void Screen::Update(float deltatime)
{
	mRootPage->Update(deltatime);
}

void Screen::Render()
{
	mRootPage->Render();
}
