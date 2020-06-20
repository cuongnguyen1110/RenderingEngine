#pragma once
#include <memory>
#include <vector>

class Node
{
public:
	Node() {};
	virtual ~Node() {};

	virtual bool Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual bool AddNode(std::shared_ptr<Node> child)
	{
		if (child.get() != this)
		{
			mChildNode.push_back(child);
			return true;
		}
		else
		{
			printf("WARNING!!! You can't add yourseft. \n");
			return false;
		}
	};
protected:
	std::vector<std::shared_ptr<Node>> mChildNode;

};

