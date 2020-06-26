#pragma once
#include "INodeComponent.h"

#include "../Variant/variant.hpp"
#include "glm/glm.hpp"

class Node2D;

typedef mpark::variant<float, bool, glm::vec2, glm::vec3> NODE_PROPERTY_TYPE;

class AnimationClip :
	public INodeComponent
{

public:

	enum class eAnimationPropertyType
	{
		E_ANIMATION_TYPE_POSSITION = 0,
		E_ANIMATION_TYPE_ROTATION = 1,
		E_ANIMATION_TYPE_SCALE = 2,
		E_ANIMATION_TYPE_MATERIAL = 3,
		E_ANIMATION_TYPE_NONE ,
	};

	enum class eAnimationPlayMode
	{
		E_ANIMATION_PLAY_MODE_LINEAR = 0,
		E_ANIMATION_PLAY_MODE_BEZIER = 1,
		E_ANIMATION_PLAY_MODE_NODE = 2,
	};

	AnimationClip();
	~AnimationClip();

	AnimationClip(eAnimationPropertyType pType, NODE_PROPERTY_TYPE start, NODE_PROPERTY_TYPE end, float duration,
		eAnimationPlayMode, std::string name, float delayTime = 0);

	virtual bool Init() override;
	virtual void Update(float detalTime) override;



private:
	

	NODE_PROPERTY_TYPE mStartValue, mEndValue, mCurrentValue;
	eAnimationPropertyType mPropertyType;
	eAnimationPlayMode mPlaybackMode;


	float mDurationTime;
};

