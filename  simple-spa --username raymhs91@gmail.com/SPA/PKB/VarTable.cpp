/*
 * @author: Peter
 */
#include "VarTable.h"

using namespace std;

VarTable::VarTable(){}

int VarTable::insertVar(std::string varName){
	int index = getVarIndex(varName);
	if(index==-1){
		index = idxToName.size();
		nameToIdx.insert(pair<string,int>(varName,index));
		idxToName.push_back(varName);
	}
	return index;
}

int VarTable::getSize(){
	return this->idxToName.size();
}

string VarTable::getVarName(int index){
	return this->idxToName[index];
}

int VarTable::getVarIndex(string varName){
	map<string, int>::iterator iter = nameToIdx.find(varName);
	if (iter != nameToIdx.end())
		return iter->second;
	else
		return -1;
}

VarTable* VarTable::getVarTable(){
	static VarTable varTable;
	return &varTable;
}

void VarTable::clearTable(){
	nameToIdx.clear();
	idxToName.clear();
}

std::vector<int> VarTable::getAllVar() {
	vector<int> result;
	for(int i = 0; i < getSize(); i++) {
		result.push_back(i);
	}
	return result;
}