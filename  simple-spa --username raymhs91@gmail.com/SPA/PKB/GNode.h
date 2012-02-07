/*
	@author: Richard
*/
#pragma once

#include <vector>

class GNode
{
private:
	int attrib;
	std::vector<GNode*> next;
	std::vector<GNode*> previous;
	void init();
public:
	GNode();
	GNode(int attrib);
	~GNode();
	void setAttrib(int attrib);
	void setNext(GNode *node);
	void setPrevious(GNode *node);
	int getAttrib();
	std::vector<GNode*> getNext();
	std::vector<GNode*> getNextTransitive();
	std::vector<GNode*> getPrev();
	std::vector<GNode*> getPrevTransitive();
	bool isNext(GNode *next);
	bool isNextTransitive(GNode *next);
	bool operator == (const GNode& g);
};

