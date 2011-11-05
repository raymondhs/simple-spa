/*
 * @author Raymond Hendy Susanto
 */

#pragma once

#include <vector>
#include <set>
#include "../Constants.h"

class UsesTable {

private:	
	std::vector< VAR_SET > usesStmtTable;
	std::vector< VAR_SET > usesProcTable;
	UsesTable();
	UsesTable(const UsesTable &);
	UsesTable& operator=(const UsesTable &);

public:
	/**
	 * Gets a reference uses table
	 *
	 * @return Reference to uses table
	 */
	static UsesTable* getUsesTable();
	
	/**
	 * Insert a statement which uses the variable into uses table
	 *
	 * @param stmt Statement number which uses the variable
	 * @param var Index of variable which is used by the statement
	 */
	void insertStmt(STMT_NO stmt, VAR_IDX var);

	/**
	 * Inserts a procedure which uses the variable into uses table
	 *
	 * @param proc Procedure index which uses the variable
	 * @param var Index of variable which is used by the procedure
	 */
	void insertProc(PROC_IDX proc, VAR_IDX var);

	/**
	 * Gets the set of statement numbers which use the variable
	 *
	 * @param var Index of variable 
	 * @return Set of statement numbers which use the variable
	 */
	STMT_SET getStmtUsesVar(VAR_IDX var);
	
	/**
	 * Gets the set of indices of procedures which use the variable
	 *
	 * @param var Index of variable 
	 * @return Set of indices of procedures which use the variable
	 */
	PROC_SET getProcUsesVar(VAR_IDX var);

	/**
	 * Gets the set of indices of variables which are used by the statement
	 *
	 * @param stmt Statement number 
	 * @return Set of indices of variables which are used by the statement
	 */
	VAR_SET getVarUsedByStmt(STMT_NO stmt);
	
	/**
	 * Gets the set of indices of variables which are used by the procedure
	 *
	 * @param proc Index of procedure 
	 * @return Set of indices of the variables which are used by the procedure
	 */
	VAR_SET getVarUsedByProc(PROC_IDX proc);

	/**
	 * Check if a statement uses a variable
	 *
	 * @param stmt Statement number 
	 * @param var Index of variable 
	 * @return true if statement uses the variable
	 */
	bool isUsesStmt(STMT_NO stmt, VAR_IDX var);
	
	/**
	 * Check if a procedure uses a variable
	 *
	 * @param stmt Index of procedure
	 * @param var Index of variable 
	 * @return true if procedure uses the variable
	 */
	bool isUsesProc(PROC_IDX proc, VAR_IDX var);

	/**
	 * Clears the uses table
	 */
	void clearTable();
};