#pragma once
#include <memory>
class Node2D;

class INodeComponent
{
	friend class Node2D;

public:
	INodeComponent() {};
	virtual ~INodeComponent() {};

	virtual bool Init() = 0;
	virtual void Update(float detalTime) = 0;
	void AssignNode2D(Node2D* node)
	{
		mAssignedNode = node;
	};
protected:
	Node2D* mAssignedNode;


};