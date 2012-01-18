#include <sstream>
#include <iostream>
#include "PQLParser.h"
#include "../ParseException.h"
#include "../PKB/VarTable.h"
#include "SynTable.h"
#include "RelTable.h"
#include "QueryTree.h"
#include "../Constants.h"

using namespace std;

static istringstream input;
static int next_token;
static string text;

// Helper methods
static bool issymbol(char c);
static int getToken();
static void match(int token);
static QNode* stmtRef();
static QNode* entRef();
static QNode* relRef();

static QNode* term();
static QNode* factor();
static QNode* expr();
static QNode* exprSpec();

static int entity();
static void declaration();
static QNode* suchthatClause();
static QNode* selectClause();

typedef enum tokentype {
	TNAME = 0, TINTEGER, TPLUS, TMIN, TTIMES, TLPARENT, TRPARENT, TEQUAL,
	TSEMICOLON, TUNDERSCORE, TDQUOTE, TCOMMA,
	TEOF, TINVALID, TPROCEDURE, TIF, TTHEN, TELSE, TCALL,
	TSELECT, TSUCH, TTHAT, TAND, TPROG, TLINE,
	TSTMT, TASSIGN, TWHILE, TVAR, TCONST,
	TPARENT, TFOLLOWS, TMODIFIES, TUSES
};

int getSynIdx(string name) {
	return SynTable::getSynTable()->getSynIdx(name);
}

int getSynType(string name) {
	SynTable *synT = SynTable::getSynTable();
	int row = synT->getSynIdx(name);
	if(row != -1) {
		return synT->getSyn(row).second;
	} else {
		PQLParser::cleanUp();
		throw ParseException("Error: Undeclared variable: "+name);
	}
}

bool issymbol(char c) {
	return c == '+' || c == '-' || c == '*' 
		|| c == '{' || c == '}' || c == '(' || c == ')'
		|| c == ';' || c == '=' || c == '_' || c == '"'
		|| c == ',';
}

