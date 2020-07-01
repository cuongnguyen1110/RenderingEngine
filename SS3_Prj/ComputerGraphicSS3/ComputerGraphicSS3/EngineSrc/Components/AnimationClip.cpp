#include "AnimationClip.h"
#include "../Node/Node2D.h"

AnimationClip::AnimationClip()
: mIsPlayDone(false)
, mIsInfinite(false)
, mPlayTime(0)
{

}


//TODO: fix all animation value has same durationtime

AnimationClip::~AnimationClip()
{
	mIsAutoPlay = false;
	Init();
}

bool AnimationClip::Init()
{
	
	for (const std::shared_ptr<AnimationValue> const animP : mListAnimProperty)
	{
		animP->Init();
	}

	if (mIsAutoPlay)
	{
		mStartTime = 0;
	}
	return true;
}


void AnimationClip::Update(float detalTime)
{

	for (const std::shared_ptr<AnimationValue> animP : mListAnimProperty)
	{
		if (mIsAutoPlay)
		{
			if (auto pval = mpark::get_if<int>(&(animP->mCurrentValue)))
			{
				ApplyAnimationValue<int>(detalTime, animP);
			}

			if (auto pval = mpark::get_if<float>(&(animP->mCurrentValue)))
			{
				ApplyAnimationValue<float>(detalTime, animP);
			}

			if (auto pval = mpark::get_if<glm::vec2>(&(animP->mCurrentValue)))
			{
				ApplyAnimationValue<glm::vec2>(detalTime, animP);
			}

			if (auto pval = mpark::get_if<glm::vec3>(&(animP->mCurrentValue)))
			{
				ApplyAnimationValue<glm::vec3>(detalTime, animP);
			}
		}
	}
	
}

void AnimationClip::AddAnimProperty(std::shared_ptr< AnimationValue> animProperty)
{
	mListAnimProperty.push_back(animProperty);
}

// implementation for class sAnimProtperty

AnimationClip::AnimationValue::AnimationValue(NODE_PROPERTY_TYPE start, NODE_PROPERTY_TYPE end, float durationTime, eAnimationPropertyType animtype,
	eAnimationPlayMode playMode, std::string materialName)
	:mStartValue(start)
	,mEndValue(end)
	,mDurationTime(durationTime)
	, mPropertyType(animtype)
	, mPlaybackMode(playMode)
	,mPropertyName(materialName)
{

}


void AnimationClip::AnimationValue::Init()
{
	mCurrentValue = mStartValue;

	if (auto pval = mpark::get_if<int>(&(mStartValue)))
	{
		int startValue = *pval;
		int endValue = mpark::get<int>(mEndValue);
		mSpeed = (int)((startValue - endValue) / mDurationTime);
	}

	if (auto pval = mpark::get_if<float>(&(mStartValue)))
	{
		float startValue = *pval;

		float endValue = mpark::get<float>(mEndValue);
		mSpeed = (float)((endValue - startValue) / mDurationTime);
	}

	if (auto pval = mpark::get_if<glm::vec2>(&(mStartValue)))
	{
		glm::vec2 startValue = *pval;
		glm::vec2 endValue = mpark::get<glm::vec2>(mEndValue);
		mSpeed = (glm::vec2)((startValue - endValue) / mDurationTime);
	}

	if (auto pval = mpark::get_if<glm::vec3>(&(mStartValue)))
	{
		glm::vec3 startValue = *pval;
		glm::vec3 endValue = mpark::get<glm::vec3>(mEndValue);
		mSpeed = (glm::vec3)((startValue - endValue) / mDurationTime);
	}
}
