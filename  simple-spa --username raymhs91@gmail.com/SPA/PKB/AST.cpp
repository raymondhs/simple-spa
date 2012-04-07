/*
 * @author: Raymond
 */
#include "AST.h"

#include "StmtTable.h"
#include "ProcTable.h"
#include "ConstantTable.h"
#include "VarTable.h"

using namespace std;

static vector<TNode*> getNode(QNodeType type, int value);
static bool notOpHasChildNotOp(vector<TNode*> n1, vector<TNode*> n2);
static bool notOpHasChildOp(vector<TNode*> n1, NodeType type2);
static bool opHasChildNotOp(NodeType type1, vector<TNode*> n2);
static bool opHasChildOp(NodeType type1, NodeType type2);
static bool checkDFS(TNode *root, NodeType type1, NodeType type2);

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

vector<TNode*> getNode(QNodeType type, int value) {
	vector<TNode *> result;
	switch(type) {
		case QSTMT:
		case QASSIGN:
		case QWHILE:
		case QIF:
			result.push_back(StmtTable::getStmtTable()->getStmtNode(value)); break;
		case QPROC:
			result.push_back(ProcTable::getProcTable()->getProcNode(value)); break;
		case QSTMTLST:
			result.push_back(StmtTable::getStmtTable()->getStmtLstNode(value)); break;
		case QCONST:
			result = ConstantTable::getConstantTable()->getConstNodes(value); break;
		case QVAR:
			result = VarTable::getVarTable()->getVarNode(value); break;
	}
	return result;
}

bool AST::contains(QNodeType t1, int v1, QNodeType t2, int v2) {
	vector<TNode*> n1, n2;
	NodeType type1, type2;
	if(t1 != QPLUS && t1 != QMINUS && t1 != QTIMES) n1 = getNode(t1, v1);
	else {
		if(t1 == QPLUS) type1 = PLUS;
		else if(t1 ==QMINUS) type1 = MINUS;
		else if(t1 ==QTIMES) type1 = TIMES;
	}
	if(t2 != QPLUS && t2 != QMINUS && t2 != QTIMES) n2 = getNode(t2, v2);
	else {
		if(t2 == QPLUS) type2 = PLUS;
		else if(t2 ==QMINUS) type2 = MINUS;
		else if(t2 ==QTIMES) type2 = TIMES;
	}

	if(n1.size() == 0 && n2.size() == 0) {
		return opHasChildOp(type1, type2);
	} else if(n1.size() == 0) {
		return opHasChildNotOp(type1, n2);
	} else if(n2.size() == 0) {
		return notOpHasChildOp(n1, type2);
	} else {
		return notOpHasChildNotOp(n1, n2);
	}
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
}