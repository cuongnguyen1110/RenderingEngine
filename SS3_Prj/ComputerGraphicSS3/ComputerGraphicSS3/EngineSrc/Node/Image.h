#pragma once
#include "Node2D.h"



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

private:
	
	std::string mImageUrl;

	void SetMaterial(std::shared_ptr<Material> m);
};

