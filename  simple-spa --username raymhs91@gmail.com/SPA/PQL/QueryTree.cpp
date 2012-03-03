#include "QueryTree.h"
#include "../Constants.h"
#include <queue>
#include <iostream>

QueryTree::QueryTree(){
	isBooleanAnswer = false;
}

void QueryTree::addClause(QNode* clause) {
	int syn;
	
	if(clause->getType() == QSELECT) {
		if(clause->getLeftChild()->getType() == QBOOL) {
			isBooleanAnswer = true;
		} else {
			syn = clause->getLeftChild()->getIntVal();
			if(dependencyGraph.size() <= (unsigned)syn)
				dependencyGraph.resize(syn+1,vector<QNode*>());
			dependencyGraph[syn].push_back(clause);
			tuple.push_back(clause);
		}
	} else if(clause->getType() != QSYN && clause->getLeftChild()->getType() != QSYN &&
			  clause->getRightChild()->getType() != QSYN) {
		booleanQueries.push_back(clause);
	} else {
		if(clause->getType() == QSYN) {
			syn = clause->getIntVal();
			if(dependencyGraph.size() <= (unsigned)syn)
				dependencyGraph.resize(syn+1,vector<QNode*>());
			dependencyGraph[syn].push_back(clause);
		}
		if(clause->getLeftChild() != NULL &&
		   clause->getLeftChild()->getType() == QSYN) {
			syn = clause->getLeftChild()->getIntVal();
			if(dependencyGraph.size() <= (unsigned)syn)
				dependencyGraph.resize(syn+1,vector<QNode*>());
			dependencyGraph[syn].push_back(clause);
		}
		if(clause->getRightChild() != NULL &&
		   clause->getRightChild()->getType() == QSYN) {
			syn = clause->getRightChild()->getIntVal();
			if(dependencyGraph.size() <= (unsigned)syn)
				dependencyGraph.resize(syn+1,vector<QNode*>());
			dependencyGraph[syn].push_back(clause);
		}
	}
}
vector<QNode*> QueryTree::nextClauses() {
	vector<QNode*> clauseList;
	if(!booleanQueries.empty()) {
		clauseList = booleanQueries;
		booleanQueries.clear();
	} else {
		int i, j, syn;
		bool isEmpty = true;
		for(i = 0; (unsigned)i < dependencyGraph.size(); i++) {
			if(!dependencyGraph[i].empty()) { isEmpty = false; break; }
		}
		//cout << "index " << i << endl;
		if(isEmpty) return clauseList;
		vector<int> synList;
		vector<bool> vis(dependencyGraph.size(), false);
		queue<int> q;
		q.push(i);
		while(!q.empty()) {
			i = q.front(); q.pop();
			vis[i] = true;
			synList.push_back(i);
			for(j = 0; (unsigned)j < dependencyGraph[i].size(); j++) {
				QNode* node = dependencyGraph[i][j];
				if(node->getType() == QSYN) {
					syn = node->getIntVal();
					if(!vis[syn]) q.push(syn);
				}
				if(node->getLeftChild() != NULL && node->getLeftChild()->getType() == QSYN) {
					syn = node->getLeftChild()->getIntVal();
					if(!vis[syn]) q.push(syn);
				}
				if(node->getRightChild() != NULL && node->getRightChild()->getType() == QSYN) {
					syn = node->getRightChild()->getIntVal();
					if(!vis[syn]) q.push(syn);
				}
			}
		}
		set<QNode*> clauseSet;
		for(i = 0; (unsigned)i < synList.size(); i++) {
			for(j = 0; (unsigned)j < dependencyGraph[ synList[i] ].size(); j++) {
				clauseSet.insert(dependencyGraph[ synList[i] ] [j]);
			}
			dependencyGraph[ synList[i] ].clear();
		}
		set<QNode*>::iterator it;
		for(it = clauseSet.begin(); it != clauseSet.end(); it++) {
			QNode* node = *it;
			if(node->getType() == QSELECT) {
				clauseList.push_back(node);
			} else {
				clauseList.insert(clauseList.begin(), node);
			}
		}
	}
	return clauseList;
}

vector<QNode*> QueryTree::getTuple() {
	return tuple;
}

bool QueryTree::isBoolean() {
	return isBooleanAnswer;
}

QueryTree* QueryTree::getQueryTree(){
	static QueryTree queryTree;
	return &queryTree;
}

void QueryTree::clearTree() {	
	/*delete result;
	delete suchThat;
	delete with;
	delete pattern;*/
	isBooleanAnswer=false;
	tuple.clear();
	dependencyGraph.clear();
	booleanQueries.clear();
}

void QueryTree::destroy() {
	/*delete result;
	delete suchThat;
	delete with;
	delete pattern;*/
}