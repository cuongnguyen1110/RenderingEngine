#pragma once
#include "../EngineSrc/Node/Page.h"


class Image;
class Node2D;

class TachometerPage :
	public Page
{
public:
	TachometerPage();
	~TachometerPage();
	 bool Init() final;
	 void Update(float deltaTime) final;
	
private:
	std::shared_ptr<Node2D> mSlider;
	std::shared_ptr<Image> mBackgroundNode;
};

