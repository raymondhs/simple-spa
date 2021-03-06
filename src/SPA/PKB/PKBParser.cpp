#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "PKBParser.h"
#include "TNode.h"
#include "VarTable.h"
#include "AST.h"
#include "../PKB/ProcTable.h"
#include "../PKB/ConstantTable.h"
#include "UsesTable.h"
#include "../ParseException.h"
#include "StmtTable.h"
#include "ModifiesTable.h"
#include "UsesTable.h"
#include "CallsTable.h"
#include "CFG.h"
#include "AffectsTable.h"
#include "AffectsBIPTable.h"

using namespace std;

static ifstream input;
static string text;
static int next_token;

static vector<int> callerStmt;
static vector<int> callerProc;
static vector<string> calledProc;

static bool issymbol(char c);
static int getToken();
static void match(int token);
static TNode* currProc;

void setTables(TNode* parent, TNode* child, STMT_NO stmtIdx);
//void print(TNode* t);

static TNode* program();
static TNode* procedure();
static TNode* stmtLst();
static TNode* stmt();
static TNode* varible();
static TNode* ifStmt();
static TNode* callStmt();
static TNode* whileStmt();
static TNode* assign();
static TNode* expr(STMT_NO stmtIdx);
static TNode* term(STMT_NO stmtIdx);
static TNode* factor(STMT_NO stmtIdx);
void checkCalls();
void postCheckCalls(int procIdx);
static void buildCFG();
static void cleanUp();

typedef enum tokentype {
	TNAME=0, 
	TINTEGER /*1*/, TLBRACE/*2*/, TRBRACE/*3*/, 
	TPLUS/*4*/, TMIN/*5*/, TTIMES/*6*/, TLPARENT, TRPARENT, TEQUAL,
	TSEMICOLON,
	TEOF/*11*/, TINVALID, TPROCEDURE, TIF, TTHEN, TELSE, TWHILE, TCALL
};

bool issymbol(char c) {
	return c == '+' || c == '-' || c == '*' 
		|| c == '{' || c == '}' || c == '(' || c == ')'
		|| c == ';' || c == '=';
}

int getToken() {
	int state = 0;
	text.assign("");

	char c=0;
	while(1) {
		try{
			c = input.get();

		}catch (ifstream::failure e) {
			return TEOF;
		}

		switch(state) {
		case 0:
			if(isalpha(c)) { text+=c;  state = 1; }
			else if(isdigit(c)) { text += c; state = 2; }
			else if(issymbol(c)) {
				text += c; 
				if(text.compare("{")==0) return TLBRACE;
				if(text.compare("}")==0) return TRBRACE;
				if(text.compare("+")==0) return TPLUS;
				if(text.compare("-")==0) return TMIN;
				if(text.compare("*")==0) return TTIMES;
				if(text.compare(")")==0) return TRPARENT;
				if(text.compare("(")==0) return TLPARENT;
				if(text.compare("=")==0) return TEQUAL;
				if(text.compare(";")==0) return TSEMICOLON;
				else return TINVALID;
			}
			else if(isspace(c)) { }
			else if(c == EOF) { return TEOF; }
			else { return TINVALID; }
			break;
		case 1:
			if(isalnum(c)) { text+=c;  }
			else if(isspace(c) || issymbol(c) || c==EOF) {
				input.putback(c); 
				if(text.compare("procedure")==0) return TPROCEDURE;
				if(text.compare("if")==0) return TIF;
				if(text.compare("then")==0) return TTHEN;
				if(text.compare("else")==0) return TELSE;
				if(text.compare("while")==0) return TWHILE;
				if(text.compare("call")==0) return TCALL;
				return TNAME; 
			}
			else { return TINVALID; }
			break;
		case 2:
			if(isdigit(c)) { text += c; }
			else if(isspace(c) || issymbol(c) || c==EOF) { input.putback(c); return TINTEGER; }
			else { return TINVALID; }
			break;
		}
	}
}

void match (int token){
	if(next_token ==token){
		next_token = getToken();
	}
	else {
		if(input.is_open()) {
			input.close();
		}
		PKBParser::cleanUp();
		throw ParseException("Error in parsing SIMPLE source code.");
	}
}

