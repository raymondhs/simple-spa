/*
 * @author: Peter
 */

#pragma once

#include <vector>
#include <set>
#include "../Constants.h"

class AffectsTable{
private:
	std::vector<set<STMT_NO>> affectsTable;
	void fillTable(STMT_NO idx);
	AffectsTable();
	AffectsTable(const AffectsTable &);
	AffectsTable& operator=(const AffectsTable &);
public:
	AffectsTable* getAffectsTable();
	void clearTable();
	void init();
	int getSize();
};