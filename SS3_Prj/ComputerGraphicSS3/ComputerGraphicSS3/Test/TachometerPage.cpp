#include "TachometerPage.h"
#include "../EngineSrc/Node/Image.h"
#include "../EngineSrc/Node/Node2D.h"
#include "../EngineSrc/Render/Material.h"
#include "../EngineSrc/Render/Texture.h"
#include"../EngineSrc/ResourceManager/TextureLoader.h"
#include "../EngineSrc/GlobalDefine.h"
#include "../EngineSrc/Components/AnimationClip.h"
#include "../EngineSrc/Components/BoxColider.h"

#include "glm/glm.hpp"
#include "../EngineSrc/Variant/variant.hpp"

#include<chrono>

//typedef mpark::variant<unsigned int, float, bool, glm::vec2, glm::vec3> NODE_PROPERTY_TYPE;


TachometerPage::TachometerPage()
{
	mBackgroundNode = std::make_shared<Image>("Tachometer_v2.png");
	this->AddNode(mBackgroundNode);

	mSlider = std::make_shared<Node2D>();
	this->AddNode(mSlider);


}

TachometerPage::~TachometerPage()
{

}

bool TachometerPage::Init()
{
	Page::Init(); // Init all added node

	mSlider->SetSize(glm::vec2(690, 690));

	//-----------Test AnimationClip -------------
	NODE_PROPERTY_TYPE startValue = 0.0f;
	NODE_PROPERTY_TYPE endValue = 1.0f;
	auto animation = std::make_shared<AnimationClip>(AnimationClip::eAnimationPropertyType::E_ANIMATION_TYPE_MATERIAL,
		startValue, endValue, 5.0f, AnimationClip::eAnimationPlayMode::E_ANIMATION_PLAY_MODE_LINEAR, "uFilledPercen", 0);
	
	animation->SetAutoPlay(true);
	animation->SetInfinite(true);

	glm::vec2 startScale = glm::vec2(1, 1);
	glm::vec2 endScale = glm::vec2(1.5f, 1.5f);
	auto rotateAnim = std::make_shared<AnimationClip>(AnimationClip::eAnimationPropertyType::E_ANIMATION_TYPE_SCALE,
		startScale, endScale, 2.0f, AnimationClip::eAnimationPlayMode::E_ANIMATION_PLAY_MODE_LINEAR, "", 0);

	rotateAnim->SetAutoPlay(true);
	rotateAnim->SetInfinite(true);
	mSlider->AddComponent(animation);
	mSlider->AddComponent(rotateAnim);

	auto testAnim = mSlider->GetComponent<AnimationClip>();
	auto testBoxColider = mSlider->GetComponent<BoxColider>();
	//-------------------------------------------

	auto sliderTexture = TextureLoader::GetInstance()->LoadTexture("7_13_RPM_Background.png");
	sliderTexture->Init();
	sliderTexture->Bind();
	mSlider->SetTexture(sliderTexture);

	auto imgFillProcess = std::make_shared<Material>("ImageFillProcess");
	imgFillProcess->BindShader();
	mSlider->SetMaterial(imgFillProcess);

	auto baseColor = glm::vec3(149, 18, 0) / glm::vec3(255);
	mSlider->SetMatProperty("uBaseColor", baseColor);
	mSlider->SetMatProperty("uRotate", 60.0f);
	mSlider->SetMatProperty("scaleProcess", 0.666667f);
	mSlider->SetMatProperty("uFilledPercen", 0.2f);

	this->SetRelativePosition(glm::vec2(SCR_WIDTH / 2, SCR_HEIGHT / 2));
	//this->se
	return true;
}

float SPEED_TEST = 0.2f;
void TachometerPage::Update(float deltaTime)
{
	Page::Update(deltaTime);

};
