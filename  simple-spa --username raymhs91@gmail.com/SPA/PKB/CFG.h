/*
 * @author: Peter
 */
#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>
#include "../Constants.h"
#include "GNode.h"

class CFG{
private:
	std::vector< GNode* > cfgRoots; 
	std::vector< GNode*> gNodeTable;
	CFG();
	CFG(const CFG &);
	CFG& operator=(const CFG &);
public:
	static CFG* getCFG();
	void addRoot( GNode* root);
	GNode* getCfgRoot(PROC_IDX proc);
	void addNode();
	GNode* getNode(STMT_NO stmt);
	void clearTable();
};