/*
 * @author Peter Phandi
 */

#pragma once

#include <string>
#include <map>
#include <vector>
#include "../Constants.h"
#include "TNode.h"

class VarTable {

private:
	std::map<std::string, int> nameToIdx;
	std::vector<std::string> idxToName;
	VarTable();
	VarTable(const VarTable &);
	VarTable& operator=(const VarTable &);

public:
	/**
	 * Gets a reference to variable table
	 * 
	 * @return Reference to variable table
	 */
	static VarTable* getVarTable();

	/**
	 * Inserts a variable into variable table
	 * 
	 * @param varName Variable name to be inserted
	 * @return Index of the inserted variable
	 */
	VAR_IDX insertVar(std::string varName);

	/**
	 * Gets the size of variable table
	 *
	 * @return Size of the variable table
	 */
	int getSize();

	/**
	 * Gets the name of a variable with the specified index
	 *
	 * @param index Index of variable
	 * @return The name of the variable
	 */
	std::string getVarName(VAR_IDX index);

	/**
	 * Gets the index of a variable with the specified name
	 *
	 * @param varName Variable name
	 * @return Index of the variable
	 */
	VAR_IDX getVarIndex(std::string varName);

	/**
	 * return all AST Node reference that has attribute value
	 *
	 * @param value variable index
	 */
	std::vector<TNode*> getVarNode(int value);
	
	/**
	 * Gets all variables in the program
	 *
	 * @return Vector of variable indices in the program
	 */
	std::vector<int> getAllVar();

	/**
	 * Clears the variable table
	 */
	void clearTable();
};