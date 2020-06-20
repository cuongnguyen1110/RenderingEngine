#include "QuadMesh2D.h"
#include "GlobalDefine.h"
#include "glad/glad.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

QuadMesh2D::~QuadMesh2D()
{
	
}

QuadMesh2D::QuadMesh2D(glm::vec2 pos, glm::vec2 size, glm::vec2 anchor)
{
	//mPosition = glm::vec3(pos, 0);
	mSize = size;
	mAnchor = anchor;
	
	// build verties
	mVerties[0] = glm::vec2(pos.x, pos.y);
	mVerties[1] = glm::vec2(pos.x + mSize.x, pos.y);
	mVerties[2] = glm::vec2(pos.x + mSize.x, pos.y + mSize.y);
	mVerties[3] = glm::vec2(pos.x, pos.y + mSize.y);

	// apply anchor
	mVerties[0] = mVerties[0] - size * mAnchor;
	mVerties[1] = mVerties[1] - size * mAnchor;
	mVerties[2] = mVerties[2] - size * mAnchor;
	mVerties[3] = mVerties[3] - size * mAnchor;

	// convert to openGl view (-1 -> 1);
	glm::vec2 screenSize(SCR_WIDTH/2, SCR_HEIGHT/2);

	mVerties[0] = (mVerties[0] / (screenSize))	- glm::vec2(1,1);
	mVerties[1] = (mVerties[1] / (screenSize )) - glm::vec2(1, 1);
	mVerties[2] = (mVerties[2] / (screenSize )) - glm::vec2(1, 1);
	mVerties[3] = (mVerties[3] / (screenSize )) - glm::vec2(1, 1);
}

void QuadMesh2D::Bind()
{
	// ==== build vertex buffer ==========
	float vertices[] = {
		// pos.x , pos.y, pos.z,              uv.x, uv.y
		mVerties[0].x, mVerties[0].y, 0.0f,   0.0f, 0.0f,
		mVerties[1].x, mVerties[1].y, 0.0f,   1.0f, 0.0f,
		mVerties[2].x, mVerties[2].y, 0.0f,   1.0f, 1.0f,
		mVerties[3].x, mVerties[3].y, 0.0f,   0.0f, 1.0f,
	};

	//float vertices[] = {
	//	// pos.x , pos.y, pos.z,              uv.x, uv.y
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
	//	 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
	//	 -0.5f, 0.5f, 0.0f,   0.0f, 1.0f,
	//	 0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
	//};
	//====================================

	// ==== build Index buffer ==========
	unsigned int indices[] = {  
		0, 1, 2,   // first triangle
		0, 2, 3    // second triangle
	};


	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mIBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// specify where is position vector
	//----------------- attributeLocation, size, type,normal, stride, position of first element
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// specify where is uv vector
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void QuadMesh2D::Active()
{
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
}

void QuadMesh2D::Render()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void QuadMesh2D::Update()
{
	Mesh::Update();
}

void QuadMesh2D::ApplyTransform()
{
	// create transformations
	glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

	// apply quad scale and translate
	glm::vec3 quadScale(mQuadScale, 1);
	transform = glm::scale(transform, quadScale);
	transform = glm::translate(transform, mPosition);

	mTransform = transform;
}

void QuadMesh2D::SetPosition(glm::vec2 pos)
{
	// convert to openGL view
	glm::vec2 screenSize(SCR_WIDTH / 2, SCR_HEIGHT / 2);
	pos = (pos / (screenSize)) ;

	glm::vec3 v3Pos(pos, 0);
	Mesh::SetPosition(v3Pos);
}

void QuadMesh2D::SetScale(glm::vec2 scale)
{
	glm::vec3 v3Scale(scale, 1);
	Mesh::SetScale(v3Scale);
}
void QuadMesh2D::SetRotationZ(glm::float32 rot)
{
	glm::vec3 v3Rot(0,0, rot);
	Mesh::SetRotation(v3Rot);
}