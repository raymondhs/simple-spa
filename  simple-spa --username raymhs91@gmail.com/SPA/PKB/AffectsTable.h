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
	std::vector<bool> affectsEntryCreated;
	std::vector<bool> affectedByEntryCreated;
	void fillTable(STMT_NO idx);
	void fillTable2(STMT_NO idx);
	AffectsTable();
	AffectsTable(const AffectsTable &);
	AffectsTable& operator=(const AffectsTable &);
public:
	static AffectsTable* getAffectsTable();
	void clearTable();
	void init();
	std::set<STMT_NO> getAffects(STMT_NO affects);
	std::set<STMT_NO> getAffectsTransitive(STMT_NO affects);
	std::set<STMT_NO> getAffectedBy(STMT_NO affected);
	std::set<STMT_NO> getAffectedByTransitive(STMT_NO affected);
	bool isAffects(STMT_NO affects, STMT_NO affected);
	bool isAffectsTransitive(STMT_NO affects, STMT_NO affected);
	int getSize();
};