TNode* program(){
	next_token=getToken();
	TNode* program = new TNode (PROGRAM);
	TNode* firstProc = procedure();
	program->setFirstChild(firstProc);
	TNode* prevProc;
	while(next_token!=TEOF){
		prevProc = currProc;
		prevProc->setRightSibling(procedure());
	}
	buildCFG();
	checkCalls();
	return program;
}

TNode* procedure(){
	TNode* proc;
	match (TPROCEDURE);
	string temp;
	temp.assign(text);
	match (TNAME);
	if(ProcTable::getProcTable()->getProcIndex(temp)!=-1) {
		if(input.is_open()) {
			input.close();
		}
		PKBParser::cleanUp();
		throw ParseException("Error in parsing SIMPLE source code: Duplicate procedure name.");
	}
	int procIdx = ProcTable::getProcTable()->insertProc(temp);
	proc=new TNode (PROCEDURE,procIdx);
	//assign proc
	currProc=proc;
	int root = StmtTable::getStmtTable()->getSize()+1;
	match (TLBRACE);
	proc->setFirstChild(stmtLst());
	match(TRBRACE);
	for(int i=root;i<=StmtTable::getStmtTable()->getSize()+1;i++){
		CFG::getCFG()->addNode();
	}
	CFG::getCFG()->addRoot(CFG::getCFG()->getNode(root));
	return proc;
}

TNode* stmtLst(){
	TNode *stmtLst, *curNode, *nextNode;
	stmtLst= new TNode (STMTLST);
	curNode = stmt();
	stmtLst->setFirstChild(curNode);
	while(next_token!=TRBRACE){
		nextNode=stmt();
		curNode->setRightSibling(nextNode);
		curNode=nextNode;
	}
	return stmtLst;
}

TNode* stmt(){
	TNode *stmt;
	switch(next_token){
	case TWHILE :
		stmt=whileStmt();
		break;
	case TNAME  :
		stmt=assign();
		match(TSEMICOLON);
		break;
	case TIF :
		stmt=ifStmt();
		break;
	case TCALL :
		stmt=callStmt();
		match(TSEMICOLON);
		break;
	default :
		if(input.is_open()) input.close();
		PKBParser::cleanUp();
		throw ParseException("Error in parsing SIMPLE source code.");
	}

	return stmt;
}

TNode* variable(){
	string temp;
	temp.assign(text);
	match(TNAME);
	VAR_IDX varIdx = VarTable::getVarTable()->insertVar(temp);
	TNode *var=new TNode (VAR,varIdx);
	return var;
}

TNode* callStmt(){
	TNode *callNode;
	match(TCALL);
	callNode = new TNode(CALL);
	STMT_NO stmtIdx=StmtTable::getStmtTable()->insertStmt(callNode);
	callNode->setAttrib(stmtIdx);
	string temp;
	temp.assign(text);
	match(TNAME);
	callerStmt.push_back(stmtIdx);
	callerProc.push_back(currProc->getAttrib());
	calledProc.push_back(temp);
	return callNode;
}

TNode* ifStmt(){
	TNode *ifNode, *var, *stmtListThen, *stmtListElse;
	match(TIF);
	ifNode = new TNode(IF);
	STMT_NO stmtIdx=StmtTable::getStmtTable()->insertStmt(ifNode);
	ifNode->setAttrib(stmtIdx);
	var=variable();
	UsesTable::getUsesTable()->insertStmt(stmtIdx, var->getAttrib());
	UsesTable::getUsesTable()->insertProc(currProc->getAttrib(), var->getAttrib());
	ifNode->setFirstChild(var);
	match(TTHEN);
	match(TLBRACE);

	stmtListThen=stmtLst();
	TNode *child=stmtListThen->getFirstChild();

	setTables(ifNode, child, stmtIdx);
	
	var->setRightSibling(stmtListThen);
	match(TRBRACE);
	match(TELSE);
	match(TLBRACE);

	stmtListElse=stmtLst();
	child=stmtListElse->getFirstChild();

	setTables(ifNode, child, stmtIdx);

	stmtListThen->setRightSibling(stmtListElse);
	match(TRBRACE);

	return ifNode;
}

