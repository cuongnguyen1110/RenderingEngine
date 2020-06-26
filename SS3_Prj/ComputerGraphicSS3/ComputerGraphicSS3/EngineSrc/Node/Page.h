#pragma once
#include <memory>
#include<vector>
#include <string>

#include "Node2D.h"

class Page : public Node2D
{
public:
	Page() {};
	~Page() {};
	Page(std::string name);
	virtual bool Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	

	inline std::string GetName() { return mName; };

private:
	//std::vector<std::shared_ptr<Node>> mListNode;
	std::string mName;

};

