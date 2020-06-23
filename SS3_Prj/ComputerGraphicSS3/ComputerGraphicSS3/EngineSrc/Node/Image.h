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

	Image();
	Image(std::string url);
	~Image();

	 bool Init() final;
	 void Update(float deltaTime) final;
	 void Render() final;

	 void SetTexture( std::string url);
	 void SetTexture(std::shared_ptr<Texture> texture);
	

	 void SetMaterial(std::shared_ptr<Material> m);

	 template<typename T>
	 void SetMatProperty(std::string name, T value)
	 {
		 PROPERTY_TYPE propertyValue(0);
		 PropertyDataType dataType = PropertyDataType::PropertyDataTypeInt;

		 if ( std::is_same<float, T>::value)
		 {
			 dataType = PropertyDataType::PropertyDataTypeFloat;
			 propertyValue = (value);
		 }
		 if (std::is_same<unsigned int, T>::value)
		 {
			 dataType = PropertyDataType::PropertyDataTypeUInt;
			 propertyValue = (value);
		 }
		 else if (std::is_same<int, T>::value)
		 {
			 dataType = PropertyDataType::PropertyDataTypeInt;
			 propertyValue = (value);
		 }
		 else if (std::is_same<glm::vec3, T>::value)
		 {
			 dataType = PropertyDataType::PropertyDataTypeVector3;
			 propertyValue = (value);
		 }


		 auto p = std::make_shared<MaterialProperty>(name, dataType, propertyValue);

		 mListMatProperty.push_back(p);
		
	 };
	 
private:
	void SubmitMatProperty();

	std::shared_ptr<Texture> mTexture;
	std::shared_ptr<Material> mMaterial;
	glm::vec2 mSize;
	glm::vec2 mAnchor;
	std::string mImageUrl;

	std::vector<std::shared_ptr<MaterialProperty>> mListMatProperty;

};

