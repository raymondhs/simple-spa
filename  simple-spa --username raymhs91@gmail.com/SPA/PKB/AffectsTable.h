/*
 * @author: Peter
 */

#pragma once

#include <vector>
#include <set>
#include "../Constants.h"

using namespace std;

class AffectsTable{
private:
	std::vector<set<STMT_NO>> affectsTable;
	std::vector<set<STMT_NO>> affectedByTable;
	void fillTable(STMT_NO idx);
	AffectsTable();
	AffectsTable(const AffectsTable &);
	AffectsTable& operator=(const AffectsTable &);
public:
	static AffectsTable* getAffectsTable();
	void clearTable();
	void init();
	int getSize();
};