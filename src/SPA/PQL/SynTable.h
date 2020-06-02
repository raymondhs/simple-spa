#pragma once

#include <map>
#include <string>
#include <vector>
#include "../Constants.h"

class SynTable {
private:
	std::vector< std::pair<std::string,int> > idxMapper;
	std::map<std::string,int> nameMapper;
	SynTable();
	SynTable(const SynTable &);
	SynTable& operator=(const SynTable &);
public:
	/**
	 * Gets the synonym table
	 *
	 * @return Reference to the synonym table
	 */
	static SynTable* getSynTable();

	/**
	 * Clears the synonym table
	 */
	void clearTable();

	/**
	 * Gets the size of synonym table
	 *
	 * @return Size of synonym table
	 */
	int getSize();

	/**
	 * Inserts a new synonym and its type
	 *
	 * @return Index of the new synonym in the synonym table if insertion is successful, otherwise, returns -1
	 */
	int insertSyn(std::string syn, int type);

	/**
	 * Gets a synonym by index
	 *
	 * @param idx Index of synonym in the synonym table
	 * @return Pair of synonym name and its type
	 */
	std::pair<std::string,int> getSyn(int idx);

	/**
	 * Gets synonym index by name
	 *
	 * @param name Name of the synonym
	 * @return Index of the synonym in the synonym table
	 */
	int getSynIdx(std::string name);
};