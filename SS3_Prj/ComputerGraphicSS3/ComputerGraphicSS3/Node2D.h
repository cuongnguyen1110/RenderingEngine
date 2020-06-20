#pragma once
#include "Node.h"
#include <glm/glm.hpp>

#include <string>
class Node2D :
	public Node
{
public:
	Node2D() {};
	virtual ~Node2D() {};

	virtual bool Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	virtual void SetPosition(glm::vec2 pos) { mPosition = pos; }
protected:
	std::string mName;
	glm::vec2 mPosition;
	glm::vec2 mScale;
	glm::float32 mRotationZ;

	


};

