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

vector<GNode*> GNode::getNextBIP() {
	vector<GNode*> nextBIP;
	TNode* current = StmtTable::getStmtTable()->getStmtNode(this->getAttrib());
	if(current->getType()==CALL){
		nextBIP.push_back(CFG::getCFG()->getCfgRoot(CallsTable::getCallsTable()->getProcCalledByStmt(this->getAttrib())));
		return nextBIP;
	}
	else
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
				visited[idx-1] = true;
				q.push(v);
				nextT.push_back(v);
			}
		}
	}

	return nextT;
}

vector<GNode*> GNode::getNextBIPTransitive() {
	vector<GNode*> nextT = getNextTransitive();
	set<GNode*> nextBIPT;
	for(unsigned i = 0; i<nextT.size();i++){
		nextBIPT.insert(nextT[i]);
		if(StmtTable::getStmtTable()->getStmtNode(nextT[i]->getAttrib())->getType()==CALL){
			GNode* root = CFG::getCFG()->getCfgRoot(CallsTable::getCallsTable()->getProcCalledByStmt(nextT[i]->getAttrib()));
			vector<GNode*> temp = root->getNextBIPTransitive();
			for(unsigned j = 0; i<temp.size();j++){
				nextBIPT.insert(temp[i]);
			}
			nextBIPT.insert(root);
		}
	}
	return vector<GNode*>(nextBIPT.begin(),nextBIPT.end());
}

vector<GNode*> GNode::getPrev() {
	return this->previous;
}

vector<GNode*> GNode::getPrevBIP() {
	vector<GNode*> prev = this->getPrev();
	set<GNode*> prevBIP;
	for(unsigned i = 0; i<prev.size();i++){
		if(StmtTable::getStmtTable()->getStmtNode(prev[i]->getAttrib())->getType()==CALL){
			vector<GNode*> last = CFG::getCFG()->getLast(CallsTable::getCallsTable()->getProcCalledByStmt(prev[i]->getAttrib()));
			for(unsigned j = 0; j<last.size();j++)
				prevBIP.insert(last[j]);
		} else prevBIP.insert(prev[i]);
	}
	return vector<GNode*>(prevBIP.begin(),prevBIP.end());
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
	vector<GNode*> prevT = getPrevTransitive();
	set<GNode*> prevBIPT;
	for(unsigned i = 0; i<prevT.size();i++){
		prevBIPT.insert(prevT[i]);
		if(StmtTable::getStmtTable()->getStmtNode(prevT[i]->getAttrib())->getType()==CALL){
			GNode* root = CFG::getCFG()->getCfgRoot(CallsTable::getCallsTable()->getProcCalledByStmt(prevT[i]->getAttrib()));
			vector<GNode*> temp = root->getNextBIPTransitive();
			for(unsigned j = 0; i<temp.size();j++){
				prevBIPT.insert(temp[i]);
			}
			prevBIPT.insert(root);
		}
	}
	return vector<GNode*>(prevBIPT.begin(),prevBIPT.end());
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
