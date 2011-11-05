#include "UsesTable.h"
#include <string>
#include "ProcTable.h"

using namespace std;

UsesTable::UsesTable() {}

void UsesTable::clearTable() {
	usesStmtTable.clear();
	usesProcTable.clear();
}

UsesTable* UsesTable::getUsesTable() {
	static UsesTable usesTable;
	return &usesTable;
}

void UsesTable::insertStmt(STMT_NO stmt, VAR_IDX var) {
	if((unsigned)stmt-1 >= usesStmtTable.size()) { // lazy load
		int i = usesStmtTable.size();
		while(i <= stmt-1) {
			i++;
			usesStmtTable.push_back(set<int>());
		}
	}
	usesStmtTable[stmt-1].insert(var);
}

void UsesTable::insertProc(PROC_IDX proc, VAR_IDX var) {
	if((unsigned)proc >= usesProcTable.size()) { // lazy load
		int i = usesProcTable.size();
		while(i <= proc) {
			i++;
			usesProcTable.push_back(set<int>());
		}
	}
	usesProcTable[proc].insert(var);
}

STMT_SET UsesTable::getStmtUsesVar(VAR_IDX var) {
	set<int> result;
	for(unsigned i = 0; i < usesStmtTable.size(); i++) {
		if(usesStmtTable[i].count(var) == 1) result.insert(i+1);
	}
	return result;
}

PROC_SET UsesTable::getProcUsesVar(VAR_IDX var) {
	set<int> result;
	for(unsigned i = 0; i < usesProcTable.size(); i++) {
		if(usesProcTable[i].count(var) == 1) result.insert(i);
	}
	return result;
}

VAR_SET UsesTable::getVarUsedByStmt(STMT_NO stmt) {
	unsigned stmtNo = (unsigned) stmt-1;
	if(stmtNo >= usesStmtTable.size() || stmtNo < 0) return set<int>();	
	return usesStmtTable[stmt-1];
}

VAR_SET UsesTable::getVarUsedByProc(PROC_IDX proc) {
	if((unsigned)proc>=usesProcTable.size()) return set<int>();
	return usesProcTable[proc];
}

bool UsesTable::isUsesStmt(STMT_NO stmt, VAR_IDX var) {
	return (unsigned)stmt-1<usesStmtTable.size() && (unsigned)stmt-1>=0 && usesStmtTable[stmt-1].count(var) == 1;
}

bool UsesTable::isUsesProc(PROC_IDX proc, VAR_IDX var) {
	return (unsigned)proc<usesProcTable.size() && usesProcTable[proc].count(var) == 1;
}