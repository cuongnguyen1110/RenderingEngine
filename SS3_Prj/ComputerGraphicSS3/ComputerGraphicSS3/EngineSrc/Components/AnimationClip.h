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
		E_ANIMATION_TYPE_NONE,
	};

	enum class eAnimationPlayMode
	{
		E_ANIMATION_PLAY_MODE_LINEAR = 0,
		E_ANIMATION_PLAY_MODE_BEZIER = 1,
		E_ANIMATION_PLAY_MODE_NODE = 2,
	};

	//==== Animation Value struct =======================
	struct AnimationValue
	{
		NODE_PROPERTY_TYPE mStartValue, mEndValue, mCurrentValue, mSpeed;
		eAnimationPropertyType mPropertyType;
		eAnimationPlayMode mPlaybackMode;
		std::string mPropertyName;
		float mDurationTime;

		AnimationValue(NODE_PROPERTY_TYPE statr, NODE_PROPERTY_TYPE end, float durationTime, eAnimationPropertyType animtype, 
			eAnimationPlayMode playMode, std::string materialName);
		AnimationValue() = delete;
		void Init();

	};

	AnimationClip();
	~AnimationClip();

	/*AnimationClip(eAnimationPropertyType pType, NODE_PROPERTY_TYPE start, NODE_PROPERTY_TYPE end, float duration,
		eAnimationPlayMode, std::string name, float delayTime = 0);*/

	virtual bool Init() override;
	virtual void Update(float detalTime) override;

	inline void SetInfinite(bool b) { mIsInfinite = b; }
	inline void SetAutoPlay(bool play) { mIsAutoPlay = play; }

	void AddAnimProperty(std::shared_ptr< AnimationValue>);


private:
	
	float mStartTime;
	float mDelayTime;
	
	float mPlayTime;
	bool mIsAutoPlay;
	bool mIsPlayDone;
	bool mIsInfinite;

	std::vector< std::shared_ptr<AnimationValue> > mListAnimProperty;

	template <typename T>
	void ApplyAnimationValue(float detalTime, std::shared_ptr<AnimationValue> animP)
	{
		mPlayTime += detalTime;
		if (mIsPlayDone)
		{
			if (mIsInfinite)
			{
				mIsPlayDone = false;
				animP->mCurrentValue = mpark::get<T>(animP->mStartValue);
			}
		}

		T currentVal = mpark::get<T>(animP->mCurrentValue);
		T endValue = mpark::get<T>(animP->mEndValue);
		T speed = mpark::get<T>(animP->mSpeed);

		currentVal += speed * detalTime ;
		animP->mCurrentValue = (T)currentVal;

		if (mPlayTime > animP->mDurationTime)
		{
			mPlayTime = 0;
			mStartTime = 0;
			mIsPlayDone = true;
			currentVal = endValue;
			
		}

		switch (animP->mPropertyType)
		{
		case eAnimationPropertyType::E_ANIMATION_TYPE_POSSITION:
		{
			glm::vec3 pos = mpark::get<glm::vec3>(animP->mCurrentValue);
			mAssignedNode->SetPosition(pos);
			break;
		}
		case eAnimationPropertyType::E_ANIMATION_TYPE_ROTATION:
		{
			float rotateZ = mpark::get<float>(animP->mCurrentValue);
			mAssignedNode->SetRotationZ(rotateZ);
			break;
		}
		case eAnimationPropertyType::E_ANIMATION_TYPE_SCALE:
		{
			glm::vec2 scale = mpark::get<glm::vec2>(animP->mCurrentValue);
			mAssignedNode->SetScale(scale);
			break;
		}
		case eAnimationPropertyType::E_ANIMATION_TYPE_MATERIAL:
		{
			T value = mpark::get<T>(animP->mCurrentValue);
			mAssignedNode->SetMatProperty<T>(animP->mPropertyName, value);
			break;
		}
		default:
			break;
		}
	}

	
};

