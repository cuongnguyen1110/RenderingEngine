#include "AnimationClip.h"
#include "../Node/Node2D.h"

AnimationClip::AnimationClip()
{

}


AnimationClip::~AnimationClip()
{

}

AnimationClip::AnimationClip(eAnimationPropertyType pType, NODE_PROPERTY_TYPE start, NODE_PROPERTY_TYPE end, float duration,
	eAnimationPlayMode, std::string name , float delayTime)
	:mPropertyType(pType)
	, mStartValue (start)
	,mEndValue(end)
	, mPropertyName(name)
	,mDurationTime(duration)
	,mDelayTime(delayTime)
	, mIsPlayDone(false)
	, mIsInfinite(false)
	, mPlayTime(0)
{
	mIsAutoPlay = true;

	Init();
}

bool AnimationClip::Init()
{
	mCurrentValue = mStartValue;

	if (auto pval = mpark::get_if<int>(&(mStartValue)))
	{
		int startValue = *pval;
		int endValue = mpark::get<int>(mEndValue);
		mSpeed = (int)((startValue - endValue) / mDurationTime );
	}

	if (auto pval = mpark::get_if<float>(&(mStartValue)))
	{
		float startValue = *pval;

		float endValue;// = mpark::get<float>(mEndValue);
		if (auto pval = mpark::get_if<float>(&(mEndValue)))
		{
			endValue = *pval;
		}
		mSpeed =  (float)((endValue - startValue) / mDurationTime);
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
	//mSpeed = (mEndValue - mStartValue) / mDurationTime;

	if (mIsAutoPlay)
	{
		auto now = std::chrono::high_resolution_clock::now();
		mStartTime = 0;// std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count();
	}
	return true;
}


void AnimationClip::Update(float detalTime)
{
	if (mIsAutoPlay)
	{
		if (auto pval = mpark::get_if<int>(&(mCurrentValue)))
		{
			ApplyAnimationValue<int>(detalTime);
			/*if (mIsPlayDone)
			{
				if (mIsInfinite)
				{
					mCurrentValue = mpark::get<int>(mStartValue);
				}
			}

			int currentVal = *pval;
			int endValue = mpark::get<int>(mEndValue);
			int speed = mpark::get<int>(mSpeed);

			currentVal += speed * detalTime;

			if (currentVal > endValue)
			{
				mIsPlayDone = true;
				currentVal = endValue;
				mCurrentValue = (int)currentVal;
			}*/

		}

		if (auto pval = mpark::get_if<float>(&(mCurrentValue)))
		{
			ApplyAnimationValue<float>(detalTime);
		}

		if (auto pval = mpark::get_if<glm::vec2>(&(mCurrentValue)))
		{
			ApplyAnimationValue<glm::vec2>(detalTime);
		}

		if (auto pval = mpark::get_if<glm::vec3>(&(mCurrentValue)))
		{
			ApplyAnimationValue<glm::vec3>(detalTime);
		}

		
	}

	
}