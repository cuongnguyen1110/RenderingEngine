#include "TachometerPage.h"
#include "Node.h"
#include "Image.h"
#include "Material.h"

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
	Page::Init();

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
	return true;
}


void TachometerPage::Update(float deltaTime)
{

	Page::Update(deltaTime);

};
