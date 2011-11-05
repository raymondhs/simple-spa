#include "QueryTree.h"
#include "../Constants.h"

QueryTree::QueryTree(){
	setResult(new QNode(QSELECT));
	setSuchThat(new QNode(QSUCHTHAT));
	setWith(new QNode(QWITH));
	setPattern(new QNode(QPATTERNLIST));
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
}

void QueryTree::destroy() {
	delete result;
	delete suchThat;
	delete with;
	delete pattern;
}