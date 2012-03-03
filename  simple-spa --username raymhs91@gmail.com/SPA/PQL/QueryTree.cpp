#include "QueryTree.h"
#include "../Constants.h"
#include <queue>

QueryTree::QueryTree(){
	setResult(new QNode(QSELECT));
	setSuchThat(new QNode(QSUCHTHAT));
	setWith(new QNode(QWITH));
	setPattern(new QNode(QPATTERNLIST));
	isBooleanAnswer = false;
}

void QueryTree::addClause(QNode* clause) {
	int syn;
	
	if(clause->getType() == QSELECT ) {
		if(clause->getType() == QBOOL) {
			isBooleanAnswer = true;
		} else {
			syn = clause->getLeftChild()->getIntVal();
			if(dependencyGraph.size() <= (unsigned)syn)
				dependencyGraph.resize(syn+1,vector<QNode*>());
			dependencyGraph[syn].push_back(clause);
		}
	} else if(clause->getLeftChild()->getType() != QSYN &&
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
			syn = clause->getLeftChild()->getIntVal();
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
		if(isEmpty) return clauseList;
		vector<int> synList;
		vector<bool> vis(dependencyGraph.size(), false);
		queue<int> q;
		q.push(i);
		while(!q.empty()) {
			i = q.front(); q.pop();
			vis[i] = true;
			synList.push_back(i);
			for(j = 0; (unsigned)j < dependencyGraph[i].size(); i++) {
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

bool QueryTree::isBoolean() {
	return isBooleanAnswer;
}

void QueryTree::addSuchThat(QNode* suchThat) {
	if(this->suchThat->getLeftChild() == NULL) {
		this->suchThat->setLeftChild(suchThat);
	} else {
		QNode* current = this->suchThat->getLeftChild();
		while(current->getRightSibling() != NULL) {
			current = current->getRightSibling();
		}
		current->setRightSibling(suchThat);
	}
}

void QueryTree::addPattern(QNode* pattern) {
	if(this->pattern->getLeftChild() == NULL) {
		this->pattern->setLeftChild(pattern);
	} else {
		QNode* current = this->pattern->getLeftChild();
		while(current->getRightSibling() != NULL) {
			current = current->getRightSibling();
		}
		current->setRightSibling(pattern);
	}
}

void QueryTree::addWith(QNode* with) {
	if(this->with->getLeftChild() == NULL) {
		this->with->setLeftChild(with);
	} else {
		QNode* current = this->with->getLeftChild();
		while(current->getRightSibling() != NULL) {
			current = current->getRightSibling();
		}
		current->setRightSibling(with);
	}
}

void QueryTree::setResult(QNode* result){
	this->result = result;
}

void QueryTree::setSuchThat(QNode* suchThat){
	this->suchThat = suchThat;
}

void QueryTree::setWith(QNode* with){
	this->with = with;
}

void QueryTree::setPattern(QNode* pattern){
	this->pattern = pattern;
}

QNode* QueryTree::getResult(){
	return this->result;
}

QNode* QueryTree::getSuchThat(){
	return this->suchThat;
}

QNode* QueryTree::getWith(){
	return this->with;
}

QNode* QueryTree::getPattern(){
	return this->pattern;
}

QueryTree* QueryTree::getQueryTree(){
	static QueryTree queryTree;
	return &queryTree;
}

void QueryTree::clearTree() {	
	delete result;
	delete suchThat;
	delete with;
	delete pattern;

	setResult(new QNode(QSELECT));
	setSuchThat(new QNode(QSUCHTHAT));
	setWith(new QNode(QWITH));
	setPattern(new QNode(QPATTERNLIST));

	dependencyGraph.clear();
	booleanQueries.clear();
}

void QueryTree::destroy() {
	delete result;
	delete suchThat;
	delete with;
	delete pattern;
}