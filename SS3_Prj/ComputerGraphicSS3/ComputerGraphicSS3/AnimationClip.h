#pragma once
#include "INodeComponent.h"

class AnimationClip :
	public INodeComponent
{
public:
	AnimationClip();
	~AnimationClip();

	virtual bool Init() override;
	virtual void Update(float detalTime) override;



private:


};