TNode* whileStmt(){
	TNode *whileNode, *var, *stmtList;
	match(TWHILE);
	whileNode = new TNode(WHILE);
	STMT_NO stmtIdx= StmtTable::getStmtTable()->insertStmt(whileNode);
	whileNode->setAttrib(stmtIdx);
	var=variable();
	UsesTable::getUsesTable()->insertStmt(stmtIdx, var->getAttrib());
	UsesTable::getUsesTable()->insertProc(currProc->getAttrib(), var->getAttrib());
	whileNode->setFirstChild(var);
	match(TLBRACE);
	stmtList=stmtLst();
	TNode *child=stmtList->getFirstChild();

	setTables(whileNode, child, stmtIdx);

	var->setRightSibling(stmtList);
	match(TRBRACE);

	return whileNode;
}

TNode* assign(){
	TNode *assign, *leftVar, *exp;
	assign= new TNode (ASSIGN);
	STMT_NO stmtIdx= StmtTable::getStmtTable()->insertStmt(assign);
	assign->setAttrib(stmtIdx);
	leftVar=variable();
	ModifiesTable::getModifiesTable()->insertStmt(stmtIdx, leftVar->getAttrib());
	ModifiesTable::getModifiesTable()->insertProc(currProc->getAttrib(), leftVar->getAttrib());
	assign->setFirstChild(leftVar);
	match(TEQUAL);
	exp= expr(stmtIdx);
	leftVar->setRightSibling(exp);
	return assign;
}

TNode* expr(STMT_NO stmtIdx){
	TNode* curr = term(stmtIdx), *expr = curr;

	while(next_token == TPLUS || next_token == TMIN) {
		if(next_token == TPLUS) {
			expr = new TNode(PLUS);
		} else {
			expr = new TNode(MINUS);
		}
		next_token = getToken();
		TNode* t = term(stmtIdx);
		expr->setFirstChild(curr);
		curr->setRightSibling(t);
		curr = expr;
	}
	return expr;
}

TNode* term(STMT_NO stmtIdx) {
	TNode* curr = factor(stmtIdx), *term = curr;

	while(next_token == TTIMES) {
		term = new TNode(TIMES);
		next_token = getToken();
		TNode* fac = factor(stmtIdx);
		term->setFirstChild(curr);
		curr->setRightSibling(fac);
		curr = term;
	}

	return term;
}

TNode* factor(STMT_NO stmtIdx) {
	TNode* fac;
	if(next_token == TINTEGER) {
		fac = new TNode(CONST,atoi(text.c_str()));
		ConstantTable::getConstantTable()->addConstant(fac);
		next_token = getToken();
	} else if(next_token == TNAME){
		VAR_IDX varIdx = VarTable::getVarTable()->insertVar(text);
		UsesTable::getUsesTable()->insertStmt(stmtIdx, varIdx);
		UsesTable::getUsesTable()->insertProc(currProc->getAttrib(), varIdx);
		fac = new TNode (VAR,varIdx);
		next_token = getToken();;
	} else if(next_token == TLPARENT) {
		next_token = getToken();
		fac = expr(stmtIdx);
		match(TRPARENT);
	} else {
		if(input.is_open()) {
			input.close();
		}
		PKBParser::cleanUp();
		throw ParseException("Error in parsing SIMPLE source code.");
	}
	return fac;
}

