/*
 * @author: Peter
 */
#include "ProcTable.h"
#include "../Constants.h"
#include "AST.h"
#include "TNode.h"

using namespace std;

ProcTable::ProcTable() {}

TNode* ProcTable::getProcNode(PROC_IDX procIdx){
	TNode* rootNode, *currProcNode, *procNode;
	AST* ast;
	rootNode = ast->getAST()->getRoot();
	currProcNode = rootNode->getFirstChild();
	while(currProcNode!=NULL){
		if(procIdx==currProcNode->getAttrib()){
			procNode = currProcNode;
			break;
		} else {
			currProcNode = currProcNode->getRightSibling();
		}
	}
	return procNode;
}

PROC_IDX ProcTable::insertProc(PROC_NAME procName){
	int index = getProcIndex(procName);
	if(index==-1){
		index = idxToName.size();
		nameToIdx.insert(pair<string,int>(procName,index));
		idxToName.push_back(procName);
	}
	return index;
}

int ProcTable::getSize(){
	return this->idxToName.size();
}

PROC_NAME ProcTable::getProcName(PROC_IDX index){
	if(index<getSize()&&index>=0) 
		return this->idxToName[index];
	else
		return "OUT OF BOUNDS";
}

PROC_IDX ProcTable::getProcIndex(PROC_NAME procName){
	map<string, int>::iterator iter = nameToIdx.find(procName);
	if (iter != nameToIdx.end())
		return iter->second;
	else
		return -1;
}

ProcTable* ProcTable::getProcTable(){
	static ProcTable procTable;
	return &procTable;
}

void ProcTable::clearTable(){
	nameToIdx.clear();
	idxToName.clear();
}

std::vector<int> ProcTable::getAllProc() {
	vector<int> result;
	for(int i = 0; i < getSize(); i++) {
		result.push_back(i);
	}
	return result;
}