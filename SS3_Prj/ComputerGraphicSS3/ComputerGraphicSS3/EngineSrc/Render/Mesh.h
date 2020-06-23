#pragma once

#include "glm/glm.hpp"
#include "glad/glad.h"

#include <string>
class Mesh
{
public:
	Mesh();
	~Mesh();

	Mesh(std::string url);

	virtual void Bind();
	virtual void UnBind();
	virtual void Active();
	virtual void Update();
	virtual void Render();
	inline virtual void SetPosition(glm::vec3 pos) { mPosition = pos; mDirtyFlag = true; }
	inline void SetScale(glm::vec3 scale) { mScale = scale; mDirtyFlag = true; }
	inline void SetRotation(glm::vec3 rot) { mRotation = rot; mDirtyFlag = true; }

	inline glm::mat4 GetTranform() { return mTransform;  }

	inline std::string GetName() { return mName; }

protected:
	std::string mName;
	glm::vec3 mPosition;
	glm::vec3 mScale;
	glm::vec3 mRotation;
	glm::mat4 mTransform;

	GLuint mVBO, mVAO, mIBO;

	char* mVertexBuffer, mIndexBuffer;

	bool mDirtyFlag;

	virtual void ApplyTransform();

};

