/*
 * @author: Peter
 */

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
	if((unsigned)proc1 >= procCallsTable.size()) { // lazy load
		int i = procCallsTable.size();
		while(i <= proc1) {
			i++;
			procCallsTable.push_back(set<int>());
		}
	}
	procCallsTable[proc1].insert(proc2);
}

STMT_SET CallsTable::getStmtCallsProc(PROC_IDX proc) {
	set<int> result;
	
	for(unsigned i = 0; i < stmtCallsTable.size(); i++) {
		if(stmtCallsTable[i].count(proc)==1) result.insert(i+1);
	}

	return result;
}

PROC_SET CallsTable::getProcCallsProc(PROC_IDX proc) {
	set<int> result;
	
	for(unsigned i = 0; i < procCallsTable.size(); i++) {
		if(procCallsTable[i].count(proc) == 1) result.insert(i);
	}

	return result;
}

PROC_SET CallsTable::getProcCallsProcTransitive(PROC_IDX proc) {
	set<int> result,temp;
	set<int> caller = getProcCallsProc(proc);
	set<int>::iterator it,itTemp;
	for(it = caller.begin(); it!=caller.end() ; it++){
		result.insert(*it);
		temp = getProcCallsProcTransitive(*it);
		for(itTemp = temp.begin(); itTemp!=temp.end() ; itTemp++){
			result.insert(*itTemp);
		}
	}
	return result;
}

PROC_SET CallsTable::getProcCalledByStmt(STMT_NO stmt) {
	unsigned stmtNo = (unsigned) stmt-1;
	if(stmtNo >= stmtCallsTable.size() || stmtNo < 0) return set<int>();
	return stmtCallsTable[stmt-1];
}

PROC_SET CallsTable::getProcCalledByProc(PROC_IDX proc) {
	unsigned procIDX = (unsigned) proc;
	if(procIDX >= procCallsTable.size() || procIDX < 0) return set<int>();
	return procCallsTable[proc];
}

PROC_SET CallsTable::getProcCalledByProcTransitive(PROC_IDX proc) {
	set<int> result,temp;
	set<int> caller = getProcCalledByProc(proc);
	set<int>::iterator it,itTemp;
	for(it = caller.begin(); it!=caller.end() ; it++){
		result.insert(*it);
		temp = getProcCalledByProcTransitive(*it);
		for(itTemp = temp.begin(); itTemp!=temp.end() ; itTemp++){
			result.insert(*itTemp);
		}
	}
	return result;
}

bool CallsTable::stmtCallsProc(STMT_NO stmt, PROC_IDX proc){
	return (unsigned)stmt-1<stmtCallsTable.size() && (unsigned)stmt-1>= 0 && stmtCallsTable[stmt-1].count(proc) == 1;
}

bool CallsTable::procCallsProc(PROC_IDX proc1, PROC_IDX proc2){
	return (unsigned)proc1<procCallsTable.size() && (unsigned)proc1-1>= 0 && procCallsTable[proc1].count(proc2) == 1;
}