#pragma once
#include "../EngineSrc/Node/Page.h"


class Image;
class Node;

class TachometerPage :
	public Page
{
public:
	TachometerPage();
	~TachometerPage();
	 bool Init() final;
	 void Update(float deltaTime) final;
	
private:
	std::shared_ptr<Image> mBackGroundNode;
	std::shared_ptr<Image> mBorderNode;
	std::shared_ptr<Image> mBackInnerCircleNode;
};

