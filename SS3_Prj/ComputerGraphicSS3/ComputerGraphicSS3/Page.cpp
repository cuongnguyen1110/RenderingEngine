#include "Page.h"

#include "Node.h"

Page::Page(std::string name)
	:mName(name)
{

}


bool Page::Init()
{
	for (std::shared_ptr<Node> node : mChildNode)
	{
		node->Init();
	}

	return true;
};

void Page::Update(float deltatime)
{
	for (std::shared_ptr<Node> node : mChildNode)
	{
		 node-> Update(deltatime);
	}
}
void Page::Render()
{
	for (std::shared_ptr<Node> node : mChildNode)
	{
		 node-> Render();
	}
}

