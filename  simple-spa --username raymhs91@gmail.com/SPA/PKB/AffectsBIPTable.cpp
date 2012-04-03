/*
* @author: Peter
*/

#include "AffectsBIPTable.h"
#include "StmtTable.h"
#include "CallsTable.h"
#include "ModifiesTable.h"
#include "UsesTable.h"
#include "CFG.h"
#include "TNode.h"
#include <queue>

using namespace std;

AffectsBIPTable::AffectsBIPTable(){
}

AffectsBIPTable* AffectsBIPTable::getAffectsBIPTable() {
	static AffectsBIPTable AffectsBIPTable;
	return &AffectsBIPTable;
}

void AffectsBIPTable::clearTable(){
	this->affectsTable.clear();
	this->affectedByTable.clear();
	affectsEntryCreated.clear();
	affectedByEntryCreated.clear();
}

void AffectsBIPTable::init(){
	vector<STMT_NO> assign = StmtTable::getStmtTable()->getAllAssign();
	affectsEntryCreated.assign(StmtTable::getStmtTable()->getSize(),false);
	affectedByEntryCreated.assign(StmtTable::getStmtTable()->getSize(),false);
}

int AffectsBIPTable::getSize(){
	return this->affectsTable.size();
}

bool AffectsBIPTable::branchIn(STMT_NO from, PROC_IDX to){
	bool canReturn=false;
	for(int i=this->affectsTable.size()-1; i<from; i++){
		this->affectsTable.push_back(set<int>());
	}
	int var = *(ModifiesTable::getModifiesTable()->getVarModifiedByStmt(from).begin());
	//BFS
	queue<GNode*> q;
	vector<bool> visited(StmtTable::getStmtTable()->getSize(), false);


	//check for the root
	int idx,type;	
	idx = CFG::getCFG()->getCfgRoot(to)->getAttrib();
	type = StmtTable::getStmtTable()->getStmtNode(idx)->getType();
	if (visited[idx-1] == false) {
		visited[idx-1] = true;
		if(type==ASSIGN&&UsesTable::getUsesTable()->isUsesStmt(idx,var)){
			for(int i=this->affectedByTable.size()-1; i<idx; i++){
				this->affectedByTable.push_back(set<int>());
			}
			affectsTable[from-1].insert(idx);
			affectedByTable[idx-1].insert(from);
		}
		if((type==ASSIGN)&&ModifiesTable::getModifiesTable()->isModifiesStmt(idx,var))
			return false;
		if(type==CALL){
			if(!branchIn(from,CallsTable::getCallsTable()->getProcCalledByStmt(idx)))
				return false;
		}
		q.push(CFG::getCFG()->getCfgRoot(to));
	}

	while (!q.empty()) {
		GNode* u = q.front(); q.pop();
		vector<GNode*> next = u->getNext();
		vector<GNode*>::iterator it;
		if(next.size()==0)
			canReturn=true;
		for (it = next.begin(); it < next.end(); it++) {
			GNode* v = *it;
			idx = v->getAttrib();
			type = StmtTable::getStmtTable()->getStmtNode(idx)->getType();
			if (visited[idx-1] == false) {
				visited[idx-1] = true;
				if(type==ASSIGN&&UsesTable::getUsesTable()->isUsesStmt(idx,var)){
					for(int i=this->affectedByTable.size()-1; i<idx; i++){
						this->affectedByTable.push_back(set<int>());
					}
					affectsTable[from-1].insert(idx);
					affectedByTable[idx-1].insert(from);
				}
				if((type==ASSIGN)&&ModifiesTable::getModifiesTable()->isModifiesStmt(idx,var))
					continue;
				if(type==CALL){
					if(!branchIn(from,CallsTable::getCallsTable()->getProcCalledByStmt(idx)))
						continue;
				}
				q.push(v);
			}
		}
	}
	return canReturn;
}

