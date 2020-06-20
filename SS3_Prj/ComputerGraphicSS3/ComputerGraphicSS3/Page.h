#pragma once
#include <memory>
#include<vector>
#include <string>

#include "Node.h"

class Page : public Node
{
public:
	Page(std::string name);
	bool Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	

	inline std::string GetName() { return mName; };

private:
	//std::vector<std::shared_ptr<Node>> mListNode;
	std::string mName;

};

