#include <queue>
#include "GNode.h"
#include "CFG.h"
#include "../PKB/StmtTable.h"
#include "../PKB/CallsTable.h"
#include "../PKB/TNode.h"
#include "../Constants.h"

using namespace std;

void GNode::init() {
	attrib=NULL;
}

GNode::GNode()
{
	init();
}

GNode::GNode(int attrib) {
	init();
	this->attrib = attrib;
}

GNode::~GNode() {
	for (unsigned i=0; i<next.size(); i++) {
		delete next[i];
	}

	next.clear();
}

void GNode::setAttrib(int attrib) {
	this->attrib = attrib;
}

void GNode::setNext(GNode *node) {
	this->next.push_back(node);
	if(node!=NULL) node->setPrevious(this);
	if(StmtTable::getStmtTable()->getStmtNode(this->getAttrib())->getType()!=CALL)
		setNextBIP(node);
}

void GNode::setPrevious(GNode *node) {
	this->previous.push_back(node);
}

void GNode::setNextBIP(GNode *node) {
	this->nextBIP.push_back(node);
	if(node!=NULL) node->setPrevious(this);
}

void GNode::setPreviousBIP(GNode *node) {
	this->previousBIP.push_back(node);
}

int GNode::getAttrib() {
	return this->attrib;
}

vector<GNode*> GNode::getNext() {
	return this->next;
}

vector<GNode*> GNode::getNextBIP() {
	return this->nextBIP;
}

vector<GNode*> GNode::getNextTransitive() {
	vector<GNode*> nextT;

	// BFS		
	queue<GNode*> q;
	q.push(this);

	vector<bool> visited(StmtTable::getStmtTable()->getSize(), false);
	visited[this->getAttrib()-1] = 0;

	while (!q.empty()) {
		GNode* u = q.front(); q.pop();
		vector<GNode*> next = u->getNext();
		vector<GNode*>::iterator it;

		for (it = next.begin(); it < next.end(); it++) {
			GNode* v = *it;
			int idx = v->getAttrib();
			if (visited[idx-1] == false) {
				visited[idx-1] = true;
				q.push(v);
				nextT.push_back(v);
			}
		}
	}

	return nextT;
}

vector<GNode*> GNode::getNextBIPTransitive() {
	vector<GNode*> nextBIPT;

	// BFS		
	queue<GNode*> q;
	q.push(this);

	vector<bool> visited(StmtTable::getStmtTable()->getSize(), false);
	visited[this->getAttrib()-1] = 0;

	while (!q.empty()) {
		GNode* u = q.front(); q.pop();
		vector<GNode*> next = u->getNextBIP();
		vector<GNode*>::iterator it;

		for (it = next.begin(); it < next.end(); it++) {
			GNode* v = *it;
			int idx = v->getAttrib();
			if (visited[idx-1] == false) {
				visited[idx-1] = true;
				q.push(v);
				nextBIPT.push_back(v);
			}
		}
	}

	return nextBIPT;
}

vector<GNode*> GNode::getPrev() {
	return this->previous;
}

vector<GNode*> GNode::getPrevBIP() {
	return this->previousBIP;
}

vector<GNode*> GNode::getPrevTransitive() {
	vector<GNode*> prevT;

	// BFS
	queue<GNode*> q;
	q.push(this);

	vector<bool> visited(StmtTable::getStmtTable()->getSize(), false);
	visited[this->getAttrib()-1] = 0;

	while (!q.empty()) {
		GNode* u = q.front(); q.pop();
		vector<GNode*> prev = u->getPrev();
		vector<GNode*>::iterator it;

		for (it = prev.begin(); it < prev.end(); it++) {
			GNode* v = *it;
			int idx = v->getAttrib();
			if (visited[idx-1] == false) {
				visited[idx-1] = true;
				q.push(v);
				prevT.push_back(v);
			}
		}
	}

	return prevT;
}

vector<GNode*> GNode::getPrevBIPTransitive() {
	vector<GNode*> prevBIPT;

	// BFS
	queue<GNode*> q;
	q.push(this);

	vector<bool> visited(StmtTable::getStmtTable()->getSize(), false);
	visited[this->getAttrib()-1] = 0;

	while (!q.empty()) {
		GNode* u = q.front(); q.pop();
		vector<GNode*> prev = u->getPrevBIP();
		vector<GNode*>::iterator it;

		for (it = prev.begin(); it < prev.end(); it++) {
			GNode* v = *it;
			int idx = v->getAttrib();
			if (visited[idx-1] == false) {
				visited[idx-1] = true;
				q.push(v);
				prevBIPT.push_back(v);
			}
		}
	}

	return prevBIPT;
}

bool GNode::isNext(GNode* next) {
	for (unsigned i=0; i<this->getNext().size(); i++) {
		if (this->getNext()[i] == next) return true;
	}

	return false;
}

bool GNode::isNextBIP(GNode* next) {
	for (unsigned i=0; i<this->getNextBIP().size(); i++) {
		if (this->getNextBIP()[i] == next) return true;
	}

	return false;
}

bool GNode::isNextTransitive(GNode* next) {
	vector<GNode*> nextT = this->getNextTransitive();

	for (unsigned i=0; i<nextT.size(); i++) {
		if(nextT[i] == next) return true;
	}

	return false;
}

bool GNode::isNextBIPTransitive(GNode* next) {
	vector<GNode*> nextBIPT = this->getNextBIPTransitive();

	for (unsigned i=0; i<nextBIPT.size(); i++) {
		if(nextBIPT[i] == next) return true;
	}

	return false;
}

bool GNode::operator == (const GNode& g) {
	return this->attrib == g.attrib;
}
