#include "Node2D.h"
#include "../ResourceManager/MeshLoader.h"
#include "../Render/QuadMesh2D.h"
#include "../GlobalDefine.h"
#include <glm/gtc/matrix_transform.hpp>


Node2D::Node2D()
	:mPosition(glm::vec3(0))
	,mScale(glm::vec3(1))
	,mRotationZ(0)
	,mProjectionMatrix(glm::mat4(1))
	,mName("Empty Node 2D")
	, mMesh(nullptr)
{
	//mParrent = nullptr;
};

Node2D::~Node2D() 
{

};

bool Node2D::Init()
{
	if (mIsInit)
	{
		return true;
	}
	// we need build projection matrix
	mProjectionMatrix = glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, -0.1f, 100.0f);

	mMesh = MeshLoader::GetInstance()->GetQuadMesh2D();
	if (mMesh == nullptr)
	{
		printf("Image Node init fail: can not load mesh");
		return false;
	}

	mMesh->Bind();

	mIsInit = true;
	return true;
}

void Node2D::Update(float deltaTime)
{
	
	mMesh->Update();
	for (const std::shared_ptr<Node> const &node  : mChildNode)
	{
		node->Update(deltaTime);
	}
}

void Node2D::Render()
{
	// render child
	for (const std::shared_ptr<Node> const &node : mChildNode)
	{
		node->Render();
	}
}

void Node2D::ResizeQuad2D(glm::vec2 newSize)
{
	// Since the quad mesh has default size, we need to rescale this mesh
	glm::vec2 quadSize = mMesh->GetInitSize();

	glm::vec2 quadScale = newSize / quadSize;
	mMesh->SetQuadScale(quadScale);
}

void Node2D::SetPosition(glm::vec2 pos)
{
	mPosition = pos;
	mMesh->SetPosition(mPosition);
}

void Node2D::SetRotationZ(glm::float32 rotate)
{
	mRotationZ = rotate;
	glm::vec3 rotation(0, 0, mRotationZ);
	mMesh->SetRotation(rotation);
}

void Node2D::SetScale(glm::vec2 scale)
{
	mScale = scale;
	mMesh->SetScale(scale);
}
