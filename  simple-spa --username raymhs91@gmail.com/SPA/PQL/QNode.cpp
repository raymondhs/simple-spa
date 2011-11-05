#include "QNode.h"

using namespace std;

void QNode::init() {
	setLeftChild(NULL);
	setRightChild(NULL);
	upLink = NULL;
	leftSibling = NULL;
	setRightSibling(NULL);
	setIntVal(0);
	setStrVal("");
}

QNode::QNode() {
	init();
}

QNode::~QNode() {
	if(leftChild != NULL) delete this->leftChild;
	if(rightChild != NULL) delete this->rightChild;
	if(rightSibling != NULL) delete this->rightSibling;
}

QNode::QNode(QNodeType type) {
	init();
	this->type = type;
}

QNode::QNode(QNodeType type, int intVal, string strVal) {
	init();
	this->type = type;
	this->intVal = intVal;
}

void QNode::setIntVal(int intVal){
	this->intVal = intVal;
}

void QNode::setStrVal(std::string strVal){
	this->strVal = strVal;
}

void QNode::setType(QNodeType type) {
	this->type = type;
}

void QNode::setLeftChild(QNode* leftChild) { 
	this->leftChild = leftChild;
	if(leftChild != NULL) leftChild->upLink=this;
}

void QNode::setRightChild(QNode* rightChild) { 
	this->rightChild = rightChild;
	if(rightChild != NULL) rightChild->upLink=this;
}

void QNode::setRightSibling(QNode* rightSibling) {
	this->rightSibling = rightSibling;
	if(rightSibling != NULL) rightSibling->leftSibling=this;
}

QNodeType QNode::getType() {
	return type;
}

int QNode::getIntVal() {
	return intVal;
}

string QNode::getStrVal() {
	return strVal;
}

QNode* QNode::getLeftChild() {
	return leftChild;
}

QNode* QNode::getRightChild() {
	return rightChild;
}

QNode* QNode::getLeftSibling() {
	return leftSibling;
}

QNode* QNode::getRightSibling() {
	return rightSibling;
}

QNode* QNode::getUpLink() {
	return upLink;
}

bool QNode::operator == (const QNode& t) {
	return this->type == t.type && this->intVal == t.intVal && this->strVal == t.strVal;
}