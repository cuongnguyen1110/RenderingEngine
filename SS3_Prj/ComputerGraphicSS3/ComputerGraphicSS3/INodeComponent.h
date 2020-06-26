#pragma once
class INodeComponent
{
public:
	INodeComponent() {};
	virtual ~INodeComponent() {};

	virtual bool Init() = 0;
	virtual void Update(float detalTime) = 0;

private:



};