#pragma once
#include "Node.h"
#include <glm/glm.hpp>

#include <string>

class Mesh;
class QuadMesh2D;


class Node2D :
	public Node
{
public:
	Node2D();
	virtual ~Node2D();

	virtual bool Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	void SetPosition(glm::vec2 pos);
	void SetRotationZ(glm::float32 rotate);
	void SetScale(glm::vec2 scale);
	inline glm::mat4 GetProjectionMatrix() { return mProjectionMatrix; };

	
protected:
	
	std::string mName;
	glm::vec2 mPosition;
	glm::vec2 mScale;
	glm::float32 mRotationZ;

	glm::mat4 mProjectionMatrix;

	std::shared_ptr<QuadMesh2D> mMesh;

	void ResizeQuad2D(glm::vec2 newSize);
	


};

