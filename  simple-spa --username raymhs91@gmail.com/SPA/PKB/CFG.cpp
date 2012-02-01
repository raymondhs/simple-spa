/*
 * @author: Peter
 */
#include"CFG.h"

using namespace std;

CFG::CFG(){}

void CFG::addRoot(GNode* root){
	this->cfgRoots.push_back(root);
}

GNode* CFG::getCfgRoot(PROC_IDX proc){
	return cfgRoots[proc];
}

void CFG::addNode(){
	gNodeTable.push_back(new GNode(gNodeTable.size()+1));
}

GNode* CFG::getNode(STMT_NO stmt){
	return gNodeTable[stmt-1];
}

CFG* CFG::getCFG(){
	static CFG cfg;
	return &cfg;
}

void CFG::clearTable(){
	gNodeTable.clear();
	cfgRoots.clear();
}