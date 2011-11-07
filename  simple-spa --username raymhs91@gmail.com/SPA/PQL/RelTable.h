#pragma once

#include <map>
#include <string>
#include <vector>
#include "../Constants.h"

class RelTable {
private:
	std::map<std::string, std::vector< std::vector<int> > > mapper;
	RelTable();
	RelTable(const RelTable &);
	RelTable& operator=(const RelTable &);

	void insertRow(std::string relName, int arg1, int arg2);
public:
	/**
	 * Gets the relationship table
	 *
	 * @return Reference to the relationship table
	 */
	static RelTable* getRelTable();

	/**
	 * Initializes the relationship table
	 */
	void init();
	
	/**
	 * Clears the relation table
	 */
	void clearTable();

	/**
	 * Validates relationship
	 *
	 * @return True if relationship is valid, otherwise, returns False
	 */
	bool validate(std::string relName, int arg1, int arg2);
};