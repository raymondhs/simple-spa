/*
 * @author: Raymond
 */
#include <queue>
#include "AST.h"
#include "StmtTable.h"

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