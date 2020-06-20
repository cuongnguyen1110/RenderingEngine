#pragma once
#include "Node2D.h"
#include "Property.h"
class Texture;
class Mesh;
class Material;


class Image :
	public Node2D
{
public:

	template<typename tType>
	struct MaterialProperty : public Property
	{
		tType mValue;
		MaterialProperty(std::string name, tType value)
			:mValue(value)
		{
			mName = name;
		}
		~MaterialProperty() {};

	};

	Image();
	Image(std::string url);
	~Image();

	 bool Init() final;
	 void Update(float deltaTime) final;
	 void Render() final;

	 void SetTexture( std::string url);
	 void SetTexture(std::shared_ptr<Texture> texture);
	 void SetPosition(glm::vec2 pos);

	 void SetMaterial(std::shared_ptr<Material> m);

	 template<typename T>
	 void SetMatProperty(std::string name, T value)
	 {
		 std::shared_ptr<Property> p = std::make_shared<MaterialProperty<T>>(name, value);
		 if (std::is_same<int, T>::value)
		 {
			 p->mDataType = PropertyDataType::PropertyDataTypeInt;
		 }
		 else if(std::is_same<float, T>::value)
		 {
			 p->mDataType = PropertyDataType::PropertyDataTypeFloat;
		 }
		 else if (std::is_same<bool, T>::value)
		 {
			 p->mDataType = PropertyDataType::PropertyDataTypeBool;
		 }

		 mListMatProperty.push_back(p);
		
	 };
	 
private:
	void SetMesh(std::shared_ptr<Mesh> mesh);
	void SubmitMatProperty();

	std::shared_ptr<Texture> mTexture;
	std::shared_ptr<Mesh> mMesh;
	std::shared_ptr<Material> mMaterial;
	glm::vec2 mSize;
	glm::vec2 mAnchor;

	glm::vec2 mImageScaleSize;

	std::string mImageUrl;

	std::vector<std::shared_ptr<Property>> mListMatProperty;

};

