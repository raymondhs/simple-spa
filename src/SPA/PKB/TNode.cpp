/*
 * @author: Raymond
 */
#include <string>
#include <queue>
#include "TNode.h"
#include "../Constants.h"
#include "StmtTable.h"

using namespace std;

void TNode::init() {
	setFirstChild(NULL);
	leftSibling=NULL;
	setRightSibling(NULL);
	upLink=NULL;
	setParent(NULL);
	setFollower(NULL);
	setFollowed(NULL);
}

TNode::TNode() {
	init();
}

TNode::TNode(NodeType type) {
	init();
	this->type = type;
}

TNode::TNode(NodeType type, int attrib) {
	init();
	this->type = type;
	this->attrib = attrib;
}

TNode::~TNode() {
	if(firstChild != NULL) delete this->firstChild;
	if(rightSibling != NULL) delete this->rightSibling;
}

void TNode::setType(NodeType type) {
	this->type = type;
}

void TNode::setAttrib(int attrib){
	this->attrib = attrib;
}

void TNode::setFirstChild(TNode* firstChild) { 
	this->firstChild = firstChild;
	if(firstChild != NULL) firstChild->upLink=this;
}

void TNode::setRightSibling(TNode* rightSibling) {
	this->rightSibling = rightSibling;
	if(rightSibling != NULL) rightSibling->leftSibling=this;
	if((this->type)==WHILE||(this->type)==ASSIGN||(this->type)==IF||(this->type)==CALL){
		this->setFollower(rightSibling);
		if(rightSibling != NULL) rightSibling->setFollowed(this);
	}
}

void TNode::setParent(TNode* parent) {
	this->parent = parent;
	if(parent!=NULL){
		parent->setParented(this);
	}
}

void TNode::setParented(TNode* node) {
	this->parented.push_back(node);
}

void TNode::setFollower(TNode* node) {
	this->follower = node;
}

void TNode::setFollowed(TNode* node) {
	this->followed = node;
}

NodeType TNode::getType() {
	return type;
}

int TNode::getAttrib() {
	return attrib;
}

TNode* TNode::getFirstChild() {
	return firstChild;
}

TNode* TNode::getLeftSibling() {
	return leftSibling;
}

TNode* TNode::getRightSibling() {
	return rightSibling;
}

TNode* TNode::getUpLink() {
	return upLink;
}

TNode* TNode::getParent() {
	return this->parent;
}

vector<TNode*> TNode::getParentedBy() {
	return this->parented;
}

bool TNode::isParent(TNode* child) {
	if(child->getParent() == NULL) return false;
	return child->getParent() == this;
}

vector<TNode*> TNode::getParentTransitive() {
	vector<TNode*> parents;
	TNode* curr = this;
	while(curr->getParent() != NULL) {
		parents.push_back(curr->getParent());
		curr = curr->getParent();
	}
	return parents;
}

vector<TNode*> TNode::getParentedByTransitive() {
	vector<TNode*> children;

	// BFS
	queue<TNode*> q;
	q.push(this);
	vector<int> dist(StmtTable::getStmtTable()->getSize(),INF);
	dist[this->getAttrib()-1] = 0;
	
	while (!q.empty()) {
		TNode* u = q.front(); q.pop();
		vector<TNode*> parented = u->getParentedBy();
		vector<TNode*>::iterator it;
		for(it = parented.begin(); it < parented.end(); it++) {
			TNode* v = *it;
			int vNum = v->getAttrib();
			if(dist[vNum-1] == INF) {
				dist[vNum-1] = 1;
				q.push(v);
				children.push_back(v);
			}
		}
	}

	return children;
}

bool TNode::isParentTransitive( TNode* child) {
	TNode* curr = child;

	while(curr->getParent() != NULL) {
		curr = curr->getParent();
		if(curr == this) return true;
	}

	return false;
}

TNode* TNode::getFollows() {
	return this->follower;
}

TNode* TNode::getFollowedBy() {
	return this->followed;
}

bool TNode::isFollows( TNode* successor) {
	return this->getFollows() == successor;
}

vector<TNode*> TNode::getFollowsTransitive() {
	vector<TNode*> followers;
	TNode* curr = this;
	while(curr->getFollows() != NULL) {
		curr = curr->getFollows();
		followers.push_back(curr);
	}
	return followers;
}

vector<TNode*> TNode::getFollowedByTransitive() {
	vector<TNode*> followed;
	TNode* curr = this;
	while(curr->getFollowedBy() != NULL) {
		curr = curr->getFollowedBy();
		followed.push_back(curr);
	}
	return followed;
}

bool TNode::isFollowsTransitive(TNode* successor) {
	TNode* curr = successor;
	while(curr->getFollowedBy() != NULL) {
		curr = curr->getFollowedBy();
		if(curr == this) return true;
	}
	return false;
}
/*
bool TNode::operator == (const TNode& t) {
	return this->type == t.type && this->attrib == t.attrib;
}
*/