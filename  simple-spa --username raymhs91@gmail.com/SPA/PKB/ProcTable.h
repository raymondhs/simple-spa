/*
 * @author Peter Phandi
 */

#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>
#include "TNode.h"
#include "../Constants.h"

class ProcTable {

private:
	std::map< PROC_NAME, PROC_IDX > nameToIdx;
	std::vector< PROC_NAME > idxToName;
	ProcTable();
	ProcTable(const ProcTable &);
	ProcTable& operator=(const ProcTable &);
public:
	/**
	 * Gets a reference to procedure table
	 *
	 * @return Reference to procedure table
	 */
	static ProcTable* getProcTable();

	/**
	 * Gets the procedure node in the AST
	 *
	 * @param index index of a procedure
	 * @return Reference to the AST procedure node of the procedure index
	 */
	static TNode* getProcNode(PROC_IDX index);

	/**
	 * Inserts a procedure into procedure table
	 *
	 * @param procName Procedure name to be inserted
	 * @return Index of the inserted procedure
	 */
	PROC_IDX insertProc(PROC_NAME procName);

	/**
	 * Gets the size of procedure table
	 *
	 * @return Size of procedure table
	 */
	int getSize();

	/**
	 * Gets the name of a procedure with the specified index
	 *
	 * @param index Index of procedure
	 * @return The procedure name
	 */
	PROC_NAME getProcName(PROC_IDX index);

	/**
	 * Gets the index of procedure with the specified name
	 *
	 * @param procName Procedure name
	 * @return Index of the procedure
	 */
	PROC_IDX getProcIndex(PROC_NAME procName);

	/**
	 * Gets all procedures in the program
	 *
	 * @return Vector of procedures indices in the program
	 */

	std::vector<int> getAllProc();
	/**
	 * Clears the procedure table
	 */
	void clearTable();
};