void checkCalls(){
	TNode* stmt;
	for(unsigned i=0 ; i<callerStmt.size(); i++){
		PROC_IDX procIdx = ProcTable::getProcTable()->getProcIndex(calledProc[i]);  
		if(procIdx==-1) {
			if(input.is_open()) {
				input.close();
			}
			PKBParser::cleanUp();
			throw ParseException("Calling an undefined procedure.");
		}
		CallsTable::getCallsTable()->insertStmt(callerStmt[i],procIdx);
		CallsTable::getCallsTable()->insertProc(callerProc[i],procIdx);
	}
	//update the next BIP
	for(unsigned i=0 ; i<callerStmt.size(); i++){
		PROC_IDX procIdx = ProcTable::getProcTable()->getProcIndex(calledProc[i]);  
		GNode* caller = CFG::getCFG()->getNode(callerStmt[i]);
		caller->setNextBIP(CFG::getCFG()->getCfgRoot(procIdx));
		vector<GNode*> lastBip = CFG::getCFG()->getLastBIP(procIdx);
		vector<GNode*> last = CFG::getCFG()->getLast(procIdx);
		if(caller->getNext().size()!=0){
			CFG::getCFG()->addBranch(caller->getNext()[0],procIdx);
			for(unsigned j=0;j<last.size();j++){
				int type = StmtTable::getStmtTable()->getStmtNode(last[j]->getAttrib())->getType();
				if(type == CALL){
					PROC_IDX procIdxIn = CallsTable::getCallsTable()->getProcCalledByStmt(last[j]->getAttrib());
					vector<GNode*> lastIn = CFG::getCFG()->getLast(procIdxIn);
					CFG::getCFG()->addBranch(caller->getNext()[0],procIdxIn);
					for(unsigned k = 0; k<lastIn.size();k++)
						last.push_back(lastIn[k]);
				}
			}
			for(unsigned j=0;j<lastBip.size();j++){
				lastBip[j]->setNextBIP(caller->getNext()[0]);
			}
		}
	}
	// update Modifies and Uses for procedure
	for(int i = 0; i<ProcTable::getProcTable()->getSize();i++)
		postCheckCalls(i);

	for(unsigned i = 0; i < callerStmt.size(); i++) {
		PROC_IDX procIdx = ProcTable::getProcTable()->getProcIndex(calledProc[i]);  

		VAR_SET modified = ModifiesTable::getModifiesTable()->getVarModifiedByProc(procIdx);
		set<int>::iterator modifiesIt;
		VAR_SET uses = UsesTable::getUsesTable()->getVarUsedByProc(procIdx);
		set<int>::iterator usesIt;
		stmt = StmtTable::getStmtTable()->getStmtNode(callerStmt[i]);
		while(stmt!=NULL){
			for(modifiesIt = modified.begin(); modifiesIt != modified.end(); modifiesIt++) {
				ModifiesTable::getModifiesTable()->insertStmt(stmt->getAttrib(),*modifiesIt);
			}
			for(usesIt = uses.begin(); usesIt != uses.end(); usesIt++) {
				UsesTable::getUsesTable()->insertStmt(stmt->getAttrib(),*usesIt);
			}
			stmt = stmt->getParent();
		}
	}
}

