#include "StmtTable.h"
#include "TNode.h"
#include "../PQL/QNode.h"
#include "VarTable.h"

#include <iostream>
#include <string>

using namespace std;

StmtTable::StmtTable() {}

StmtTable* StmtTable::getStmtTable() {
	static StmtTable stmtTable;
	return &stmtTable;
}

void StmtTable::clearTable() {
	idxToRef.clear();
}

int StmtTable::getSize() {
	return idxToRef.size();
}

STMT_NO StmtTable::insertStmt(TNode* stmt) {
	idxToRef.push_back(stmt);
	return idxToRef.size();
}

TNode* StmtTable::getStmtNode(STMT_NO idx) {
	if((unsigned)idx >= 1 && (unsigned)idx <= idxToRef.size()) {
		return idxToRef[idx-1];
	}
	return NULL;
}

TNode* StmtTable::getStmtLstNode(STMT_NO idx) {
	if((unsigned)idx >= 1 && (unsigned)idx <= idxToRef.size()) {
		return idxToRef[idx-1]->getUpLink();
	}
	return NULL;
}


std::vector<int> StmtTable::getAllStmt() {
	vector<int> result;
	for(int i = 0; i < getSize(); i++) {
		result.push_back(i+1);
	}
	return result;
}

std::vector<int> StmtTable::getAllAssign() {
	vector<int> result;
	for(int i = 0; i < getSize(); i++) {
		if(getStmtNode(i+1)->getType() == ASSIGN)
			result.push_back(i+1);
	}
	return result;
}

std::vector<int> StmtTable::getAllWhile() {
	vector<int> result;
	for(int i = 0; i < getSize(); i++) {
		if(getStmtNode(i+1)->getType() == WHILE)
			result.push_back(i+1);
	}
	return result;
}

std::vector<int> StmtTable::getAllProgline() {
	vector<int> result;
	for(int i = 0; i < getSize(); i++) {
		result.push_back(i+1);
	}
	return result;
}

std::vector<int> StmtTable::getAllIf() {
	vector<int> result;
	for(int i = 0; i < getSize(); i++) {
		if(getStmtNode(i+1)->getType() == IF)
			result.push_back(i+1);
	}
	return result;
}

std::vector<int> StmtTable::getAllStmtLst() {
	vector<int> result;
	for(int i = 0; i < getSize(); i++) {
		if (getStmtNode(i+1)->getUpLink()!= NULL){
			result.push_back(i+1);
		}
	}
	return result;
}

static string toStr(int value);
static void preorder(TNode* target,string &result);
static void preorder(QNode* target,string &result);

string toStr(int value) {
    string s = "";
    s += (value%10+'0');
    value/=10;
    while(value) {
        s = (char)(value%10+'0') + s;
        value/=10;
    }
    return s;
}

void preorder(TNode* root, string &result) {
	result += "#";
	switch(root->getType()) {
		case PLUS: result += "+"; break;
		case MINUS: result += "-"; break;
		case TIMES: result += "*"; break;
		case VAR: result += "V"+toStr(root->getAttrib()); break;
		case CONST: result += toStr(root->getAttrib()); break;
	}

    if(root->getFirstChild() !=NULL) {
		preorder(root->getFirstChild(),result);
		if(root->getFirstChild()->getRightSibling()!=NULL) {
			preorder(root->getFirstChild()->getRightSibling(),result);
		}
		else result += "#R";
	}
    else result += "#L";
}

void preorder(QNode* root, string &result) {
	result += "#";
	switch(root->getType()) {
		case QPLUS: result += "+"; break;
		case QMINUS: result += "-"; break;
		case QTIMES: result += "*"; break;
		case QVAR: 
			if(root->getIntVal()==-1) result += "V-1";
			else result += "V"+toStr(root->getIntVal());
			break;
		case QINT: result += toStr(root->getIntVal()); break;
	}

    if(root->getLeftChild() != NULL) {
		preorder(root->getLeftChild(),result);
		if(root->getLeftChild()->getRightSibling() != NULL) {
			preorder(root->getLeftChild()->getRightSibling(),result);
		}
		else result += "#R";
	}
    else result += "#L";

	
}

bool StmtTable::doesMatchPattern(TNode *stmt, QNode *pattern) {
	TNode *left = stmt->getFirstChild();
	TNode *right = left->getRightSibling();
	
	QNode *left_pattern = pattern->getLeftChild();
	QNode *right_pattern = pattern->getRightChild();

	if(left_pattern->getType() == QSTRING) {
		int varIdxLeft = VarTable::getVarTable()->getVarIndex(left_pattern->getStrVal());
		if(varIdxLeft != left->getAttrib()) return false;
	}
	
	string expr_pattern, expr_stmt;

	if(right_pattern->getType() == QANY) {
		if(right_pattern->getRightSibling() == NULL) {
			return true;
		} else {
			preorder(right_pattern->getRightSibling(),expr_pattern);
			preorder(right,expr_stmt);

			int found = expr_stmt.find(expr_pattern);
			if(found != string::npos) {
				return true;
			}
			return false;
		}
	}

	preorder(right_pattern,expr_pattern);
	
	preorder(right,expr_stmt);

	if(expr_pattern == expr_stmt) return true;
	return false;
}