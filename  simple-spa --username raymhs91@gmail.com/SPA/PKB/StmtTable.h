/*
 * @author Raymond Hendy Susanto
 */

#pragma once

#include <vector>
#include "../Constants.h"

class TNode;

class StmtTable {

private:
	std::vector<TNode*> idxToRef;
	StmtTable();
	StmtTable(const StmtTable &);
	StmtTable& operator=(const StmtTable &);
public:
	/**
	 * Gets a reference to statement table
	 *
	 * @return Reference to statement table
	 */
	static StmtTable* getStmtTable();

	/**
	 * Gets the size of statement table
	 *
	 * @return Size of statement table
	 */
	int getSize();

	/**
	 * Inserts a statement into statement table
	 *
	 * @param stmt Statement node to be inserted
	 * @return Number of the inserted statement
	 */
	STMT_NO insertStmt(TNode* stmt);

	/**
	 * Gets the statement node based on statement number
	 *
	 * @param idx Statement number
	 * @return Reference to the statement node
	 */
	TNode* getStmtNode(STMT_NO idx);

	/**
	 * Gets all statements in the program
	 *
	 * @return Vector of all statement numbers in the program
	 */
	std::vector<int> getAllStmt();

	/**
	 * Gets all assignments in the program
	 *
	 * @return Vector of all assignment numbers in the program
	 */
	std::vector<int> getAllAssign();

	/**
	 * Gets all while statements in the program
	 *
	 * @return Vector of all while statement numbers in the program
	 */
	std::vector<int> getAllWhile();

	/**
	 * Gets all program lines in the program
	 *
	 * @return Vector of all program line numbers in the program
	 */
	std::vector<int> getAllProgline();

	/**
	 * Clears statement table
	 */
	void clearTable();
};