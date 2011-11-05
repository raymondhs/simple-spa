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
	static SynTable* getSynTable();
	void clearTable();

	int getSize();
	int insertSyn(std::string syn, int type);
	std::pair<std::string,int> getSyn(int idx);
	int getSynIdx(std::string name);
};