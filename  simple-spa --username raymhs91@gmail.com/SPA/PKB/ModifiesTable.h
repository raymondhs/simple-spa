/*
 * @author Raymond Hendy Susanto
 */

#pragma once

#include <vector>
#include <set>
#include "../Constants.h"

class ModifiesTable {

private:
	std::vector< VAR_SET > modifiesStmtTable;
	std::vector< VAR_SET > modifiesProcTable;
	ModifiesTable();
	ModifiesTable(const ModifiesTable &);
	ModifiesTable& operator=(const ModifiesTable &);
public:	
	/**
	 * Gets a reference to modifies table
	 *
	 * @return Reference to modifies table
	 */
	static ModifiesTable* getModifiesTable();

	/**
	 * Inserts a statement which modifies the variable
	 *
	 * @param stmt Number of statement which modifies the variable
	 * @param var Index of variable which is modified by the statement
	 */
	void insertStmt(STMT_NO stmt, VAR_IDX var);
	
	/**
	 * Inserts a procedure which modifies the variable
	 *
	 * @param stmt Index of procedure which modifies the variable
	 * @param var Index of variable which is modified by the procedure
	 */
	void insertProc(PROC_IDX proc, VAR_IDX var);

	/**
	 * Gets the numbers of statements which modify the variable
	 *
	 * @param Index of variable
	 * @return Set of numbers of statements which modify the variable
	 */
	STMT_SET getStmtModifiesVar(VAR_IDX var);
	
	/**
	 * Gets the indices of procedures which modify the variable
	 *
	 * @param Index of variable
	 * @return Set of indices of procedures which modify the variable
	 */
	PROC_SET getProcModifiesVar(VAR_IDX var);
	
	/**
	 * Gets the indices of variables which are modified by the statement
	 *
	 * @param stmt Statement number 
	 * @return Set of indices of variables which are modified by the statement
	 */
	VAR_SET getVarModifiedByStmt(STMT_NO stmt);
	
	/**
	 * Gets the indices of variables which are modified by the procedure
	 *
	 * @param proc Index of procedure
	 * @return Set of indices of variables which are modified by the procedure
	 */
	VAR_SET getVarModifiedByProc(PROC_IDX proc);

	/**
	 * Checks if a statement modifies a variable
	 *
	 * @param stmt Statement number 
	 * @param var Index of variable 
	 * @return true if statement modifies the variable
	 */
	bool isModifiesStmt(STMT_NO stmt, VAR_IDX var);
	
	/**
	 * Checks if a procedure modifies a variable
	 *
	 * @param stmt Index of procedure
	 * @param var Index of variable 
	 * @return true if procedure modifies the variable
	 */
	bool isModifiesProc(PROC_IDX proc, VAR_IDX var);

	/**
	 * Clears the modifies table
	 */
	void clearTable();
};