int getToken() {
	int state = 0;
	text = "";
	char c;
	while(1) {
		c = input.get();
		switch(state) {
			case 0:
				if(isalpha(c)) { text += c; state = 1; }
				else if(isdigit(c)) { text += c; state = 2; }
				else if(issymbol(c)) {
					text += c; 
					if(text == "+") return TPLUS;
					if(text == "-") return TMIN;
					if(text == "*") return TTIMES;
					if(text == ")") return TRPARENT;
					if(text == "(") return TLPARENT;
					if(text == "=") return TEQUAL;
					if(text == ";") return TSEMICOLON;
					if(text == "\"") return TDQUOTE;
					if(text == "_") return TUNDERSCORE;
					if(text == ",") return TCOMMA;
					else return TINVALID;
				}
				else if(isspace(c)) { }
				else if(c == EOF) { return TEOF; }
				else { return TINVALID; }
				break;
			case 1:
				if(isalnum(c) || c == '#') { text += c; }
				else if(isspace(c) || issymbol(c) || c==EOF) {
					input.putback(c); 
					if(text == "Select") return TSELECT;
					if(text == "such") return TSUCH;
					if(text == "that") return TTHAT;
					if(text == "stmt") return TSELECT;
					if(text == "assign") return TASSIGN;
					if(text == "while") return TWHILE;
					if(text == "variable") return TVAR;
					if(text == "constant") return TCONST;
					if(text == "prog") return TPROG;
					if(text == "line") return TLINE;
					if(text == "Modifies") return TMODIFIES;
					if(text == "Uses") return TUSES;
					if(text == "Parent") return TPARENT;
					if(text == "Follows") return TFOLLOWS;
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

void match(int token) {
	if(next_token == token){
		next_token = getToken();
	}
	else {
		PQLParser::cleanUp();
		throw ParseException("Syntax error: Invalid query.");
	}
}

QNode* stmtRef() {
	QNode* stmt = new QNode();
	if(next_token == TUNDERSCORE) {
		next_token = getToken();
		stmt->setType(QANY);
	} else if(next_token == TINTEGER) {
		stmt->setIntVal(atoi(text.c_str()));
		next_token = getToken();
		stmt->setType(QCONST);
	} else if(next_token == TNAME) {
		stmt->setIntVal(getSynIdx(text));
		next_token = getToken();
		stmt->setType(QSYN);
	} else {
		PQLParser::cleanUp();
		throw ParseException("Syntax error: Invalid query.");
	}
	return stmt;
}

QNode* entRef() {
	QNode* ent = new QNode();
	if(next_token == TUNDERSCORE) {
		next_token = getToken();
		ent->setType(QANY);
	} else if(next_token == TDQUOTE) {
		next_token = getToken();
		ent->setStrVal(text);
		ent->setType(QSTRING);
		match(TNAME);
		match(TDQUOTE);
	} else if(next_token == TNAME) {
		ent->setIntVal(getSynIdx(text));
		ent->setType(QSYN);
		next_token = getToken();
	} else {
		PQLParser::cleanUp();
		throw ParseException("Syntax error: Invalid query.");
	}
	return ent;
}

QNode* relRef() {
	string relName = "", temp;
	int arg1, arg2, tok;
	int allStmt = QSTMT|QASSIGN|QWHILE|QPROGLINE;
	QNode *rel, *arg1node, *arg2node;
	if(text == "Modifies" || text == "Uses") {
		arg1 = allStmt;
		arg2 = QVAR;
		relName = text;
		next_token = getToken();
		match(TLPARENT);
		
		temp = text;
		tok = next_token;
		arg1node = stmtRef();

		if(tok == TUNDERSCORE) {
			arg1 = QANY; // not allowed in Modifies/Uses
		}
		if(tok != TUNDERSCORE && tok != TINTEGER) {
			arg1 = getSynType(temp);		
		}

		match(TCOMMA);

		temp = text;
		tok = next_token;
		arg2node = entRef();

		if(tok != TUNDERSCORE && tok != TDQUOTE) {
			arg2 = getSynType(temp);
		}

		match(TRPARENT);

		if(RelTable::getRelTable()->validate(relName, arg1, arg2)) {
		} else {
			PQLParser::cleanUp();
			throw ParseException("Error: Violation in declaration of " + relName + " relationship.");
		}

		if(relName == "Modifies") {
			rel = new QNode(QMODIFIES);
		} else {
			rel = new QNode(QUSES);
		}
		rel->setLeftChild(arg1node);
		rel->setRightChild(arg2node);
	} else if(text == "Parent" || text == "Follows") {
		QNodeType t;
		arg1 = allStmt;
		arg2 = allStmt;
		relName = text;
		if(relName == "Parent") { t = QPARENT; }
		else t = QFOLLOWS;
		next_token = getToken();
		if(text == "*") {
			relName += "*";
			if(relName == "Parent*") { t = QPARENTT; }
			else t = QFOLLOWST;
			next_token = getToken();
		} else if(text == "(") {
		} else {
			PQLParser::cleanUp();
			throw ParseException("Syntax error: Invalid query.");
		}
		match(TLPARENT);

		temp = text;
		tok = next_token;
		arg1node = stmtRef();
		if(tok != TUNDERSCORE && tok != TINTEGER) {
			arg1 = getSynType(temp);
		}


		match(TCOMMA);
		
		temp = text;
		tok = next_token;
		arg2node = stmtRef();
		if(tok != TUNDERSCORE && tok != TINTEGER) {
			arg1 = getSynType(temp);
		}

		match(TRPARENT);

		if(RelTable::getRelTable()->validate(relName, arg1, arg2)) {
		} else {
			PQLParser::cleanUp();
		throw ParseException("Error: Violation in declaration of " + relName + " relationship.");
		}

		rel = new QNode(t);
		rel->setLeftChild(arg1node);
		rel->setRightChild(arg2node);
	} else {
		PQLParser::cleanUp();
		throw ParseException("Syntax error: Invalid query.");
	}
	return rel;
}

QNode* expr() {
	QNode* curr = term(), *exp = curr;
	
	while(next_token == TPLUS || next_token == TMIN) {
		if(next_token == TPLUS) {
			exp = new QNode(QPLUS);
		} else {
			exp = new QNode(QMINUS);
		}
		next_token = getToken();
		QNode* t = term();
		exp->setLeftChild(curr);
		curr->setRightSibling(t);
		curr = exp;
	}
	return exp;
}

QNode* term() {
	QNode* curr = factor(), *term = curr;

	while(next_token == TTIMES) {
		term = new QNode(QTIMES);
		next_token = getToken();
		QNode* fac = factor();
		term->setLeftChild(curr);
		curr->setRightSibling(fac);
		curr = term;
	}

	return term;
}

QNode* factor() {
	QNode* fac;
	if(next_token == TINTEGER) {
		fac = new QNode(QCONST);
		fac->setIntVal(atoi(text.c_str()));
		next_token = getToken();
	} else if(next_token == TNAME){
		fac = new QNode(QVAR);
		fac->setIntVal(VarTable::getVarTable()->getVarIndex(text));
		next_token = getToken();
	} else if(next_token == TLPARENT) {
		next_token = getToken();
		fac = expr();
		match(TRPARENT);
	} else {
		PQLParser::cleanUp();
		throw ParseException("Error: Invalid SIMPLE expression.");
	}
	return fac;
}


QNode* exprSpec() {
	QNode *exp;
	//match(TUNDERSCORE);
	if(next_token == TDQUOTE) {
		match(TDQUOTE);
		//exp = new QNode(QSTRING);
		//exp->setStrVal(text);
		//match(TNAME);
		exp = expr();		
		match(TDQUOTE);
		//match(TUNDERSCORE);
	} else if(next_token == TUNDERSCORE) {
		match(TUNDERSCORE);
		if(next_token == TRPARENT) {
			match(TRPARENT);
			exp = new QNode(QANY);
		} else {
			exp = new QNode(QANY);
			exp->setRightSibling(expr());
			match(TUNDERSCORE);
		}
	}
	return exp;
}

int entity() {
	if(text == "stmt") {
		next_token = getToken();
		return QSTMT;
	} else if(text == "assign") {
		next_token = getToken();
		return QASSIGN;
	} else if(text == "while") {
		next_token = getToken();
		return QWHILE;
	} else if(text == "variable") {
		next_token = getToken();
		return QVAR;
	} else if(text == "constant") {
		next_token = getToken();
		return QCONST;
	} else if(text == "prog") {
		next_token = getToken();
		match(TUNDERSCORE);
		match(TLINE);
		return QPROGLINE;
	} else {
		PQLParser::cleanUp();
		throw ParseException("Syntax error: Invalid query.");
	}
}

void declaration() {
	int type = entity();
	string temp = text;
	
	match(TNAME);	
	QNode *ent = NULL, *sibling = NULL;
	if(SynTable::getSynTable()->getSynIdx(temp) == -1) {
		int idx = SynTable::getSynTable()->insertSyn(temp,type);
		ent = new QNode(QSYN);
		ent->setIntVal(idx);
	} else {
		PQLParser::cleanUp();
		throw ParseException("Error: Redeclaration of variable "+temp);
	}	

	while(next_token == TCOMMA) {
		next_token = getToken();
		temp = text;
		match(TNAME);
		if(SynTable::getSynTable()->getSynIdx(temp) == -1) {
			int idx = SynTable::getSynTable()->insertSyn(temp,type);
			sibling = new QNode(QSYN);
			sibling->setIntVal(idx);

			ent->setRightSibling(ent);
		} else {
			PQLParser::cleanUp();
		throw ParseException("Error: Redeclaration of variable "+temp);
		}
	}
	match(TSEMICOLON);
}

/*
void print() {
	QueryTree *qt = QueryTree::getQueryTree();
	QNode *curr = qt->getResult();
	cout << curr->getType() << " " << curr->getIntVal() << endl;
	curr = curr->getLeftChild();

	while(curr != NULL) {
		cout << curr->getType() << " " << curr->getIntVal() << endl;
		curr = curr->getRightSibling();
	}

	curr = qt->getSuchThat();
	cout << curr->getType() << " " << curr->getIntVal() << endl;
	curr = curr->getLeftChild();
	if(curr != NULL) {
		cout << curr->getType() << endl;
		QNode* l = curr->getLeftChild(), *r = curr->getRightChild();
		cout << l->getType() << " " << l->getIntVal() << " " << l->getStrVal() << endl;
		cout << r->getType() << " " << r->getIntVal() << " " << r->getStrVal() << endl;
	}

	cout << endl;

	curr = qt->getPattern();
	cout << curr->getType() << " " << curr->getIntVal() << endl;
	curr = curr->getLeftChild();
	if(curr != NULL) {
		cout << curr->getType() << endl;
		QNode* l = curr->getLeftChild(), *r = curr->getRightChild();
		cout << l->getType() << " " << l->getIntVal() << " " << l->getStrVal() << endl;
		cout << r->getType() << " " << r->getIntVal() << " " << r->getStrVal() << endl;
	}
}
*/

QNode* suchthatCond() {
	QNode* node = relRef(), *current = node;
	while(text == "and"){
		next_token = getToken();
		current->setRightSibling(relRef());
		current = current->getRightSibling();
	}
	return node;
}

QNode* patternClause() {
	QNode *node, *left, *right;

	next_token = getToken();

	string temp = text;
	match(TNAME);
	if(getSynType(temp) != QASSIGN) {
		PQLParser::cleanUp();
		throw ParseException("Error: Expecting assignment in pattern clause.");
	}
	match(TLPARENT);
	left = entRef();
	match(TCOMMA);
	right = exprSpec();
	match(TRPARENT);
	node = new QNode(QSYN);
	node->setIntVal(getSynIdx(temp));
	node->setLeftChild(left);
	node->setRightChild(right);

	return node;
}

QNode* patternCond() {
	QNode* node = patternClause(), *current = node;
	while(text == "and") {
		next_token = getToken();
		current->setRightSibling(patternClause());
		current = current->getRightSibling();
	}
	return node;
}

QNode* selectClause() {
	next_token = getToken();
	QueryTree *qt = QueryTree::getQueryTree();

	QNode* curr = NULL; int count = 0;
	while(text != "Select") {
		declaration();
	}

	match(TSELECT);

	int synIdx = SynTable::getSynTable()->getSynIdx(text);
	if(synIdx == -1) {		
		PQLParser::cleanUp();
		throw ParseException("Error: Undeclared variable: " + text);
	} else {
		QNode* selNode = new QNode(QSYN);
		selNode->setIntVal(synIdx);
		qt->getResult()->setLeftChild(selNode);
	}

	match(TNAME);

	while(text != "") {
		if(text == "such") {
			next_token = getToken();
			match(TTHAT);
			qt->addSuchThat(suchthatCond());
		} else if(text == "pattern") {
			qt->addPattern(patternCond());
		} else if(text != "") {
			PQLParser::cleanUp();
			throw ParseException("Syntax error: Invalid query.");
		}
	}	
	return NULL;
}

void PQLParser::parse(string query) {	
	RelTable::getRelTable()->init();
	input = istringstream(query,istringstream::in);
	selectClause();
}

void PQLParser::cleanUp() {
	RelTable::getRelTable()->clearTable();
	QueryTree::getQueryTree()->clearTree();
	SynTable::getSynTable()->clearTable();
}