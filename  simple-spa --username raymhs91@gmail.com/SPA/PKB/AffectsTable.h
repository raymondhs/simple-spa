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
	std::vector<STMT_NO> getAffects(STMT_NO affects);
	std::vector<STMT_NO> getAffectsTransitive(STMT_NO affects);
	std::vector<STMT_NO> getAffectedBy(STMT_NO affected);
	std::vector<STMT_NO> getAffectedByTransitive(STMT_NO affected);
	bool isAffects(STMT_NO affects, STMT_NO affected);
	bool isAffectsTransitive(STMT_NO affects, STMT_NO affected);
	int getSize();
};