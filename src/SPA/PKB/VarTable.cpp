/*
 * @author: Peter
 */
#include "VarTable.h"
#include "StmtTable.h"
#include "../Constants.h"
#include "TNode.h"
#include "AST.h"

using namespace std;

static void DFS(TNode *root, int val, vector<TNode *> &result);

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

void DFS(TNode *root, int val, vector<TNode *> &result) {
	if(root == NULL) return;
	if(root->getType() == VAR && root->getAttrib() == val) {
		result.push_back(root);
	}
	DFS(root->getFirstChild(), val, result);
	DFS(root->getRightSibling(), val, result);
}

vector<TNode*> VarTable::getVarNode(int v){
	vector<TNode*> result;
	DFS(AST::getAST()->getRoot(), v, result);
	return result;
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

std::vector<TNode*> VarTable::getAllVarNodes() {
	vector<TNode*> result;
	for(int i = 0; i < getSize(); i++) {
		vector<TNode*> nodes;
		DFS(AST::getAST()->getRoot(), i, nodes);
		for(unsigned j = 0; j < nodes.size(); j++) {
			result.push_back(nodes[j]);
		}
	}
	return result;
}