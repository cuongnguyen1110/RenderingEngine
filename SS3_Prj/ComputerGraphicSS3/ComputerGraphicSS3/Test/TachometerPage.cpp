#include "TachometerPage.h"
#include "../EngineSrc/Node/Node.h"
#include "../EngineSrc/Node/Image.h"
#include "../EngineSrc/Render/Material.h"
#include "../EngineSrc/GlobalDefine.h"

#include "glm/glm.hpp"

TachometerPage::TachometerPage()
{
	mBackGroundNode = std::make_shared<Image>("7_13_RPM_Background.png");
	this->AddNode(mBackGroundNode);

	mBorderNode = std::make_shared<Image>("7_13_RPM_Border.png");
	this->AddNode(mBorderNode);

	mBackInnerCircleNode = std::make_shared<Image>("7_13_InnerCircles.png");
	this->AddNode(mBackInnerCircleNode);
}

TachometerPage::~TachometerPage()
{

}
bool TachometerPage::Init()
{
	Page::Init(); // Init all added node

	auto mat = std::make_shared<Material>("ImageBaseColor");
	mat->BindShader();
	mBackGroundNode->SetMaterial(mat);
	mBorderNode->SetMaterial(mat);
	mBackInnerCircleNode->SetMaterial(mat);

	glm::vec3 baseColor = glm::vec3(149, 18, 0) / glm::vec3(255);
	mBackGroundNode->SetMatProperty("BaseColor", baseColor);

	baseColor = glm::vec3(26) / glm::vec3(255);
	mBackInnerCircleNode->SetMatProperty("BaseColor", baseColor);

	baseColor = glm::vec3(150) / glm::vec3(255);
	mBorderNode->SetMatProperty("BaseColor", baseColor);

	//mBorderNode->SetScale(glm::vec2(0.5f, 0.5f));

	//mBorderNode->SetRotationZ(-90);

	mBorderNode->SetPosition(glm::vec2(SCR_WIDTH/2, SCR_HEIGHT/2));
	mBackGroundNode->SetPosition(glm::vec2(SCR_WIDTH / 2, SCR_HEIGHT / 2));
	mBackInnerCircleNode->SetPosition(glm::vec2(SCR_WIDTH / 2, SCR_HEIGHT / 2));
	return true;
}


void TachometerPage::Update(float deltaTime)
{

	Page::Update(deltaTime);

};
