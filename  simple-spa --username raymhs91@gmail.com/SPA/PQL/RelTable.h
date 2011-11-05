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
	static RelTable* getRelTable();
	void init();
	void clearTable();
	bool validate(std::string relName, int arg1, int arg2);
};