void postCheckCalls(int procIdx) {
	PROC_SET calledProcs = CallsTable::getCallsTable()->getProcCalledByProc(procIdx);
	PROC_SET::iterator it;
	for(it = calledProcs.begin(); it != calledProcs.end(); it++) {
		postCheckCalls(*it);
		VAR_SET modified = ModifiesTable::getModifiesTable()->getVarModifiedByProc(*it);
		set<int>::iterator modifiesIt;
		for(modifiesIt = modified.begin(); modifiesIt != modified.end(); modifiesIt++) {
			ModifiesTable::getModifiesTable()->insertProc(procIdx,*modifiesIt);
		}

		VAR_SET uses = UsesTable::getUsesTable()->getVarUsedByProc(*it);
		set<int>::iterator usesIt;
		for(usesIt = uses.begin(); usesIt != uses.end(); usesIt++) {
			UsesTable::getUsesTable()->insertProc(procIdx,*usesIt);
		}
	}
}
/*
void connectGNode(STMT_NO stmt){
	GNode* gNode = CFG::getCFG()->getNode(stmt);
	TNode* tNode = StmtTable::getStmtTable()->getStmtNode(stmt);
	NodeType type = tNode->getType();
	TNode *follower, *child, *thenChild, *elseChild;
	switch(type){
	case ASSIGN:
	case CALL:
		follower = tNode->getRightSibling();
		if(follower!=NULL) gNode->setNext(CFG::getCFG()->getNode(follower->getAttrib()));
		break;
	case WHILE:
		follower = tNode->getRightSibling();
		if(follower!=NULL) gNode->setNext(CFG::getCFG()->getNode(follower->getAttrib()));
		child = tNode->getFirstChild()->getRightSibling()->getFirstChild();
		gNode->setNext(CFG::getCFG()->getNode(child->getAttrib()));
		while(child->getRightSibling()!=NULL)
			child=child->getRightSibling();
		CFG::getCFG()->getNode(child->getAttrib())->setNext(gNode);
		break;
	case IF:
		thenChild = tNode->getFirstChild()->getRightSibling()->getFirstChild();
		elseChild = tNode->getFirstChild()->getRightSibling()->getRightSibling()->getFirstChild();
		gNode->setNext(CFG::getCFG()->getNode(thenChild->getAttrib()));
		gNode->setNext(CFG::getCFG()->getNode(elseChild->getAttrib()));
		follower = tNode->getRightSibling();
		while(thenChild->getRightSibling()!=NULL)
			thenChild=thenChild->getRightSibling();
		while(elseChild->getRightSibling()!=NULL)
			elseChild=elseChild->getRightSibling();
		if(follower!=NULL){
			CFG::getCFG()->getNode(thenChild->getAttrib())->setNext(CFG::getCFG()->getNode(follower->getAttrib()));
			CFG::getCFG()->getNode(elseChild->getAttrib())->setNext(CFG::getCFG()->getNode(follower->getAttrib()));
		}
		break;
	}
}

void buildCFG(){
	for(int i=0;i<StmtTable::getStmtTable()->getSize();i++){
		connectGNode(i+1);
	}
}
*/

vector<GNode*> connectGNode(GNode* gNode){
	int stmt = gNode->getAttrib();
	vector<GNode*> next, last;
	TNode* tNode = StmtTable::getStmtTable()->getStmtNode(stmt);
	NodeType type = tNode->getType();
	TNode *follower, *child, *thenChild, *elseChild;
	last = vector<GNode*>();
	switch(type){
	case ASSIGN:
	case CALL:
		follower = tNode->getRightSibling();
		if(follower!=NULL) gNode->setNext(CFG::getCFG()->getNode(follower->getAttrib()));
		if(follower==NULL) last.push_back(gNode);
		else
			last=connectGNode(CFG::getCFG()->getNode(follower->getAttrib()));
		break;
	case WHILE:
		follower = tNode->getRightSibling();
		if(follower!=NULL) gNode->setNext(CFG::getCFG()->getNode(follower->getAttrib()));
		child = tNode->getFirstChild()->getRightSibling()->getFirstChild();
		gNode->setNext(CFG::getCFG()->getNode(child->getAttrib()));
		last = connectGNode(CFG::getCFG()->getNode(child->getAttrib()));
		for(unsigned i=0; i<last.size();i++){
			last[i]->setNext(gNode);
		}
		last = vector<GNode*>();
		if(follower==NULL) last.push_back(gNode);
		else
			last=connectGNode(CFG::getCFG()->getNode(follower->getAttrib()));
		break;
	case IF:
		thenChild = tNode->getFirstChild()->getRightSibling()->getFirstChild();
		elseChild = tNode->getFirstChild()->getRightSibling()->getRightSibling()->getFirstChild();
		gNode->setNext(CFG::getCFG()->getNode(thenChild->getAttrib()));
		gNode->setNext(CFG::getCFG()->getNode(elseChild->getAttrib()));
		follower = tNode->getRightSibling();
		next=connectGNode(CFG::getCFG()->getNode(thenChild->getAttrib()));
		for(unsigned i=0; i<next.size();i++){
			last.push_back(next[i]);
		}
		next=connectGNode(CFG::getCFG()->getNode(elseChild->getAttrib()));
		for(unsigned i=0; i<next.size();i++){
			last.push_back(next[i]);
		}
		if(follower!=NULL){
			for(unsigned i=0; i<last.size();i++){
				last[i]->setNext(CFG::getCFG()->getNode(follower->getAttrib()));
			}
			last=connectGNode(CFG::getCFG()->getNode(follower->getAttrib()));
		}
		break;
	}
	return last;
}

