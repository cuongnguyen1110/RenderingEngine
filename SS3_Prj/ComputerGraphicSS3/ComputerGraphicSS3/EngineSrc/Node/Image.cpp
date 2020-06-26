#include <type_traits>

#include "Image.h"

#include "../ResourceManager/MeshLoader.h"
#include "../Render/QuadMesh2D.h"''
#include "../GlobalDefine.h"
#include "../ResourceManager/TextureLoader.h"
#include "../Render/Texture.h"
#include "../Render/Material.h"
#include "glm/gtc/type_ptr.hpp"

#include "../Variant/variant.hpp"

Image::Image()
{
	
	mSize = IMAGE_DEFAULT_SIZE;
}

Image::Image(std::string url)
	:mImageUrl(url)
{
	mSize = IMAGE_DEFAULT_SIZE;
}

Image::~Image() 
{
};

bool Image::Init()
{
	Node2D::Init();

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
			}

		}
	}
	
	Node2D::ResizeQuad2D(mSize);
	
	// init material
	mMaterial = std::make_shared<Material>("Image");
	mMaterial->BindShader();
	return true;
}

void Image::Update(float deltaTime)
{
	Node2D::Update(deltaTime);

}

void Image::Render()
{
	if (mTexture == nullptr || mMesh == nullptr)
	{

		printf("Missing texture/mesh for ImageNode: %s", mName.c_str());
	}
	else
	{
		Node2D::Render();
	}

	Node2D::RenderChild();
}

