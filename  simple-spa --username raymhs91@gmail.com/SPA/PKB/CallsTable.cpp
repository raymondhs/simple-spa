
#include "CallsTable.h"
#include "ProcTable.h"

using namespace std;

CallsTable::CallsTable() {}

CallsTable* CallsTable::getCallsTable() {
	static CallsTable callsTable;
	return &callsTable;
}

void CallsTable::clearTable() {
	this->stmtCallsTable.clear();
	this->procCallsTable.clear();
}

void CallsTable::insertStmt(STMT_NO stmt, PROC_IDX proc) {
	if((unsigned)stmt-1 >= stmtCallsTable.size()) { // lazy load
		int i = stmtCallsTable.size();
		while(i <= stmt-1) {
			i++;
			stmtCallsTable.push_back(set<int>());
		}
	}
	stmtCallsTable[stmt-1].insert(proc);
}

void CallsTable::insertProc(PROC_IDX proc1, PROC_IDX proc2) {
	if((unsigned)proc1-1 >= procCallsTable.size()) { // lazy load
		int i = procCallsTable.size();
		while(i <= proc1-1) {
			i++;
			procCallsTable.push_back(set<int>());
		}
	}
	procCallsTable[proc1-1].insert(proc2);
}