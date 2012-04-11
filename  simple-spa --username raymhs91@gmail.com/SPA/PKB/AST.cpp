/*
 * @author: Raymond
 */
#include "AST.h"

#include "StmtTable.h"
#include "ProcTable.h"
#include "ConstantTable.h"
#include "VarTable.h"
#include "CallsTable.h"

using namespace std;

static vector<TNode*> getNode(QNodeType type, int value);
static bool DFS_contains(TNode *root, TNode *target);
/*static bool isOp(NodeType t);
static bool notOpHasChildNotOp(vector<TNode*> n1, vector<TNode*> n2);
static bool notOpHasChildOp(vector<TNode*> n1, NodeType type2);
static bool opHasChildNotOp(NodeType type1, vector<TNode*> n2);
static bool opHasChildOp(NodeType type1, NodeType type2);
static bool checkDFS(TNode *root, NodeType type1, NodeType type2);*/
static void checkTree(TNode* root, NodeType type, vector<int>& result);

AST::AST() {}

void AST::setRoot(TNode* root) {
	this->root = root;
}

TNode* AST::getRoot() {
	return this->root;
}

AST* AST::getAST(){
	static AST ast;
	return &ast;
}

void AST::destroy() {
	delete root;
}
#include <iostream>
vector<TNode*> getNode(QNodeType type, int value) {
	vector<TNode *> result;
	vector<int> tmp;
	switch(type) {
		case QPROGLINE:
		case QSTMT:
		case QASSIGN:
		case QWHILE:
		case QIF:
		case QCALL:
			result.push_back(StmtTable::getStmtTable()->getStmtNode(value)); break;
		case QPROC:
			result.push_back(ProcTable::getProcTable()->getProcNode(value)); break;
		case QSTMTLST:
			result.push_back(StmtTable::getStmtTable()->getStmtLstNode(value)); break;
		case QCONST:
			result = ConstantTable::getConstantTable()->getConstNodes(value); break;
		case QVAR:
			result = VarTable::getVarTable()->getVarNode(value); break;
		case QPLUS:
		case QMINUS:
		case QTIMES:
			result.push_back((TNode *)value); break;
	}
	return result;
}



bool AST::contains(QNodeType t1, int v1, QNodeType t2, int v2) {
	vector<TNode*> n1, n2;
	
	n1 = getNode(t1, v1);
	n2 = getNode(t2, v2);

	int i,j;
	for (i=0;(unsigned)i<n1.size();i++){
		for (j=0;(unsigned)j<n2.size();j++){
			TNode *cur = n2[j];
			while(cur->getLeftSibling()) cur = cur->getLeftSibling();
			if (cur->getUpLink()==n1[i]) return true;
		}
	}

	return false;
}

bool AST::containsT(QNodeType t1, int v1, QNodeType t2, int v2) {
	vector<TNode*> n1, n2;
	
	n1 = getNode(t1, v1);
	n2 = getNode(t2, v2);

	int i,j;
	for (i=0;(unsigned)i<n1.size();i++){
		for (j=0;(unsigned)j<n2.size();j++){
			TNode *root = n1[i], *target = n2[j];
			if(DFS_contains(root, target)) return true;
		}
	}
	return false;
}

bool DFS_contains(TNode *root, TNode *target) {
	if(root == NULL) return false;
	if(root == target) return true;
	return DFS_contains(root->getFirstChild(), target)
		|| DFS_contains(root->getLeftSibling(), target);
}

bool AST::sibling(QNodeType t1, int v1, QNodeType t2, int v2) {
	vector<TNode*> n1, n2;

	n1 = getNode(t1, v1);
	n2 = getNode(t2, v2);

	int i,j;
	for (i=0;(unsigned)i<n1.size();i++){
		for (j=0;(unsigned)j<n2.size();j++){
			TNode *cur1 = n1[i], *cur2 = n2[j];
			if(cur1 == cur2) continue;
			while(cur1->getLeftSibling()) { cur1 = cur1->getLeftSibling(); }
			while(cur2->getLeftSibling()) { cur2 = cur2->getLeftSibling(); }
			if(cur1 == cur2) return true;
		}
	}

	return false;
}

vector <int> AST::getAllPlus(){
	TNode* root = AST::getAST()->getRoot();
	vector<int> result;
	checkTree(root,PLUS,result);
	return result;
}

vector <int> AST::getAllMinus(){
	TNode* root = AST::getAST()->getRoot();
	vector<int> result;
	checkTree(root,MINUS,result);
	return result;
}

vector <int> AST::getAllTimes(){
	TNode* root = AST::getAST()->getRoot();
	vector<int> result;
	checkTree(root,TIMES,result);
	return result;
}

void checkTree(TNode* root, NodeType type, vector<int>& result){
	if(root == NULL) return;
	if(root->getType()==type){
		result.push_back((int)root);
	}
	checkTree(root->getFirstChild(),type,result);
	checkTree(root->getRightSibling(),type,result);
}

/*bool isOp(NodeType t) {
	return t == PLUS || t == MINUS || t == TIMES;
}

bool notOpHasChildNotOp(vector<TNode*> n1, vector<TNode*> n2){
	int i,j;
	for (i=0;(unsigned)i<n1.size();i++){
		for (j=0;(unsigned)j<n2.size();j++){
			TNode *cur = n2[j];
			while(cur->getLeftSibling()) cur = cur->getLeftSibling();
			if (cur->getUpLink()==n1[i]) return true;
		}
	}
	return false;
}

bool notOpHasChildOp(vector<TNode*> n1, NodeType type2){
	int i;
	for (i=0;(unsigned)i<n1.size();i++){
		TNode* curr = n1[i]->getFirstChild();
		while(curr!=NULL){
			if(type2==curr->getType()) return true;
			curr = curr->getRightSibling();
		}
	}
	return false;
}

bool opHasChildNotOp(NodeType type1, vector<TNode*> n2){
	int i;
	for (i=0;(unsigned)i<n2.size();i++){
		TNode* curr = n2[i];
		while(curr->getLeftSibling()) curr = curr->getLeftSibling();
		if(curr->getType()==type1) return true;
	}
	return false;
}

bool opHasChildOp(NodeType type1, NodeType type2){
	TNode* root = AST::getAST()->getRoot();
	return checkDFS(root,type1,type2);
}

bool checkDFS(TNode *root, NodeType type1, NodeType type2) {
	if(root == NULL) return false;
	TNode* temp=root->getFirstChild();
	while(temp!=NULL){
		if(root->getType()==type1 && temp->getType() == type2) return true;
		temp=temp->getRightSibling();
	}
	return checkDFS(root->getFirstChild(), type1, type2) || checkDFS(root->getRightSibling(), type1, type2);
}*/
