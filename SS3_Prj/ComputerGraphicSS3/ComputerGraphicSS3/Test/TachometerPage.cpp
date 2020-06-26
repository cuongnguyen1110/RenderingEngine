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

#include<chrono>

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
	auto animation = std::make_shared<AnimationClip>();
	mSlider->AddComponent(animation);

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
	static auto lastTime = std::chrono::high_resolution_clock::now();

	auto now = std::chrono::high_resolution_clock::now();

	auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count();
	Page::Update(deltaTime);

	static float percen = 0.0f;
	percen += SPEED_TEST * deltaTime;
	if (percen > 1.0f || percen < 0.0f)
	{
		SPEED_TEST = SPEED_TEST * (-1.0f);
	}

	mSlider->SetMatProperty("uFilledPercen", percen);

	lastTime = std::chrono::high_resolution_clock::now();
};
