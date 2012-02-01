/*
 * @author: Peter
 */

#pragma once

#include <vector>
#include <set>
#include "../Constants.h"

class CallsTable{
private:
	std::vector< PROC_IDX > stmtCallsTable;
	std::vector< PROC_SET > procCallsTable;
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

	/**
	 * Get the indices of the statements which calls the specified procedure
	 *
	 * @param proc Index of the procedure called
	 * @return Set of indices of the statements which calls the specified procedure
	 */
	STMT_SET getStmtCallsProc(PROC_IDX proc);

	PROC_IDX getProcCalledByStmt(STMT_NO stmt);

	/**
	 * Get the indices of the procedures which calls the specified procedure
	 *
	 * @param proc Index of the procedure called
	 * @return Set of indices of the statements which calls the specified procedure
	 */
	PROC_SET getProcCallsProc(PROC_IDX proc);

	PROC_SET getProcCallsProcTransitive(PROC_IDX proc);

	/**
	 * Get the indices of the procedures called by the specified statement
	 *
	 * @param stmt Index of the statement calling the procedures
	 * @return Index of the procedure called by the specified statement
	 */
	PROC_IDX CallsTable::getProcCalledByStmt(STMT_NO stmt);

	/**
	 * Get the indices of the procedures called by the specified procedure
	 *
	 * @param proc Index of the procedure calling the procedures
	 * @return Set of indices of the procedures called by the specified procedure
	 */
	PROC_SET getProcCalledByProc(PROC_IDX proc);

	PROC_SET getProcCalledByProcTransitive(PROC_IDX proc);

	/**
	 * Checks if a statement calls a procedure
	 *
	 * @param stmt Statement number 
	 * @param proc Index of procedure
	 * @return true if statement calls the procedure
	 */
	bool stmtCallsProc(STMT_NO stmt, PROC_IDX proc);

	/**
	 * Checks if a procedure calls another procedure
	 *
	 * @param proc1 Index of the caller procedure 
	 * @param proc2 Index of the procedure called
	 * @return true if proc1 calls the proc2
	 */
	bool procCallsProc(PROC_IDX proc1, PROC_IDX proc2);

	bool procCallsProcTransitive(PROC_IDX proc1, PROC_IDX proc2);

	std::vector<int> getAllCall();

	void clearTable();
};