void buildCFG(){
	for(int i=0; i<ProcTable::getProcTable()->getSize();i++){
		CFG::getCFG()->addLast(connectGNode(CFG::getCFG()->getCfgRoot(i)));
	}
}

void setTables(TNode* parent, TNode* child, STMT_NO stmtIdx) {
	while(child!=NULL){
		//set parent
		child->setParent(parent);
		STMT_NO childIdx=child->getAttrib();
		//set modifies for container
		VAR_SET childModVar = ModifiesTable::getModifiesTable()->getVarModifiedByStmt(childIdx);
		set<int>::iterator iterMod;
		for (iterMod = childModVar.begin(); iterMod != childModVar.end() ; ++iterMod)
		{
			ModifiesTable::getModifiesTable()->insertStmt(stmtIdx, *iterMod);
			ModifiesTable::getModifiesTable()->insertProc(currProc->getAttrib(), *iterMod);
		}

		//set uses for container
		VAR_SET childUsesVar = UsesTable::getUsesTable()->getVarUsedByStmt(childIdx);
		set<int>::iterator iterUses;

		for (iterUses = childUsesVar.begin(); iterUses != childUsesVar.end() ; ++iterUses)
		{
			UsesTable::getUsesTable()->insertStmt(stmtIdx, *iterUses);
			UsesTable::getUsesTable()->insertProc(currProc->getAttrib(), *iterUses);
		}

		child=child->getRightSibling();
	}
}

void PKBParser::parse(string fileName){
	input.open(fileName);
	if(input.good()) {
		AST::getAST()->setRoot(program());
		if(input.is_open()) {
			input.close();
		}
	} else {
		if(input.is_open()) {
			input.close();
		}
		PKBParser::cleanUp();
		throw ParseException("Error in reading file.");
	}
	AffectsTable::getAffectsTable()->init();
	AffectsBIPTable::getAffectsBIPTable()->init();
}

void PKBParser::cleanUp() {
	ModifiesTable::getModifiesTable()->clearTable();
	UsesTable::getUsesTable()->clearTable();
	StmtTable::getStmtTable()->clearTable();
	VarTable::getVarTable()->clearTable();
	ProcTable::getProcTable()->clearTable();
	ConstantTable::getConstantTable()->clearTable();
	callerStmt.clear();
	callerProc.clear();
	calledProc.clear();
	CallsTable::getCallsTable()->clearTable();
	AffectsTable::getAffectsTable()->clearTable();
	AffectsBIPTable::getAffectsBIPTable()->clearTable();
	CFG::getCFG()->clearTable();
}


/*
void getAssign() {
	StmtTable* stmtT = StmtTable::getStmtTable();
	vector<int> ass = stmtT->getAllAssign();

	TNode* t;
	for (unsigned i=0; i < ass.size(); i++) {
		//cout << ass[i] << endl;
		t = stmtT->getStmtNode(ass[i]);
		//print(t);
	}
}
*/

/*
void print(TNode* t){

TNode* lc;
TNode* rc;

if (t == NULL) return;

switch (t->getType()) {
case 0: 
cout << "NODE" << " "; break;
case 1:
cout << "PROGRAM" << " "; break;
case 2:
cout << "PROCEDURE" << " ";	break;
case 3:
cout << "STMTLST" << " "; break;
case 4:
cout << "STMT" << " "; break;
case 5:
cout << "ASSIGN" << " "; break;
case 6:
cout << "WHILE" << " "; break;
case 7:
cout << "IF" << " "; break;
case 8:
cout << "'CONST " << t->getAttrib() << "' "; break;
case 9:
cout << "EXPR" << " "; break;
case 10:
cout << "PLUS" << " "; break;
case 11:
cout << "MINUS" << " "; break;
case 12:
cout << "TIMES" << " "; break;
case 13:
cout << "'VAR " << t->getAttrib() << "' "; break;
}

if (t->getFirstChild() != NULL){
lc = t->getFirstChild();
rc = lc->getRightSibling();

print(lc);
print(rc);

cout << endl;
}

}*/
