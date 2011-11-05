/*
* @author Jessinca N Jong
*/

#pragma once

#include <vector>
#include "../PKB/TNode.h"

class ConstantTable{
private :
	std::set<int> constantsList;
	ConstantTable();
	ConstantTable(const ConstantTable &);
	ConstantTable& operator=(const ConstantTable &);
	
public:
	/**
	 * Gets a reference to constant table
	 *
	 * @return Reference to constant table
	 */
	static ConstantTable* getConstantTable();

	/**
	 * Inserts a constant into constant table
	 *
	 * @param constant TNode of type constant to be inserted
	 */
	void addConstant(TNode* constant);

	/**
	 * Gets all constants in the program
	 *
	 * @return Vector of all constants in the program
	 */
	std::vector<int> getAllConstant();

	/**
	 * Clears the constant table
	 */
	void clearTable();
};