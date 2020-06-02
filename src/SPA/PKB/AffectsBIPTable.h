/*
 * @author: Peter
 */

#pragma once

#include <vector>
#include <set>
#include "../Constants.h"

using namespace std;

class AffectsBIPTable{
private:
	std::vector<set<STMT_NO>> affectsTable;
	std::vector<set<STMT_NO>> affectedByTable;
	std::vector<bool> affectsEntryCreated;
	std::vector<bool> affectedByEntryCreated;
	void fillTable(STMT_NO idx);
	void fillTable2(STMT_NO idx);
	bool branchIn(STMT_NO from, PROC_IDX to);
	AffectsBIPTable();
	AffectsBIPTable(const AffectsBIPTable &);
	AffectsBIPTable& operator=(const AffectsBIPTable &);
public:
	static AffectsBIPTable* getAffectsBIPTable();
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