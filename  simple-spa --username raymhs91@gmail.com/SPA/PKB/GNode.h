#pragma once

#include <set>

class GNode
{
private:
	int attribute;
	std::set<int> next;
public:
	GNode(void);
	~GNode(void);
	GNode createNode(int attribute);
	void setNext(GNode *node);
	void setPrevious(GNode *node);
	std::set<int> getNext();
	std::set<int> getNextTransitive();
	std::set<int> getPrevious();
	std::set<int> getPreviousTransitive();
	bool isNext(GNode node1, GNode node2);
	bool isNextTransitive(GNode node1, GNode node2);
};

