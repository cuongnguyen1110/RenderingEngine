#pragma once
#include "INodeComponent.h"
#include "../Node/Node2D.h"

#include "../Variant/variant.hpp"
#include "glm/glm.hpp"

#include <chrono>

class Node2D;

typedef mpark::variant<int, unsigned int, float, glm::vec2, glm::vec3, glm::mat4> NODE_PROPERTY_TYPE;

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

	inline void SetInfinite(bool b) { mIsInfinite = b; }
	inline void SetAutoPlay(bool play) { mIsAutoPlay = play; }



private:
	

	NODE_PROPERTY_TYPE mStartValue, mEndValue, mCurrentValue, mSpeed;
	eAnimationPropertyType mPropertyType;
	eAnimationPlayMode mPlaybackMode;
	std::string mPropertyName;

	float mStartTime;
	float mDelayTime;
	float mDurationTime;
	float mPlayTime;
	bool mIsAutoPlay;
	bool mIsPlayDone;
	bool mIsInfinite;

	template <typename T>
	void ApplyAnimationValue(float detalTime)
	{
		mPlayTime += detalTime;
		if (mIsPlayDone)
		{
			if (mIsInfinite)
			{
				mIsPlayDone = false;
				mCurrentValue = mpark::get<T>(mStartValue);
			}
		}

		T currentVal = mpark::get<T>(mCurrentValue);
		T endValue = mpark::get<T>(mEndValue);
		T speed = mpark::get<T>(mSpeed);

		currentVal += speed * detalTime ;
		mCurrentValue = (T)currentVal;

		if (mPlayTime > mDurationTime)
		{
			mPlayTime = 0;
			mStartTime = 0;;// std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count();
			mIsPlayDone = true;
			currentVal = endValue;
			
		}

		switch (mPropertyType)
		{
		case eAnimationPropertyType::E_ANIMATION_TYPE_POSSITION:
		{
			glm::vec3 pos = mpark::get<glm::vec3>(mCurrentValue);
			mAssignedNode->SetPosition(pos);
			break;
		}
		case eAnimationPropertyType::E_ANIMATION_TYPE_ROTATION:
		{
			float rotateZ = mpark::get<float>(mCurrentValue);
			mAssignedNode->SetRotationZ(rotateZ);
			break;
		}
		case eAnimationPropertyType::E_ANIMATION_TYPE_SCALE:
		{
			glm::vec2 scale = mpark::get<glm::vec2>(mCurrentValue);
			mAssignedNode->SetScale(scale);
			break;
		}
		case eAnimationPropertyType::E_ANIMATION_TYPE_MATERIAL:
		{
			T value = mpark::get<T>(mCurrentValue);
			mAssignedNode->SetMatProperty<T>(mPropertyName, value);
			break;
		}
		default:
			break;
		}
	}

	
};

