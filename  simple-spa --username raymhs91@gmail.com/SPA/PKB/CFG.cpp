/*
 * @author: Peter
 */
#include"CFG.h"
#include"StmtTable.h"
#include"CallsTable.h"
#include"TNode.h"
#include <string>
using namespace std;

CFG::CFG(){}

void CFG::addRoot(GNode* root){
	this->cfgRoots.push_back(root);
}

GNode* CFG::getCfgRoot(PROC_IDX proc){
	return cfgRoots[proc];
}

void CFG::addLast(vector<GNode*> last){
	this->lastElements.push_back(last);
}

vector<GNode*> CFG::getLast(PROC_IDX proc){
	return lastElements[proc];
}

vector<GNode*> CFG::getLastBIP(PROC_IDX proc){
	set<GNode*> lastBip;
	for(unsigned i=0; i<lastElements[proc].size();i++){
		GNode* u = lastElements[proc][i];
		int type = (StmtTable::getStmtTable()->getStmtNode(u->getAttrib()))->getType();
		if(type == CALL){
			vector<GNode*> called = getLastBIP(CallsTable::getCallsTable()->getProcCalledByStmt(u->getAttrib()));
			for(unsigned j=0;j<called.size();j++)
				lastBip.insert(called[j]);
		} else
			lastBip.insert(u);
	}
	return vector<GNode*>(lastBip.begin(),lastBip.end());
}

void CFG::addNode(){
	gNodeTable.push_back(new GNode(gNodeTable.size()+1));
}

GNode* CFG::getNode(STMT_NO stmt){
	if((unsigned)stmt >= 1 && (unsigned)stmt <= gNodeTable.size()) {
		return gNodeTable[stmt-1];
	}
	return NULL;
}

CFG* CFG::getCFG(){
	static CFG cfg;
	return &cfg;
}

void CFG::clearTable(){
	gNodeTable.clear();
	cfgRoots.clear();
	lastElements.clear();
}