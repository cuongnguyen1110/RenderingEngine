#include <type_traits>

#include "Image.h"

#include "MeshLoader.h"
#include "QuadMesh2D.h"
#include "GlobalDefine.h"
#include "TextureLoader.h"
#include "Texture.h"
#include "Material.h"
#include "glm/gtc/type_ptr.hpp"

#include "variant.hpp"

Image::Image()
	:mTexture(nullptr)
	, mMesh(nullptr)
{
	
	mSize = IMAGE_DEFAULT_SIZE;
}

Image::Image(std::string url)
	:mTexture(nullptr)
	, mMesh(nullptr)
	, mImageUrl(url)
{
	mSize = IMAGE_DEFAULT_SIZE;
}

Image::~Image() 
{
};

bool Image::Init()
{
	if (mTexture == nullptr)
	{
		if (!mImageUrl.empty())
		{
			mTexture = TextureLoader::GetInstance()->LoadTexture(mImageUrl);
			if (mTexture == nullptr)
			{

			}
			else
			{
				mTexture->Init();
				mTexture->Bind();
				mSize = mTexture->GetSize();
				//SetMatProperty(std::string("Texture"), mTexture->GetID());
			}

		}
	}
	mMesh = MeshLoader::GetInstance()->LoadMesh("QuadMesh2D");
	if (mMesh == nullptr)
	{
		printf("Image Node init fail: can not load mesh");
		return false;
	}
	else
	{
		//mMesh->Bind();
	}

	// Since the quad mesh has default size, we need to rescale this mesh
	glm::vec2 quadSize =  dynamic_cast<QuadMesh2D*>(mMesh.get())->GetInitSize();	

	glm::vec2 quadScale = mSize / quadSize;
	dynamic_cast<QuadMesh2D*>(mMesh.get())->SetQuadScale(quadScale);

	mMesh->Bind();
	
	// init material
	mMaterial = std::make_shared<Material>("Image");
	mMaterial->BindShader();
	return true;
}

void Image::SetPosition(glm::vec2 pos)
{
	mPosition = pos;
	dynamic_cast<QuadMesh2D*>(mMesh.get())->SetPosition(mPosition);
}


void Image::Update(float deltaTime)
{
	mMesh->Update();
}

void Image::Render()
{
	if (mTexture == nullptr || mMesh == nullptr)
	{

		printf("Missing texture/mesh for ImageNode: %s", mName.c_str());
	}
	else
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		mMaterial->Active();

		mTexture->Active();

		 //binding uniform;
		auto textureLocation = glGetUniformLocation(mMaterial->GetID(), "Texture");
		glUniform1i(textureLocation, 0);

		auto transformLocation = glGetUniformLocation(mMaterial->GetID(), "uTransform");
		glm::mat4 meshTransform = mMesh->GetTranform();
		glUniformMatrix4fv(transformLocation,1, GL_FALSE, glm::value_ptr(meshTransform));
		
		SubmitMatProperty();

		mMesh->Active();
		//render mesh
		mMesh->Render();
	}
}


void Image::SetTexture(std::string url)
{

}

void Image::SetTexture(std::shared_ptr<Texture> texture)
{
	
	mTexture = texture;
}



void Image::SetMesh(std::shared_ptr<Mesh> mesh)
{
	mMesh = mesh;
}

void Image::SetMaterial(std::shared_ptr<Material> m)
{
	mMaterial = m;
}

void Image::SubmitMatProperty()
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