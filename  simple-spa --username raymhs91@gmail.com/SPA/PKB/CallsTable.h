#pragma once

#include <vector>
#include <set>
#include "../Constants.h"

class CallsTable{
private:
	std::vector< VAR_SET > stmtCallsTable;
	std::vector< VAR_SET > procCallsTable;
	CallsTable();
	CallsTable(const CallsTable &);
	CallsTable& operator=(const CallsTable &);
public:
	static CallsTable* getCallsTable();
	void insertStmt(STMT_NO stmt, PROC_IDX proc);
	void insertProc(PROC_IDX proc1, PROC_IDX proc2);
	void clearTable();
};