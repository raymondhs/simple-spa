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

	/**
	 * Gets a reference to calls table
	 *
	 * @return Reference to calls table
	 */
	static CallsTable* getCallsTable();

	/**
	 * Insert the index of the calls statement which calls a procedure
	 *
	 * @param stmt Index of the caller statement
	 * @param proc Index of the procedure called
	 */
	void insertStmt(STMT_NO stmt, PROC_IDX proc);

	/**
	 * Insert the index of the procedure which calls another procedure
	 *
	 * @param proc1 Index of the caller procedure
	 * @param proc2 Index of the procedure called
	 */
	void insertProc(PROC_IDX proc1, PROC_IDX proc2);

	void clearTable();
};