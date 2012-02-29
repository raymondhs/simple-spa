/*
* @author: Peter
*/

#include "AffectsTable.h"
#include "StmtTable.h"
#include "ModifiesTable.h"
#include "UsesTable.h"
#include "CFG.h"
#include "TNode.h"
#include <queue>

using namespace std;

AffectsTable::AffectsTable(){}

AffectsTable* AffectsTable::getAffectsTable() {
	static AffectsTable affectsTable;
	return &affectsTable;
}

void AffectsTable::clearTable(){
	this->affectsTable.clear();
	this->affectedByTable.clear();
	affectsEntryCreated.clear();
	affectedByEntryCreated.clear();
}

void AffectsTable::init(){
	vector<STMT_NO> assign = StmtTable::getStmtTable()->getAllAssign();
	affectsEntryCreated.assign(StmtTable::getStmtTable()->getSize(),false);
	affectedByEntryCreated.assign(StmtTable::getStmtTable()->getSize(),false);
}

int AffectsTable::getSize(){
	return this->affectsTable.size();
}

void AffectsTable::fillTable(STMT_NO stmt){
	if(StmtTable::getStmtTable()->getStmtNode(stmt)->getType()!=ASSIGN) return;
	for(int i=this->affectsTable.size()-1; i<stmt; i++){
		this->affectsTable.push_back(set<int>());
	}
	int var = *(ModifiesTable::getModifiesTable()->getVarModifiedByStmt(stmt).begin());
	//BFS
	queue<GNode*> q;
	q.push(CFG::getCFG()->getNode(stmt));

	vector<bool> visited(StmtTable::getStmtTable()->getSize(), false);

	while (!q.empty()) {
		GNode* u = q.front(); q.pop();
		vector<GNode*> next = u->getNext();
		vector<GNode*>::iterator it;

		for (it = next.begin(); it < next.end(); it++) {
			GNode* v = *it;
			int idx = v->getAttrib();
			int type = StmtTable::getStmtTable()->getStmtNode(idx)->getType();
			if (visited[idx-1] == false) {
				visited[idx-1] = true;
				if(type==ASSIGN&&UsesTable::getUsesTable()->isUsesStmt(idx,var)){
					for(int i=this->affectedByTable.size()-1; i<idx; i++){
						this->affectedByTable.push_back(set<int>());
					}
					affectsTable[stmt-1].insert(idx);
					affectedByTable[idx-1].insert(stmt);
				}
				if((type==ASSIGN||type==CALL)&&ModifiesTable::getModifiesTable()->isModifiesStmt(idx,var))
					continue;
				q.push(v);
			}
		}
	}
}

void AffectsTable::fillTable2(STMT_NO stmt){
	if(StmtTable::getStmtTable()->getStmtNode(stmt)->getType()!=ASSIGN) return;
	queue<GNode*> q;
	q.push(CFG::getCFG()->getNode(stmt));

	vector<bool> visited(StmtTable::getStmtTable()->getSize(), false);

	while (!q.empty()) {
		GNode* u = q.front(); q.pop();
		vector<GNode*> prev = u->getPrev();
		vector<GNode*>::iterator it;

		for (it = prev.begin(); it < prev.end(); it++) {
			GNode* v = *it;
			int idx = v->getAttrib();
			int type = StmtTable::getStmtTable()->getStmtNode(idx)->getType();
			if (visited[idx-1] == false) {
				visited[idx-1] = true;
			if(!affectsEntryCreated[idx-1])
				fillTable(idx);
			q.push(v);
			}
		}
	}
}

set<STMT_NO> AffectsTable::getAffects(STMT_NO affects){
	if(!affectsEntryCreated[affects-1])
		fillTable(affects);
	affectsEntryCreated[affects-1] = true;
	return affectsTable[affects-1];
}

set<STMT_NO> AffectsTable::getAffects(STMT_NO affected){
	if(!affectedByEntryCreated[affected-1])
		fillTable2(affected);
	affectedByEntryCreated[affected-1] = true;
	return affectedByTable[affected-1];
}

bool AffectsTable::isAffects(STMT_NO affects, STMT_NO affected){
	set<STMT_NO> entry = getAffects(affects);
	return (entry.find(affected)!=entry.end());
}

