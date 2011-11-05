/*
 * @author: Peter
 */
#include "ProcTable.h"
#include "../Constants.h"

using namespace std;

ProcTable::ProcTable() {}

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
	return this->idxToName[index];
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