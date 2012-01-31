#pragma once

#include <set>

class GNode
{
private:
	int attrib;
	std::set<GNode*> next;
	std::set<GNode*> previous;
	void init();
public:
	GNode();
	~GNode();
	GNode createNode(int attribute);
	void setNext(GNode *node);
	void setPrevious(GNode *node);
	std::set<GNode*> getNext();
	std::set<GNode*> getNextTransitive();
	std::set<GNode*> getPrevious();
	std::set<GNode*> getPreviousTransitive();
	bool isNext(GNode node1, GNode node2);
	bool isNextTransitive(GNode node1, GNode node2);
};

