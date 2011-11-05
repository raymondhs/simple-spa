#include <fstream>
#include <iostream>
#include <string>
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

using namespace std;

static ifstream input;
static string text;
static int next_token;

static bool issymbol(char c);
static int getToken();
static void match(int token);

static TNode* program();
static TNode* procedure();
static TNode* stmtLst();
static TNode* stmt();
static TNode* varible();
static TNode* whileStmt();
static TNode* assign();
static TNode* plusVarName();
static TNode* expr(STMT_NO stmtIdx);
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
		PKBParser::cleanUp();
		throw ParseException("Error in parsing SIMPLE source code.");
	}
}

TNode* program(){
	next_token=getToken();
	TNode* program = new TNode (PROGRAM);
	TNode* firstProc = procedure();
	program->setFirstChild(firstProc);
	TNode* currProc=firstProc;
	TNode* nextProc;
	while(next_token!=TEOF){
		nextProc=procedure();
		currProc->setRightSibling(nextProc);
		currProc=nextProc;
	}
	return program;
}

TNode* procedure(){
	TNode* proc;
	match (TPROCEDURE);
	string temp;
	temp.assign(text);
	match (TNAME);
	int procIdx = ProcTable::getProcTable()->insertProc(temp);
	proc=new TNode (PROCEDURE,procIdx);
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

	if (next_token==TWHILE)
		stmt=whileStmt();
	else if(next_token==TNAME){
		stmt=assign();
		match(TSEMICOLON);
	}
	else throw ParseException("Error in parsing SIMPLE source code.");
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

TNode* whileStmt(){
	TNode *whileNode, *var, *stmtList;
	match(TWHILE);
	whileNode = new TNode(WHILE);
	STMT_NO stmtIdx= StmtTable::getStmtTable()->insertStmt(whileNode);
	whileNode->setAttrib(stmtIdx);
	var=variable();
	UsesTable::getUsesTable()->insertStmt(stmtIdx, var->getAttrib());
	whileNode->setFirstChild(var);
	match(TLBRACE);
	stmtList=stmtLst();
	TNode *child=stmtList->getFirstChild();
	
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
		 }
		 
		//set uses for container
		VAR_SET childUsesVar = UsesTable::getUsesTable()->getVarUsedByStmt(childIdx);
		set<int>::iterator iterUses;
		
        for (iterUses = childUsesVar.begin(); iterUses != childUsesVar.end() ; ++iterUses)
        {
			UsesTable::getUsesTable()->insertStmt(stmtIdx, *iterUses);
		}
		
		child=child->getRightSibling();
	}
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
	assign->setFirstChild(leftVar);
	match(TEQUAL);
	exp= expr(stmtIdx);
	leftVar->setRightSibling(exp);
	return assign;
}

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

TNode* expr(STMT_NO stmtIdx){
	TNode *expr;

	if(next_token==TINTEGER){
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
	}
	return expr;
}

void PKBParser::cleanUp() {
	ModifiesTable::getModifiesTable()->clearTable();
	UsesTable::getUsesTable()->clearTable();
	StmtTable::getStmtTable()->clearTable();
	VarTable::getVarTable()->clearTable();
	ProcTable::getProcTable()->clearTable();
	ConstantTable::getConstantTable()->clearTable();
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

