#pragma once

#include "../PKB/GNode.h"

class CFG
{
private:
	GNode *root;
	CFG();
	CFG(const CFG &);
	CFG& operator=(const CFG &);
public:
	static CFG* getCFG();
	void setRoot(GNode* root);
	GNode* getRoot();
	void destroy();
};

