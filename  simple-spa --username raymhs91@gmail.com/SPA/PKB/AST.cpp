/*
 * @author: Raymond
 */
#include <queue>
#include "AST.h"
#include "StmtTable.h"
#include "VarTable.h"

using namespace std;

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

static string toInt(int value);
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
		case VAR: result += VarTable::getVarTable()->getVarName(root->getAttrib()); break;
		case CONST: result += toStr(root->getAttrib()); break;
	}

    if(root->getFirstChild() !=NULL)
		preorder(root->getFirstChild(),result);
    else result += "#L";

	if(root->getFirstChild()->getRightSibling()!=NULL) 
		preorder(root->getFirstChild()->getRightSibling(),result);
    else result += "#R";
}

void preorder(QNode* root, string &result) {
	result += "#";
	switch(root->getType()) {
		case QPLUS: result += "+"; break;
		case QMINUS: result += "-"; break;
		case QTIMES: result += "*"; break;
		case QVAR: result += VarTable::getVarTable()->getVarName(root->getIntVal()); break;
		case QCONST: result += toStr(root->getIntVal()); break;
	}

    if(root->getLeftChild() !=NULL)
		preorder(root->getLeftChild(),result);
    else result += "#L";

	if(root->getLeftChild()->getRightSibling()!=NULL) 
		preorder(root->getLeftChild()->getRightSibling(),result);
    else result += "#R";
}

vector<int> matchPattern(QNode* target) {
	vector<int> ans;
	StmtTable* table = StmtTable::getStmtTable();
	
	string target_str;
	preorder(target,target_str);

	for(int i = 0; i < table->getSize(); i++) {
		TNode* stmtNode = table->getStmtNode(i+1);
		if(stmtNode->getType() == ASSIGN) {
			string tmp;
			preorder(stmtNode,tmp);
			if(target_str.find(tmp)!=string::npos) {
				ans.push_back(i+1);
			}
		}
	}
	return ans;
}