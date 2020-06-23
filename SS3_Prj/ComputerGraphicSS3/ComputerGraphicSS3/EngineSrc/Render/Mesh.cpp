#include "Mesh.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh()
	:mPosition(glm::vec3(0))
	, mScale(glm::vec3(1))
	,mRotation(glm::vec3(0))
	,mTransform(glm::mat4(1))
	,mVAO(0)
	,mVBO(0)
	,mIBO(0)
{
	mDirtyFlag = true;
}

Mesh::~Mesh()
{
	UnBind();
}

Mesh::Mesh(std::string url)
{

}


void Mesh::Bind()
{

}

void Mesh::UnBind()
{
	if (mVAO)
	{
		glDeleteVertexArrays(1, &mVAO);
		mVAO = 0;
	}

	if (mVBO)
	{
		glDeleteBuffers(1, &mVBO);
		mVBO = 0;
	}

	if (mIBO)
	{
		glDeleteBuffers(1, &mIBO);
		mIBO = 0;
	}
	
}

void Mesh::Active()
{

}

void Mesh::Render()
{

}

void Mesh::Update()
{
	if (mDirtyFlag)
	{
		ApplyTransform();
		mDirtyFlag = false;
	}
}

void Mesh::ApplyTransform()
{
	// create transformations
	glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	transform = glm::translate(transform, mPosition);
	transform = glm::rotate(transform, mRotation.x, glm::vec3(1, 0, 0));
	transform = glm::rotate(transform, mRotation.y, glm::vec3(0, 1, 0));
	transform = glm::rotate(transform, mRotation.z, glm::vec3(0, 0, 1));
	transform = glm::scale(transform, mScale);
	mTransform = transform;
}
