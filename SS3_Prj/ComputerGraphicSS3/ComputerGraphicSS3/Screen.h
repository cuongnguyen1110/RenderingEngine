#pragma once

#include <vector>
#include <memory>
#include <mutex>

class Page;
class Screen
{
public:
	bool InitScreen();
	void Update(float deltatime);
	void Render();

	static Screen* GetIstance();
	static void DestroyInstance();


private:

	static Screen* mIstance;
	static std::mutex mLock;
	std::vector<std::shared_ptr<Page>> mListPage;
	std::shared_ptr<Page> mRootPage;
};

