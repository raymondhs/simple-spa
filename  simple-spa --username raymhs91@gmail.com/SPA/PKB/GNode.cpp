#include <queue>
#include "GNode.h"
#include "../PKB/StmtTable.h"

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
	for (int i=0; i<next.size(); i++) {
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
}

void GNode::setPrevious(GNode *node) {
	this->previous.push_back(node);
}

int GNode::getAttrib() {
	return this->attrib;
}

vector<GNode*> GNode::getNext() {
	return this->next;
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
				visited[idx-1] == true;
				q.push(v);
				nextT.push_back(v);
			}
		}
	}

	return nextT;
}

vector<GNode*> GNode::getPrev() {
	return this->previous;
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
				visited[idx-1] == true;
				q.push(v);
				prevT.push_back(v);
			}
		}
	}

	return prevT;
}

bool GNode::isNext(GNode* next) {
	for (int i=0; i<this->getNext().size(); i++) {
		if (this->getNext()[i] == next) return true;
	}

	return false;
}

bool GNode::isNextTransitive(GNode* next) {
	vector<GNode*> nextT = this->getNextTransitive();

	for (int i=0; i<nextT.size(); i++) {
		if(nextT[i] == next) return true;
	}

	return false;
}

bool GNode::operator == (const GNode& g) {
	return this->attrib == g.attrib;
}
