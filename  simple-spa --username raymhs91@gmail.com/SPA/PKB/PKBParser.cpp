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
//static TNode* plusVarName();
static TNode* expr(STMT_NO stmtIdx);
static TNode* term(STMT_NO stmtIdx);
static TNode* factor(STMT_NO stmtIdx);
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

void checkCalls(){
	for(int i=0 ; i<callerStmt.size(); i++){
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
	match (TLBRACE);
	proc->setFirstChild(stmtLst());
	match(TRBRACE);
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
	/*
	if (next_token==TWHILE)
		stmt=whileStmt();
	else if(next_token==TNAME){
		stmt=assign();
		match(TSEMICOLON);
	} else if (next_token==TIF) {
		stmt=ifStmt();
	}else throw ParseException("Error in parsing SIMPLE source code.");
	*/
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
	match (TNAME);
	callerStmt.push_back(stmtIdx);
	callerProc.push_back(currProc->getAttrib());
	calledProc.push_back(temp);
	/*
	PROC_IDX procIdx = ProcTable::getProcTable()->getProcIndex(temp);  
	if(procIdx==-1) {
		if(input.is_open()) {
			input.close();
		}
		PKBParser::cleanUp();
		throw ParseException("Calling an undefined procedure.");
	}
	
	CallsTable::getCallsTable()->insertStmt(stmtIdx,procIdx);
	CallsTable::getCallsTable()->insertProc(currProc->getAttrib(),procIdx);
	*/
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
	/*
	while(child!=NULL){
		//set parent
		child->setParent(ifNode);
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
	*/
	var->setRightSibling(stmtListThen);
	match(TRBRACE);
	match(TELSE);
	match(TLBRACE);

	stmtListElse=stmtLst();
	child=stmtListElse->getFirstChild();
	
	setTables(ifNode, child, stmtIdx);
	/*
	while(child!=NULL){
		//set parent
		child->setParent(ifNode);
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
	}*/
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
	/*
	while(child!=NULL){
		//set parent
		child->setParent(whileNode);
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
	}*/
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
/*
TNode* plusVarName(TNode *term, STMT_NO stmtIdx){
			TNode *plus, *var;
			match(TPLUS);
			plus= new TNode(PLUS);
			var=variable();
			UsesTable::getUsesTable()->insertStmt(stmtIdx, var->getAttrib());
			plus->setFirstChild(term);
			term->setRightSibling(var);
			return plus;
}
*/
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

	/*if(next_token==TINTEGER){
		string temp;
		temp.assign(text);
		match(TINTEGER);
		expr=new TNode(CONST,atoi(temp.c_str()));
		ConstantTable::getConstantTable()->addConstant(expr);
	}
	if(next_token==TNAME){
		expr=variable();
		UsesTable::getUsesTable()->insertStmt(stmtIdx, expr->getAttrib());
	}
	while(next_token!=TSEMICOLON) {
		expr=plusVarName(expr,stmtIdx);
	}*/
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
}

void PKBParser::getAssign() {
	StmtTable* stmtT = StmtTable::getStmtTable();
	vector<int> ass = stmtT->getAllAssign();

	TNode* t;
	for (unsigned i=0; i < ass.size(); i++) {
		//cout << ass[i] << endl;
		t = stmtT->getStmtNode(ass[i]);
		//print(t);
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
