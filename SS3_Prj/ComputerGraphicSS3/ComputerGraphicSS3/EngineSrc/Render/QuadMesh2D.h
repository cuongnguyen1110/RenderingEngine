#pragma once
#include "Mesh.h"

#include "glm/glm.hpp"
#include <memory>
class QuadMesh2D :
	public Mesh
{

public:
	 QuadMesh2D() = delete;
	~QuadMesh2D();

	QuadMesh2D(glm::vec2 pos, glm::vec2 size, glm::vec2 anchor);



	void Bind() final;
	void Active() final;
	void Render() final;
	void Update();
	void ApplyTransform();

	std::shared_ptr<QuadMesh2D> Clone();
	
	void SetPosition(glm::vec2 pos);
	void SetScale(glm::vec2 scale);
	void SetRotationZ(glm::float32 rot);

	inline glm::vec2 GetInitSize() { return mSize; }
	inline void SetQuadScale(glm::vec2 scalse) { mQuadScale = scalse; };
private:
	glm::vec2 mVerties[4];
	glm::vec2 mSize;
	glm::vec2 mQuadScale;
	glm::vec2 mAnchor;
	
};

