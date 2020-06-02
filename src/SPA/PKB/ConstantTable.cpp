/*
 * @author: Jessinca
 */
#include "ConstantTable.h"
#include <queue>
#include "StmtTable.h"
#include "../Constants.h"
#include "TNode.h"
#include "AST.h"

using namespace std;

static void DFS(TNode *root, int val, vector<TNode *> &result);

ConstantTable::ConstantTable() {}

ConstantTable* ConstantTable::getConstantTable(){
	static ConstantTable consTable;
	return &consTable;
}

void ConstantTable::clearTable() {
	constantsList.clear();
}

void ConstantTable::addConstant(TNode* constant) {
	constantsList.insert(constant->getAttrib());
}

void DFS(TNode *root, int val, vector<TNode *> &result) {
	if(root == NULL) return;
	if(root->getType() == CONST && root->getAttrib() == val) {
		result.push_back(root);
	}
	DFS(root->getFirstChild(), val, result);
	DFS(root->getRightSibling(), val, result);
}

vector<TNode*> ConstantTable::getConstNodes(int v) {
	vector<TNode*> result;
	DFS(AST::getAST()->getRoot(), v, result);
	return result;
}

std::vector<int> ConstantTable::getAllConstant() {
	return std::vector<int> (constantsList.begin(),constantsList.end());
}

std::vector<TNode*> ConstantTable::getAllConstantNodes() {
	vector<TNode*> result;
	for(set<int>::iterator it = constantsList.begin(); it != constantsList.end(); it++) {
		vector<TNode*> nodes;
		DFS(AST::getAST()->getRoot(), *it, nodes);
		for(unsigned j = 0; j < nodes.size(); j++) {
			result.push_back(nodes[j]);
		}
	}
	return result;
}