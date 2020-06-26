#pragma once
#include "Node.h"
#include "Property.h"

#include <glm/glm.hpp>

#include <string>
#include <type_traits>

class Mesh;
class QuadMesh2D;
class Texture;
class Material;
class INodeComponent;
class AnimationClip;

class Node2D :
	public Node
{
public:
	enum class eComponentEnumType
	{
		E_COMPONENT_ANIMATION = 0,
		E_COMPONENT_NONE
	};

	struct ComponentInterface 
	{
		eComponentEnumType mType;
		ComponentInterface() {};
		~ComponentInterface() {};
	};


	template <class T>
	struct ComponentNode : public ComponentInterface
	{
		T mComponent;

		ComponentNode(T com)
		{
			mComponent = com;
		}

		~ComponentNode()
		{

		}

	};


	Node2D();
	virtual ~Node2D();

	virtual bool Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	void SetPosition(glm::vec2 pos);
	void SetRelativePosition(glm::vec2 pos);
	void SetRotationZ(glm::float32 rotate);
	void SetScale(glm::vec2 scale);

	void SetSize(glm::vec2 size);
	inline glm::mat4 GetProjectionMatrix() { return mProjectionMatrix; };


	virtual bool AddNode(std::shared_ptr<Node2D> child)
	{
		bool addable = true;
		for (std::shared_ptr<Node2D> node : child->mChildNode2D)
		{
			if (node.get() == this)
			{
				addable = false;
				break;
			}
		}

		if (child.get() != this && addable)
		{
			mChildNode2D.push_back(child);
			return true;
		}
		else
		{
			printf("WARNING!!! You can't add Node. \n");
			return false;
		}
	};

	void SetTexture(std::shared_ptr<Texture> texture);


	void SetMaterial(std::shared_ptr<Material> m);

	template<typename T>
	void SetMatProperty(std::string name, T value)
	{

		PROPERTY_TYPE propertyValue(0);
		PropertyDataType dataType = PropertyDataType::PropertyDataTypeInt;

		if (std::is_same<float, T>::value)
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

		for (int i = 0; i < mListMatProperty.size(); i++)
		{
			if (mListMatProperty[i]->mUniformName == name)
			{
				mListMatProperty[i]->mValue = propertyValue;
				return;
			}
		}

		auto p = std::make_shared<MaterialProperty>(name, dataType, propertyValue);

		mListMatProperty.push_back(p);

	};

	template<typename T>
	void AddComponent(T component)
	{
		
		component->AssignNode2D(this);
		std::shared_ptr<ComponentInterface> componentPtr = std::make_shared< ComponentNode<T>>(component);
		if (std::is_same<T, std::shared_ptr<AnimationClip>>::value)
		{
			componentPtr->mType = eComponentEnumType::E_COMPONENT_ANIMATION;
		}
		else
		{
			componentPtr->mType = eComponentEnumType::E_COMPONENT_NONE;
		}

		mListComponents.push_back(componentPtr);
	};

	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		for (auto componetPtr : mListComponents)
		{
			auto componetType = componetPtr->mType;
			ComponentInterface* cInterface = componetPtr.get();
			if (componetType == eComponentEnumType::E_COMPONENT_ANIMATION)
			{
				if (std::is_same<T, AnimationClip>::value)
				{
					ComponentNode<std::shared_ptr<T>>* cNode = static_cast<ComponentNode<std::shared_ptr<T>>*> (cInterface);
					return cNode->mComponent;
				}
				
			}
		}
		return nullptr;
	};
	
protected:
	
	std::string mName;
	glm::vec2 mPosition;
	glm::vec2 mRelativePosition;
	glm::vec2 mScale;
	glm::float32 mRotationZ;

	glm::mat4 mProjectionMatrix;

	std::shared_ptr<QuadMesh2D> mMesh;
	std::vector<std::shared_ptr<Node2D>> mChildNode2D;
	std::vector<std::shared_ptr<MaterialProperty>> mListMatProperty;

	std::shared_ptr<Texture> mTexture;
	std::shared_ptr<Material> mMaterial;
	glm::vec2 mSize;
	glm::vec2 mAnchor;

	void RenderChild();
	void ResizeQuad2D(glm::vec2 newSize);
	void UpdatePositionFromParrent(glm::vec2 parentRelativePos);
	void SubmitMatProperty();
	
	std::vector<std::shared_ptr< ComponentInterface> > mListComponents;

	void UpdateComponent(float );

};

