#pragma once
#include <memory>
#include <vector>

class Node
{
public:
	Node()
		:mIsInit(false)
	{};
	virtual ~Node() {};

	virtual bool Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;

	inline bool IsInit() { return mIsInit; };
	bool mIsInit;
	virtual bool AddNode(std::shared_ptr<Node> child)
	{
		if (child.get() != this)
		{
			
			mChildNode.push_back(child);
			//auto parent = std::shared_ptr<Node>(this);
			//child->SetParrentNode(parent);
			return true;
		}
		else
		{
			printf("WARNING!!! You can't add yourseft. \n");
			return false;
		}
	};

	//virtual void SetParrentNode(std::shared_ptr<Node> parent) { mParrent = parent; };
protected:
	std::vector<std::shared_ptr<Node>> mChildNode;
	//std::weak_ptr<Node> mParrent;

};

