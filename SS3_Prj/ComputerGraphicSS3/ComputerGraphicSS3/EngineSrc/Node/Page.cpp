#include "Page.h"

#include "Node2D.h"

Page::Page(std::string name)
	:mName(name)
{

}


bool Page::Init()
{
	return Node2D::Init();
};

void Page::Update(float deltatime)
{
	Node2D::Update(deltatime);
}
void Page::Render()
{
	Node2D::Render();
}