void AffectsBIPTable::fillTable(STMT_NO stmt){	
	for(int i=this->affectsTable.size()-1; i<stmt; i++){
		this->affectsTable.push_back(set<int>());
	}
	if(StmtTable::getStmtTable()->getStmtNode(stmt)->getType()!=ASSIGN) return;
	int var = *(ModifiesTable::getModifiesTable()->getVarModifiedByStmt(stmt).begin());
	//BFS
	queue<GNode*> q;
	q.push(CFG::getCFG()->getNode(stmt));

	vector<bool> visited(StmtTable::getStmtTable()->getSize(), false);

	while (!q.empty()) {
		GNode* u = q.front(); q.pop();
		vector<GNode*> next = u->getNext();
		vector<GNode*>::iterator it;
		if(next.size()==0){
			next = u->getNextBIP();
		}
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
				if((type==ASSIGN)&&ModifiesTable::getModifiesTable()->isModifiesStmt(idx,var))
					continue;
				if(type==CALL){
					if(!branchIn(stmt,CallsTable::getCallsTable()->getProcCalledByStmt(idx)))
						continue;
				}
				q.push(v);
			}
		}
	}
}

void AffectsBIPTable::fillTable2(STMT_NO stmt){
	for(int i=this->affectedByTable.size()-1; i<stmt; i++){
		this->affectedByTable.push_back(set<int>());
	}
	if(StmtTable::getStmtTable()->getStmtNode(stmt)->getType()!=ASSIGN) return;
	vector<GNode*> prevBIP = CFG::getCFG()->getNode(stmt)->getPrevBIPTransitive();
	for(unsigned i=0;i<prevBIP.size();i++){
		STMT_NO idx = prevBIP[i]->getAttrib();
		if(!affectsEntryCreated[idx-1]){
			fillTable(idx);
			affectsEntryCreated[idx-1]=true;
		}
	}
	/*
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
	}*/
}

set<STMT_NO> AffectsBIPTable::getAffects(STMT_NO affects){
	if(!affectsEntryCreated[affects-1])
		fillTable(affects);
	affectsEntryCreated[affects-1] = true;
	return affectsTable[affects-1];
}

set<STMT_NO> AffectsBIPTable::getAffectsTransitive(STMT_NO stmt){
	set<STMT_NO> affectsT;
	vector<bool> visited(StmtTable::getStmtTable()->getSize(), false);
	queue<int> q;
	q.push(stmt);
	while(!q.empty()){
		int u = q.front(); q.pop();
		set<int> affects = getAffects(u);
		set<int>::iterator it;

		for (it = affects.begin(); it != affects.end(); it++) {
			int v = *it;
			if (visited[v-1] == false) {
				visited[v-1] = true;
				q.push(v);
				affectsT.insert(v);
			}
		}
	}
	return affectsT;
}

set<STMT_NO> AffectsBIPTable::getAffectedBy(STMT_NO affected){
	if(!affectedByEntryCreated[affected-1])
		fillTable2(affected);
	affectedByEntryCreated[affected-1] = true;
	return affectedByTable[affected-1];
}

set<STMT_NO> AffectsBIPTable::getAffectedByTransitive(STMT_NO stmt){
	set<STMT_NO> affectedByT;
	vector<bool> visited(StmtTable::getStmtTable()->getSize(), false);
	queue<int> q;
	q.push(stmt);
	while(!q.empty()){
		int u = q.front(); q.pop();
		set<int> affected = getAffectedBy(u);
		set<int>::iterator it;

		for (it = affected.begin(); it != affected.end(); it++) {
			int v = *it;
			if (visited[v-1] == false) {
				visited[v-1] = true;
				q.push(v);
				affectedByT.insert(v);
			}
		}
	}
	return affectedByT;
}

bool AffectsBIPTable::isAffects(STMT_NO affects, STMT_NO affected){
	set<STMT_NO> entry = getAffects(affects);
	return (entry.find(affected)!=entry.end());
}

bool AffectsBIPTable::isAffectsTransitive(STMT_NO affects, STMT_NO affected){
	set<STMT_NO> entry = getAffectsTransitive(affects);
	return (entry.find(affected)!=entry.end());
}

