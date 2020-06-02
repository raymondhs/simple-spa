/*
 * @author: Raymond
 */

#include "ModifiesTable.h"
#include "../Constants.h"
#include "ProcTable.h"

using namespace std;

ModifiesTable::ModifiesTable() {}

ModifiesTable* ModifiesTable::getModifiesTable() {
	static ModifiesTable modifiesTable;
	return &modifiesTable;
}

void ModifiesTable::clearTable() {
	this->modifiesStmtTable.clear();
	this->modifiesProcTable.clear();
}

void ModifiesTable::insertStmt(STMT_NO stmt, VAR_IDX var) {
	if((unsigned)stmt-1 >= modifiesStmtTable.size()) { // lazy load
		int i = modifiesStmtTable.size();
		while(i <= stmt-1) {
			i++;
			modifiesStmtTable.push_back(set<int>());
		}
	}
	modifiesStmtTable[stmt-1].insert(var);
}

void ModifiesTable::insertProc(PROC_IDX proc, VAR_IDX var) {
	if((unsigned)proc >= modifiesProcTable.size()) { // lazy load
		int i = modifiesProcTable.size();
		while(i <= proc) {
			i++;
			modifiesProcTable.push_back(set<int>());
		}
	}
	modifiesProcTable[proc].insert(var);
}

STMT_SET ModifiesTable::getStmtModifiesVar(VAR_IDX var) {
	set<int> result;
	
	for(unsigned i = 0; i < modifiesStmtTable.size(); i++) {
		if(modifiesStmtTable[i].count(var)==1) result.insert(i+1);
	}

	return result;
}

PROC_SET ModifiesTable::getProcModifiesVar(VAR_IDX var) {
	set<int> result;
	
	for(unsigned i = 0; i < modifiesProcTable.size(); i++) {
		if(modifiesProcTable[i].count(var) == 1) result.insert(i);
	}

	return result;
}

VAR_SET ModifiesTable::getVarModifiedByStmt(STMT_NO stmt) {
	unsigned stmtNo = (unsigned) stmt-1;
	if(stmtNo >= modifiesStmtTable.size() || stmtNo < 0) return set<int>();
	return modifiesStmtTable[stmt-1];
}

VAR_SET ModifiesTable::getVarModifiedByProc(PROC_IDX proc) {
	if((unsigned)proc>=modifiesProcTable.size()) return set<int>();
	return modifiesProcTable[proc];
}

bool ModifiesTable::isModifiesStmt(STMT_NO stmt, VAR_IDX var) {
	return (unsigned)stmt-1<modifiesStmtTable.size() && (unsigned)stmt-1>= 0 && modifiesStmtTable[stmt-1].count(var) == 1;
}

bool ModifiesTable::isModifiesProc(PROC_IDX proc, VAR_IDX var) {
	return (unsigned)proc<modifiesProcTable.size() && (modifiesProcTable[proc].count(var) == 1);
}