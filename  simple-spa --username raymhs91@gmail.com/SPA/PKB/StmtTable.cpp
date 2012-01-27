#include "StmtTable.h"
#include "TNode.h"

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