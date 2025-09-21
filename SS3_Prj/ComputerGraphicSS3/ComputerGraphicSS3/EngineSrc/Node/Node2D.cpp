#include "Node2D.h"
#include "../ResourceManager/MeshLoader.h"
#include "../Render/QuadMesh2D.h"
#include "../GlobalDefine.h"
#include "../Render/Texture.h"
#include "../Render/Material.h"
#include "../Components/INodeComponent.h"
#include "../Components/AnimationClip.h"

#include <glm/gtc/matrix_transform.hpp>


Node2D::Node2D()
	:mPosition(glm::vec3(0))
	,mRelativePosition(glm::vec3(0))
	,mScale(glm::vec3(1))
	,mRotationZ(0)
	,mProjectionMatrix(glm::mat4(1))
	,mName("Empty Node 2D")
	, mMesh(nullptr)
	,mTexture(nullptr)
	,mMaterial(nullptr)
{
	//mParrent = nullptr;
	mSize = IMAGE_DEFAULT_SIZE;
};

Node2D::~Node2D() 
{

};

bool Node2D::Init()
{
	
	// we need build projection matrix
	mProjectionMatrix = glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, -0.1f, 100.0f);

	mMesh = MeshLoader::GetInstance()->GetQuadMesh2D();
	if (mMesh == nullptr)
	{
		printf("Image Node init fail: can not load mesh");
		return false;
	}

	mMesh->Bind();
	Node2D::ResizeQuad2D(mSize);
	for (auto iter = mChildNode2D.begin(); iter != mChildNode2D.end(); ++iter)
	{
		(*iter)->Init();
	}


	return true;
}

void Node2D::Update(float deltaTime)
{
	
	mMesh->Update();


	for (auto iter = mChildNode2D.begin(); iter != mChildNode2D.end(); ++iter)
	{
		(*iter)->Update(deltaTime);
	}

	UpdateComponent(deltaTime);
}

void Node2D::Render()
{
	// render child
	if (mMesh != nullptr && mMaterial !=nullptr)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		mMaterial->Active();
		

		if (mTexture != nullptr)
		{
			mTexture->Active();
			//binding uniform;
			auto textureLocation = glGetUniformLocation(mMaterial->GetID(), "Texture");
			glUniform1i(textureLocation, 0);
		}

		auto transformLocation = glGetUniformLocation(mMaterial->GetID(), "uTransform");
		glm::mat4 meshTransform = mMesh->GetTranform();
		glm::mat4 projectionMat = this->GetProjectionMatrix();
		glm::mat4 projectionViewModleMat = projectionMat * glm::mat4(1.0f) * meshTransform;
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(projectionViewModleMat));

		SubmitMatProperty();

		mMesh->Active();
		//render mesh
		mMesh->Render();
	}
	
	RenderChild();
}

void Node2D::RenderChild()
{
	for (auto iter = mChildNode2D.begin(); iter != mChildNode2D.end(); ++iter)
	{
		(*iter)->Render();
	}

}

void Node2D::ResizeQuad2D(glm::vec2 newSize)
{
	// Since the quad mesh has default size, we need to rescale this mesh
	glm::vec2 quadSize = mMesh->GetInitSize();

	glm::vec2 quadScale = newSize / quadSize;
	mMesh->SetQuadScale(quadScale);
}

void Node2D::SetRelativePosition(glm::vec2 pos)
{
	mRelativePosition = pos;

	for (auto iter = mChildNode2D.begin(); iter != mChildNode2D.end(); ++iter)
	{
		(*iter)->UpdatePositionFromParrent(mRelativePosition);
	}

}

void Node2D::UpdatePositionFromParrent(glm::vec2 parentRelativePos)
{
	auto pos = mRelativePosition + parentRelativePos;
	SetPosition(pos);
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

void Node2D::SetTexture(std::shared_ptr<Texture> texture)
{

	mTexture = texture;
}


void Node2D::SetMaterial(std::shared_ptr<Material> m)
{
	mMaterial = m;
}

void Node2D::SubmitMatProperty()
{
	for (std::shared_ptr<MaterialProperty> p : mListMatProperty)
	{
		auto location = glGetUniformLocation(mMaterial->GetID(), p->mUniformName.c_str());
		if (location < 0)
		{
			printf("WARNING! can not bind uniform name: %s \n", p->mUniformName.c_str());
			continue;
		}

		switch (p->mDataType)
		{
		case PropertyDataType::PropertyDataTypeFloat:
		{
			if (auto pval = mpark::get_if<float>(&(p->mValue)))
			{
				float value = *pval;
				glUniform1f(location, value);
			}
			break;
		}

		case PropertyDataType::PropertyDataTypeUInt:
		{
			if (auto pval = mpark::get_if<unsigned int>(&(p->mValue)))
			{
				unsigned int value = *pval;
				glUniform1i(location, value);
			}
			break;
		}
		case PropertyDataType::PropertyDataTypeVector3:
		{
			if (auto pval = mpark::get_if<glm::vec3>(&(p->mValue)))
			{
				glm::vec3 value = *pval;
				glUniform3fv(location, 1, glm::value_ptr(value));
			}
			break;
		}
		default:
			break;
		}
	}
}

void Node2D::SetSize(glm::vec2 size)
{
	mSize = size;
	ResizeQuad2D(mSize);
}


void Node2D::UpdateComponent(float deltaTime)
{
	for (auto componetPtr : mListComponents)
	{
		auto componetType = componetPtr->mType;
		ComponentInterface* cInterface = componetPtr.get();
		if (componetType == eComponentEnumType::E_COMPONENT_ANIMATION)
		{
			//if (std::is_same<T, AnimationClip>::value)
			{
				ComponentNode<std::shared_ptr<AnimationClip>>* cNode = static_cast<ComponentNode<std::shared_ptr<AnimationClip>>*> (cInterface);
				cNode->mComponent->Update(deltaTime);
			}

		}
	}
}

