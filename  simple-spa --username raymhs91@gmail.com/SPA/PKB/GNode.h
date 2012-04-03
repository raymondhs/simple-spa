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
	std::vector<GNode*> nextBIP;
	std::vector<GNode*> previousBIP;
	void init();
public:
	GNode();
	GNode(int attrib);
	~GNode();
	void setAttrib(int attrib);
	void setNext(GNode *node);
	void setPrevious(GNode *node);
	void setNextBIP(GNode *node);
	void setPreviousBIP(GNode *node);
	int getAttrib();
	std::vector<GNode*> getNext();
	std::vector<GNode*> getNextTransitive();
	std::vector<GNode*> getNextBIP();
	std::vector<GNode*> getNextBIPTransitive();
	std::vector<GNode*> getPrev();
	std::vector<GNode*> getPrevTransitive();
	std::vector<GNode*> getPrevBIP();
	std::vector<GNode*> getPrevBIPTransitive();
	bool isNext(GNode *next);
	bool isNextTransitive(GNode *next);
	bool isNextBIP(GNode *next);
	bool isNextBIPTransitive(GNode *next);
	bool operator == (const GNode& g);
};

