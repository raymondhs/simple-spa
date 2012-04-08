#include <iostream>
#include <sstream>
#include <map>
#include "QueryEvaluator.h"
#include "QueryTree.h"
#include "../PKB/TNode.h"
#include "../PKB/ModifiesTable.h"
#include "../PKB/UsesTable.h"
#include "../PKB/AST.h"
#include "../PKB/CFG.h"
#include "../PKB/VarTable.h"
#include "../PKB/ProcTable.h"
#include "../PKB/StmtTable.h"
#include "../PKB/CallsTable.h"
#include "SynTable.h"
#include "../PKB/ConstantTable.h"
#include "PQLParser.h"
#include <list>
#include "../PKB/AffectsTable.h"
#include "../PKB/AffectsBIPTable.h"

//#include "../../AbstractWrapper.h"

using namespace std;

typedef unsigned ui;

static QueryTree *qt;
static ModifiesTable *m;
static SynTable *syn;
static VarTable *var;
static StmtTable *st;
static UsesTable *u;
static AST *ast;
static CFG *cfg;
static ConstantTable *ct;
static ProcTable *pt;
static CallsTable *callst;
static list< vector<int> > table, resultTable;
static map< int, int > mapper, mapperResult;
static AffectsTable *a;
static AffectsBIPTable *ab;

static void cartesianProduct(list< vector<int> >& table1, list< vector<int> >& table2, list< vector<int> >& result);
static vector<int> allEntitiesWithType(int type);
static vector<string> resultString;

static void initVars(QNode* leftArg, QNode* rightArg);
static void initVarsForCalls(QNode* leftArg, QNode* rightArg);
static void initVarsForNext(QNode* leftArg, QNode* rightArg);

static void initTable();
static void initResultTable();
static void addAttribute(int synIdx, list< vector<int> >& old, map< int, int >& m);
static void clearTable();
static bool isEmptyResult();

static void formatResult();

static void evaluateSelectNode(QNode *q);
static void evaluateWithNode(QNode *q);
static void evaluateSuchThatNode(QNode *q);
static void evaluatePatternNode(QNode *q);
static void handleParent(QNode* query);
static void handleParentT(QNode* query);
static void handleFollows(QNode* query);
static void handleFollowsT(QNode* query);
static void handleModifies(QNode* query);
static void handleUses(QNode* query);
static void handleCalls(QNode* query);
static void handleCallsT(QNode* query);
static void handleNext(QNode* query);
static void handleNextT(QNode* query);
static void handleNextBIP(QNode* query);
static void handleNextBIPT(QNode* query);
static void handleAffects(QNode* query);
static void handleAffectsT(QNode* query);
static void handleAffectsBIP(QNode* query);
static void handleAffectsBIPT(QNode* query);
static void handleContains(QNode* query);
static void handleContainsT(QNode* query);
static void handleSibling(QNode* query);



static int leftType, rightType;
static int synIdxLeft, synIdxRight;

// Modifies and Uses
static int varIdx, procIdx;
static TNode *stmt1, *stmt2;

static int constLeft, constRight;

// Next
static GNode *line1, *line2;

// Calls
static int procIdxLeft, procIdxRight;

// to detect non exist input (stmt idx out of range, etc)
static bool valid;

// to answer boolean queries, and fast termination
static bool booleanAnswer;

void initVars(QNode* leftArg, QNode* rightArg) {
	valid = true;

	leftType = leftArg->getType();
	rightType = rightArg->getType();

	if(leftType == QSYN) { synIdxLeft = leftArg->getIntVal(); }
	if(leftType == QINT) {
		constLeft = leftArg->getIntVal();
		stmt1 = st->getStmtNode(constLeft);
		if(stmt1 == NULL) valid = false;
	}
	if(leftType == QSTRING) {
		procIdx = pt->getProcIndex(leftArg->getStrVal());
		if(procIdx == -1) valid = false;
	}

	if(rightType == QSYN) { synIdxRight = rightArg->getIntVal(); }
	if(rightType == QSTRING) {
		varIdx = var->getVarIndex(rightArg->getStrVal());
		if(varIdx == -1) valid = false;
	}
	if(rightType == QINT) {
		constRight = rightArg->getIntVal();
		stmt2 = st->getStmtNode(constRight);
		if(stmt2 == NULL) valid = false;
	}
}

void initVarsForCalls(QNode* leftArg, QNode* rightArg) {
	valid = true;

	leftType = leftArg->getType();
	rightType = rightArg->getType();

	if(leftType == QSYN) { synIdxLeft = leftArg->getIntVal(); }
	if(leftType == QSTRING) {
		procIdxLeft = pt->getProcIndex(leftArg->getStrVal());
		if(procIdxLeft == -1) valid = false;
	}

	if(rightType == QSYN) { synIdxRight = rightArg->getIntVal(); }
	if(rightType == QSTRING) {
		procIdxRight = pt->getProcIndex(rightArg->getStrVal());
		if(procIdxRight == -1) valid = false;
	}
}

void initVarsForNext(QNode* leftArg, QNode* rightArg) {
	valid = true;

	leftType = leftArg->getType();
	rightType = rightArg->getType();

	if(leftType == QSYN) { synIdxLeft = leftArg->getIntVal(); }
	if(leftType == QINT) {
		line1 = cfg->getNode(leftArg->getIntVal());
		if(line1 == NULL) valid = false;
	}

	if(rightType == QSYN) { synIdxRight = rightArg->getIntVal(); }
	if(rightType == QINT) {
		line2 = cfg->getNode(rightArg->getIntVal());
		if(line2 == NULL) valid = false;
	}
}

void cartesianProduct(list< vector<int> >& table1, list< vector<int> >& table2, list< vector<int> >& result) {
	if(table1.empty()) {
		result = list< vector<int> > (table2.begin(), table2.end());
		return;
	}
	if(table2.empty()) {
		result = list< vector<int> > (table1.begin(), table1.end());
		return;
	}
	result.clear();
	vector<int> temp;
	temp = table1.front();
	for( unsigned i = 0; i< table2.front().size(); i++){
		temp.push_back(table2.front()[i]);
	}
	result.push_back(temp);
	list<vector<int> >::iterator it1,it2;
	it1=table1.begin();it1++;
	while(it1!=table1.end()){
		it2 = table2.begin(); it2++;
		while(it2!=table2.end()){
			temp=(*it1);
			for(unsigned i=0;i<((*it2).size());i++)
				temp.push_back((*it2)[i]);
			result.push_back(temp);
			it2++;
		}
		it1++;
	}	
}

vector<int> allEntitiesWithType(int type) {
	vector<int> result;
	switch(type) {
	case QSTMT:
		result = st->getAllStmt(); break;
	case QSTMTLST:
		result = st->getAllStmtLst(); break;
	case QASSIGN:
		result = st->getAllAssign(); break;
	case QWHILE:
		result = st->getAllWhile(); break;
	case QVAR:
		result = var->getAllVar(); break;
	case QPROC:
		result = pt->getAllProc(); break;
	case QCONST:
		result = ct->getAllConstant(); break;
	case QPROGLINE:
		result = st->getAllProgline(); break;
	case QIF:
		result = st->getAllIf(); break;
	case QCALL:
		result = callst->getAllCall(); break;
	default:
		break;
	}
	return result;
}

void initTable() {
	table.clear();
	mapper.clear();

	// Yes/No Question
	booleanAnswer = true;
}

void initResultTable() {
	resultTable.clear();
	mapperResult.clear();
}

void addAttribute(int synIdx, list< vector<int> >& old, map< int, int >& m) {
	int entType = syn->getSyn(synIdx).second;
	vector<int> allEnt = allEntitiesWithType(entType);

	list< vector<int> > newCol;
	newCol.assign(allEnt.size()+1,vector<int>());
	list< vector<int> >::iterator it = newCol.begin();
	(*it).push_back(synIdx);
	it++;
	for(unsigned i = 0; it!=newCol.end(); i++,it++) {
		(*it).push_back(allEnt[i]);
	}

	if(old.size() == 0) {
		old = newCol;
	} else {
		list< vector<int> > result;
		cartesianProduct(old,newCol,result);
		old=result;
	}

	m.insert(pair<int,int>(synIdx,m.size()));
}

void clearTable() {
	booleanAnswer = false;
	for(ui i=table.size(); i>1 ; i--)
		table.pop_back();
}

bool isEmptyResult() {
	return table.size() <= 1;
}

void deleteRow(list< vector<int> >::iterator it) {
	table.erase(it);
	if(table.size() <= 1) booleanAnswer = false;
}

void evaluateWithNode(QNode* with){
	//cout << "with" << endl;
	if(!booleanAnswer) return;
	QNode* leftArg = with->getLeftChild();
	QNode* rightArg = with->getRightChild();
	if(leftArg->getType() == QSYN) {
		if(mapper.count(leftArg->getIntVal()) == 0) {
			addAttribute(leftArg->getIntVal(), table, mapper);
		}
	}
	if(rightArg->getType() == QSYN) {
		if(mapper.count(rightArg->getIntVal()) == 0) {
			addAttribute(rightArg->getIntVal(), table, mapper);
		}
	}

	int synIdx1 = leftArg->getIntVal();
	int synIdx2 = rightArg->getType();
	int typeRight;
	if(synIdx2 == QSYN){
		synIdx2 = rightArg->getIntVal();
		typeRight = SynTable::getSynTable()->getSyn(synIdx2).second;
	} else
		typeRight = rightArg->getType();

	int typeLeft = SynTable::getSynTable()->getSyn(synIdx1).second;

	if(typeLeft==QVAR){
		if(typeRight==QSTRING){
			int aIdx = mapper[synIdx1];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				string name=VarTable::getVarTable()->getVarName((*it)[aIdx]);
				if(name!=rightArg->getStrVal()) deleteRow(it--);
			}
		} else if(typeRight==QVAR){
			int aIdx1 = mapper[synIdx1], aIdx2 = mapper[synIdx2];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if((*it)[aIdx1]!=(*it)[aIdx2]) deleteRow(it--);
			}
		} else if(typeRight==QPROC){
			int aIdx1 = mapper[synIdx1], aIdx2 = mapper[synIdx2];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				string name1=VarTable::getVarTable()->getVarName((*it)[aIdx1]);
				string name2=ProcTable::getProcTable()->getProcName((*it)[aIdx2]);				
				if(name1!=name2) deleteRow(it--);
			}
		} else if(typeRight==QCALL) {
			int aIdx1 = mapper[synIdx1], aIdx2 = mapper[synIdx2];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				string name1=VarTable::getVarTable()->getVarName((*it)[aIdx1]);
				int proc2 = CallsTable::getCallsTable()->getProcCalledByStmt((*it)[aIdx2]);
				string name2=ProcTable::getProcTable()->getProcName(proc2);
				if(name1!=name2) deleteRow(it--);
			}
		}
	} else if(typeLeft==QPROC){
		if(typeRight==QSTRING){
			int aIdx = mapper[synIdx1];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				string name=ProcTable::getProcTable()->getProcName((*it)[aIdx]);
				if(name!=rightArg->getStrVal()) {
					deleteRow(it--);
				}
			}
		} else if(typeRight==QVAR){
			int aIdx1 = mapper[synIdx1], aIdx2 = mapper[synIdx2];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				string name1=ProcTable::getProcTable()->getProcName((*it)[aIdx1]);
				string name2=VarTable::getVarTable()->getVarName((*it)[aIdx2]);
				if(name1!=name2) deleteRow(it--);
			}
		} else if(typeRight==QPROC){
			int aIdx1 = mapper[synIdx1], aIdx2 = mapper[synIdx2];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if((*it)[aIdx1]!=(*it)[aIdx2]) deleteRow(it--);
			}
		} else if(typeRight==QCALL) {
			int aIdx1 = mapper[synIdx1], aIdx2 = mapper[synIdx2];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				string name1=ProcTable::getProcTable()->getProcName((*it)[aIdx1]);
				int proc2 = CallsTable::getCallsTable()->getProcCalledByStmt((*it)[aIdx2]);
				string name2=ProcTable::getProcTable()->getProcName(proc2);
				if(name1!=name2) deleteRow(it--);
			}
		}
	} else if(typeLeft==QCALL){
		if(typeRight==QSTRING){
			int aIdx = mapper[synIdx1];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				int proc = CallsTable::getCallsTable()->getProcCalledByStmt((*it)[aIdx]);
				string name=ProcTable::getProcTable()->getProcName(proc);
				if(name!=rightArg->getStrVal()) deleteRow(it--);
			}
		} else if(typeRight==QVAR){
			int aIdx1 = mapper[synIdx1], aIdx2 = mapper[synIdx2];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				int proc = CallsTable::getCallsTable()->getProcCalledByStmt((*it)[aIdx1]);
				string name1=ProcTable::getProcTable()->getProcName(proc);
				string name2=VarTable::getVarTable()->getVarName((*it)[aIdx2]);
				if(name1!=name2) deleteRow(it--);
			}
		} else if(typeRight==QPROC){
			int aIdx1 = mapper[synIdx1], aIdx2 = mapper[synIdx2];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				int proc = CallsTable::getCallsTable()->getProcCalledByStmt((*it)[aIdx1]);
				string name1=ProcTable::getProcTable()->getProcName(proc);
				string name2=ProcTable::getProcTable()->getProcName((*it)[aIdx2]);				
				if(name1!=name2) deleteRow(it--);
			}
		} else if(typeRight==QCALL && (rightArg->getStrVal()=="procName")) {
			int aIdx1 = mapper[synIdx1], aIdx2 = mapper[synIdx2];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				int proc1 = CallsTable::getCallsTable()->getProcCalledByStmt((*it)[aIdx1]);
				int proc2 = CallsTable::getCallsTable()->getProcCalledByStmt((*it)[aIdx2]);
				if(proc1!=proc2) deleteRow(it--);
			}
		} else {
			if(typeRight==QINT) {
				int aIdx1 = mapper[synIdx1];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if((*it)[aIdx1]!=rightArg->getIntVal()) deleteRow(it--);
				}
			} else {
				int aIdx1 = mapper[synIdx1], aIdx2 = mapper[synIdx2];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if((*it)[aIdx1]!=(*it)[aIdx2]) deleteRow(it--);
				}
			}
		}
	} else if((typeLeft&(QSTMT|QASSIGN|QWHILE|QIF|QPROGLINE))||typeLeft==QCONST){
		if(typeRight==QINT){
			int aIdx1 = mapper[synIdx1];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if((*it)[aIdx1]!=rightArg->getIntVal()) deleteRow(it--);
			}
		} else if((typeRight&(QSTMT|QASSIGN|QWHILE|QIF|QPROGLINE|QCALL))){
			int aIdx1 = mapper[synIdx1], aIdx2 = mapper[synIdx2];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if((*it)[aIdx1]!=(*it)[aIdx2]) deleteRow(it--);
			}
		} else if(typeRight==QCONST){
			int aIdx1 = mapper[synIdx1], aIdx2 = mapper[synIdx2];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if((*it)[aIdx1]!=(*it)[aIdx2]) deleteRow(it--);
			}
		}
	} 
}

void evaluateSuchThatNode(QNode* such){
	//cout << "such" << endl;
	if(!booleanAnswer) return;
	QNode* leftArg = such->getLeftChild();
	QNode* rightArg = such->getRightChild();
	if(leftArg->getType() == QSYN) {
		if(mapper.count(leftArg->getIntVal()) == 0) {
			addAttribute(leftArg->getIntVal(), table, mapper);
		}
	}

	if(rightArg->getType() == QSYN) {
		if(mapper.count(rightArg->getIntVal()) == 0) {
			addAttribute(rightArg->getIntVal(), table, mapper);
		}
	}

	switch(such->getType()) {
	case QPARENT:
		handleParent(such); break;
	case QPARENTT:
		handleParentT(such); break;
	case QFOLLOWS:
		handleFollows(such); break;
	case QFOLLOWST:
		handleFollowsT(such); break;
	case QMODIFIES:
		handleModifies(such); break;
	case QUSES:
		handleUses(such); break;
	case QCALL:
		handleCalls(such); break;
	case QCALLT:
		handleCallsT(such); break;
	case QNEXT:
		handleNext(such); break;
	case QNEXTT:
		handleNextT(such); break;
	case QAFFECT:
		handleAffects(such); break;
	case QAFFECTT:
		handleAffectsT(such); break;
	case QNEXTBIP:
		handleNextBIP(such); break;
	case QNEXTBIPT:
		handleNextBIPT(such); break;
	case QAFFECTBIP:
		handleAffectsBIP(such); break;
	case QAFFECTBIPT:
		handleAffectsBIPT(such); break;
	case QCONTAINS:
		handleContains(such); break;
	case QCONTAINST:
		handleContainsT(such); break;
	case QSIBLING:
		handleSibling(such); break;
	default:
		break;
	}
}

void evaluatePatternNode(QNode* patt){
	//cout << "pat" << endl;
	if(!booleanAnswer) return;
	if(mapper.count(patt->getIntVal()) == 0) {
		addAttribute(patt->getIntVal(), table, mapper);
	}
	SynTable *synT = SynTable::getSynTable();
	int type = synT->getSyn(patt->getIntVal()).second;
	int aIdx = mapper[patt->getIntVal()];
	QNode *leftPatt = patt->getLeftChild();
	int type2 = leftPatt->getType();
	int aIdx2;
	if(type2==QSYN){
		if(mapper.count(leftPatt->getIntVal()) == 0)
			addAttribute(leftPatt->getIntVal(), table, mapper);
		aIdx2 = mapper[leftPatt->getIntVal()];
	}
	if (type == QASSIGN){
		if(type2 == QSYN){
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode *assignNode = st->getStmtNode((*it)[aIdx2]);
				if(*(ModifiesTable::getModifiesTable()->getVarModifiedByStmt((*it)[aIdx]).begin())!=(*it)[aIdx2]) deleteRow(it--);
			}
			//leftPatt->setType(QANY);
		}
		for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
			TNode *assignNode = st->getStmtNode((*it)[aIdx]);
			if(!(st->doesMatchPattern(assignNode,patt))) deleteRow(it--);
		}
	} else if (type == QWHILE){
		QNode *rightPatt = patt->getRightChild();
		int type3 = rightPatt->getType();
		int aIdx3;
		if(type3==QSYN){
			if(mapper.count(rightPatt->getIntVal()) == 0)
				addAttribute(rightPatt->getIntVal(), table, mapper);
		aIdx3 = mapper[rightPatt->getIntVal()];
		}
		if(type2==QANY) {
			if(type3==QANY){
				//pattern while(_,_)
				if(st->getAllWhile().size()==0) clearTable();
			} else if (type3==QSYN){
				//pattern while(_,stmtLst)
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					int whileIdx = (*it)[aIdx];
					int stmtLstIdx = (*it)[aIdx3];
					if(stmtLstIdx != whileIdx+1) deleteRow(it--);
				}
			}
		}
		else if(type2 == QSYN){
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					TNode *whileNode = st->getStmtNode((*it)[aIdx]);
					int varIdx = (*it)[aIdx2];
					if(!(whileNode->getFirstChild()->getAttrib() == varIdx)) deleteRow(it--);
			}
			if(type3==QANY){
				//pattern while(varaible,_)
			}
			else if (type3==QSYN){
				//pattern while(variable,stmtLst)
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					int whileIdx = (*it)[aIdx];
					int stmtLstIdx = (*it)[aIdx3];
					if(stmtLstIdx != whileIdx+1) deleteRow(it--);
				}
			}
		} else {
			// type2=string value
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode *whileNode = st->getStmtNode((*it)[aIdx]);
				int varIdx = VarTable::getVarTable()->getVarIndex(patt->getLeftChild()->getStrVal());
				if(!(whileNode->getFirstChild()->getAttrib() == varIdx)) deleteRow(it--);
			}
			if (type3==QANY){
				//pattern while("var",_)
			}
			else if (type3==QSYN){
				//pattern while("var",stmtLst)
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					int whileIdx = (*it)[aIdx];
					int stmtLstIdx = (*it)[aIdx3];
					if(stmtLstIdx != whileIdx+1) deleteRow(it--);
				}
			}
		}
	} else if (type == QIF){
		QNode *middlePatt = patt->getRightChild();
		int type3 = middlePatt->getType();
		int aIdx3;
		QNode *rightPatt = patt->getRightChild()->getRightSibling();
		int type4 = rightPatt->getType();
		int aIdx4;

		if(type3==QSYN){
			if(mapper.count(middlePatt->getIntVal()) == 0)
				addAttribute(middlePatt->getIntVal(), table, mapper);
		aIdx3 = mapper[middlePatt->getIntVal()];
		}
		if(type4==QSYN){
			if(mapper.count(rightPatt->getIntVal()) == 0)
				addAttribute(rightPatt->getIntVal(), table, mapper);
		aIdx4 = mapper[rightPatt->getIntVal()];
		}

		if(type2==QANY) {
			if(type3==QANY && type4==QANY){
				//pattern if(_,_,_);
				if(st->getAllIf().size()==0) clearTable();
			}
			else if (type3==QSYN && type4==QANY){
				//pattern if(_,i1,_)
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					int ifIdx = (*it)[aIdx];
					int thenStmtLstIdx = (*it)[aIdx3];
					if(thenStmtLstIdx != ifIdx+1) deleteRow(it--);
				}
			}
			else if (type3==QANY && type4==QSYN){
				//pattern if(_,_,i1)
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					TNode *ifNode = st->getStmtNode((*it)[aIdx]);
					TNode *elseNode = ifNode->getFirstChild()->getRightSibling()->getRightSibling();
					int elseStmtLstIdx = (*it)[aIdx4];
					if(elseStmtLstIdx!=elseNode->getFirstChild()->getAttrib()) {
						deleteRow(it--);
					}
				}
			}
			else{
				//pattern if(_,i1,i2)
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					int ifIdx = (*it)[aIdx];
					int stmtLstIdx = (*it)[aIdx3];
					if(stmtLstIdx != ifIdx+1) {
						deleteRow(it--);
					}
				}
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					TNode *ifNode = st->getStmtNode((*it)[aIdx]);
					TNode *elseNode = ifNode->getFirstChild()->getRightSibling()->getRightSibling();
					int elseStmtLstIdx = (*it)[aIdx4];
					if(!(elseStmtLstIdx==elseNode->getFirstChild()->getAttrib())){
						deleteRow(it--);
					}
				}
			}
		}
		else if(type2 == QSYN){
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode *ifNode = st->getStmtNode((*it)[aIdx]);
				int varIdx = (*it)[aIdx2];
				if(!(ifNode->getFirstChild()->getAttrib() == varIdx)) deleteRow(it--);
			}
			if (type3==QSYN && type4==QANY){
				//pattern if(v,i1,_)
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					int ifIdx = (*it)[aIdx];
					int stmtLstIdx = (*it)[aIdx3];
					if(stmtLstIdx != ifIdx+1) deleteRow(it--);
				}
			}
			else if (type3==QANY && type4==QSYN){
				//pattern if(v,_,i2)
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					TNode *ifNode = st->getStmtNode((*it)[aIdx]);
					TNode *elseNode = ifNode->getFirstChild()->getRightSibling()->getRightSibling();
					int elseStmtLstIdx = (*it)[aIdx4];
					if(!(elseStmtLstIdx==elseNode->getFirstChild()->getAttrib())) deleteRow(it--);
				}
			}
			else if (type3==QSYN && type4==QSYN){
				//pattern if(v,i1,i2)
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					int ifIdx = (*it)[aIdx];
					int stmtLstIdx = (*it)[aIdx3];
					if(stmtLstIdx != ifIdx+1) deleteRow(it--);
				}
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					TNode *ifNode = st->getStmtNode((*it)[aIdx]);
					TNode *elseNode = ifNode->getFirstChild()->getRightSibling()->getRightSibling();
					int elseStmtLstIdx = (*it)[aIdx4];
					if(!(elseStmtLstIdx==elseNode->getFirstChild()->getAttrib())) deleteRow(it--);
				}
			}
		} else {
			//type2==string value
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode *ifNode = st->getStmtNode((*it)[aIdx]);
				int varIdx = VarTable::getVarTable()->getVarIndex(patt->getLeftChild()->getStrVal());
				if(!(ifNode->getFirstChild()->getAttrib() == varIdx)) deleteRow(it--);
			}
			if (type3==QSYN && type4==QANY){
				//pattern if("var",i1,_)
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					int ifIdx = (*it)[aIdx];
					int stmtLstIdx = (*it)[aIdx3];
					if(stmtLstIdx != ifIdx+1) deleteRow(it--);
				}
			}
			else if (type3==QANY && type4==QSYN){
				//pattern if("var",_,i2)
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					TNode *ifNode = st->getStmtNode((*it)[aIdx]);
					TNode *elseNode = ifNode->getFirstChild()->getRightSibling()->getRightSibling();
					int elseStmtLstIdx = (*it)[aIdx4];
					if(!(elseStmtLstIdx==elseNode->getFirstChild()->getAttrib())) deleteRow(it--);
				}
			}
			else if (type3==QSYN && type4==QSYN){
				//pattern if("var",i1,i2)
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					int ifIdx = (*it)[aIdx];
					int stmtLstIdx = (*it)[aIdx3];
					if(stmtLstIdx != ifIdx+1) deleteRow(it--);
				}
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					TNode *ifNode = st->getStmtNode((*it)[aIdx]);
					TNode *elseNode = ifNode->getFirstChild()->getRightSibling()->getRightSibling();
					int elseStmtLstIdx = (*it)[aIdx4];
					if(!(elseStmtLstIdx==elseNode->getFirstChild()->getAttrib())) deleteRow(it--);
				}
			}
		}
	}
	//cout << "pat" << endl;
}

void evaluateSelectNode(QNode* sel){
	//cout << "sel" << endl;
	if(booleanAnswer){
		int selIdx = sel->getLeftChild()->getIntVal();
		int selType = syn->getSyn(selIdx).second;
		if(mapper.count(selIdx) == 0) {
			if(mapperResult.count(selIdx) == 0)
				addAttribute(selIdx, resultTable, mapperResult);
		} else {
			int aSelIdx = mapper[selIdx];

			set<int> unique;
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if( (selType == QCALL)&&(sel->getLeftChild()->getStrVal()=="procName")){
					unique.insert(callst->getProcCalledByStmt((*it)[aSelIdx]));
				} else
					unique.insert((*it)[aSelIdx]);
			}

			list< vector<int> > newCol, old;
			
			vector<int> aux;
			aux.push_back(mapperResult.size());
			newCol.push_back(aux);
			for(set<int>::iterator it = unique.begin(); it != unique.end(); it++) {
				aux.clear();
				aux.push_back(*it);
				newCol.push_back(aux);
			}
			
			mapperResult.insert(pair<int,int>(selIdx, mapperResult.size()));

			old = list< vector<int> >(resultTable.begin(), resultTable.end());
			cartesianProduct(old, newCol, resultTable);			
		}
		/*for(set<int>::iterator it = unique.begin(); it != unique.end(); it++) {
			if(selType == QVAR) {
				resultString.push_back(var->getVarName(*it));
			} 
			else if(selType ==QPROC){
				resultString.push_back(pt->getProcName(*it));
			}
			else if((selType == QCALL)&&(sel->getLeftChild()->getStrVal()=="procName")){
				resultString.push_back(pt->getProcName(*it));
			}
			else {
				stringstream out;
				out << *it;
				resultString.push_back(out.str());
			}
		}*/
	}
}

void evaluateSelectNodes(vector<QNode*> select) {
	set<int> selSet;
	vector<QNode*> selVector;
	for(int i = 0; (unsigned)i < select.size(); i++) {
		int selIdx = select[i]->getLeftChild()->getIntVal();
		int selType = syn->getSyn(selIdx).second;
		if(mapper.count(selIdx) == 0) {
			addAttribute(selIdx, table, mapper);
		}
		selSet.insert(selIdx);
	}

	list< vector<int> > newTable;
	newTable.push_back(vector<int>());
	for(set<int>::iterator it = selSet.begin(); it != selSet.end(); it++) {
		for(int i = 0; (unsigned)i < select.size(); i++) {
			int selIdx = select[i]->getLeftChild()->getIntVal();
			if(selIdx == (*it)) {
				selVector.push_back(select[i]);
				break;
			}
		}
		mapperResult.insert(pair<int,int>(*it, mapperResult.size()));
		newTable.begin()->push_back(*it);
	}

	set< vector<int> > unique;
	
	for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
		vector<int> tmp;
		for(int i = 0; (unsigned)i < selVector.size(); i++) {
			int selIdx = selVector[i]->getLeftChild()->getIntVal();
			int selType = syn->getSyn(selIdx).second;
			int aSelIdx = mapper[selIdx];
			/*if( (selType == QCALL)&&(selVector[i]->getLeftChild()->getStrVal()=="procName")){
				//cout << (*it)[aSelIdx];
				tmp.push_back(callst->getProcCalledByStmt((*it)[aSelIdx]));
			} else {
				tmp.push_back((*it)[aSelIdx]);
			}*/
			tmp.push_back((*it)[aSelIdx]);
		}
		unique.insert(tmp);
	}

	for(set< vector<int> >::iterator it = unique.begin(); it != unique.end(); it++) {
		newTable.push_back(*it);
	}

	list< vector<int> > old = list< vector<int> >(resultTable.begin(), resultTable.end());
	cartesianProduct(old, newTable, resultTable);			
}

void evaluateNode(QNode* node){
	//cout<<"evaluate "<< node->getType() <<endl;
	switch(node->getType()){
		case QWITH: evaluateWithNode(node); break;
		case QSYN:	evaluatePatternNode(node); break;
		case QSELECT: evaluateSelectNode(node); break;
		default: evaluateSuchThatNode(node);
	}
}

void evaluateCluster(vector<QNode*> cluster){
	for(unsigned i=0;i<cluster.size();i++){
		//cout <<"evaluating cluster "<<endl;
		if(cluster[i]->getType() != QSELECT) {
			evaluateNode(cluster[i]);
		} else {
			evaluateSelectNodes(vector<QNode*>(cluster.begin()+i, cluster.end()));
			break;
		}
	}
}

void formatResult() {
	vector<QNode*> tuple = qt->getTuple();
	int tmp = 0;
	set<vector<int>> res;
	for(list<vector<int> >::iterator it = resultTable.begin(); it != resultTable.end(); it++) {
		if(!tmp++) continue;
		vector<int> ans;
		for(int j = 0; (unsigned)j < tuple.size(); j++) {
			int selIdx = tuple[j]->getLeftChild()->getIntVal();
			int selType = syn->getSyn(selIdx).second;
			int aSelIdx = mapperResult[selIdx];
			if((selType == QCALL)&&(tuple[j]->getLeftChild()->getStrVal()=="procName")){
				ans.push_back(callst->getProcCalledByStmt((*it)[aSelIdx]));
			}
			else {
				ans.push_back((*it)[aSelIdx]);
			}
		}
		res.insert(ans);
	}
	for(set<vector<int> >::iterator it = res.begin(); it != res.end(); it++) {
		string ans = "";
		for(int j = 0; (unsigned)j < tuple.size(); j++) {
			if(j) ans += " ";
			int selIdx = tuple[j]->getLeftChild()->getIntVal();
			int selType = syn->getSyn(selIdx).second;
			if(selType == QVAR) {
				ans += var->getVarName((*it)[j]);
			} 
			else if(selType == QPROC){
				ans += pt->getProcName((*it)[j]);
			}
			else if((selType == QCALL)&&(tuple[j]->getLeftChild()->getStrVal()=="procName")){
				ans += pt->getProcName((*it)[j]);
			}
			else {
				stringstream out;
				out << (*it)[j];
				ans += out.str();
			}
		}
		resultString.push_back(ans);
	}
}

void processClauses(){
	//cout<<"evaluating"<<endl;
	vector<QNode*> cluster = qt->nextClauses();
	while(cluster.size()!=0){		
		table.clear();
		mapper.clear();
		evaluateCluster(cluster);
		cluster = qt->nextClauses();
	}
	if(!booleanAnswer) {
		resultString.clear();
	} else {
		formatResult();
	}
	if (qt->isBoolean()){
		if(booleanAnswer) {
			resultString.push_back("true");
		}
		else{
			resultString.push_back("false");
		}
	}
}

void handleParent(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QINT) {
		if(rightType == QINT) {
			if(!(stmt1->isParent(stmt2))) clearTable();
		} else if(rightType == QANY) {
			if(stmt1->getParentedBy().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(!(stmt1->isParent(stmtNode))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QINT) {
			if(stmt2->getParent() == NULL) clearTable();
		} else if(rightType == QANY) {
			if(st->getAllWhile().size() == 0 && st->getAllIf().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(stmtNode->getParent() == NULL) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QINT) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(!(stmtNode->isParent(stmt2))) deleteRow(it--);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(stmtNode->getParentedBy().size() == 0) deleteRow(it--);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* s1 = st->getStmtNode((*it)[aIdx1]);
				TNode* s2 = st->getStmtNode((*it)[aIdx2]);
				if(!(s1->isParent(s2))) deleteRow(it--);
			}
		}
	}
}

void handleParentT(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QINT) {
		if(rightType == QINT) {
			if(!(stmt1->isParentTransitive(stmt2))) clearTable();
		} else if(rightType == QANY) {
			if(stmt1->getParentedBy().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(!(stmt1->isParentTransitive(stmtNode))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QINT) {
			if(stmt2->getParent() == NULL) clearTable();
		} else if(rightType == QANY) {
			if(st->getAllWhile().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(stmtNode->getParent() == NULL) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QINT) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(!(stmtNode->isParentTransitive(stmt2))) deleteRow(it--);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(stmtNode->getParentedBy().size() == 0) deleteRow(it--);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* s1 = st->getStmtNode((*it)[aIdx1]);
				TNode* s2 = st->getStmtNode((*it)[aIdx2]);
				if(!(s1->isParentTransitive(s2))) deleteRow(it--);
			}
		}
	}
}

void handleFollows(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QINT) {
		if(rightType == QINT) {
			if(!(stmt1->isFollows(stmt2))) clearTable();
		} else if(rightType == QANY) {
			if(stmt1->getFollows() == NULL) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(!(stmt1->isFollows(stmtNode))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QINT) {
			if(stmt2->getFollowedBy() == NULL) clearTable();
		} else if(rightType == QANY) {
			bool found = false;
			for(int i = 0; i < st->getSize(); i++) {
				TNode* stmtNode = st->getStmtNode(i+1);
				if(stmtNode->getFollows() != NULL) { found = true; break; }
			}
			if(!found) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(stmtNode->getFollowedBy() == NULL) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QINT) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(!(stmtNode->isFollows(stmt2))) deleteRow(it--);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(stmtNode->getFollows() == NULL) deleteRow(it--);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* s1 = st->getStmtNode((*it)[aIdx1]);
				TNode* s2 = st->getStmtNode((*it)[aIdx2]);
				if(!(s1->isFollows(s2))) deleteRow(it--);
			}
		}
	}
}

void handleFollowsT(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QINT) {
		if(rightType == QINT) {
			if(!(stmt1->isFollowsTransitive(stmt2))) clearTable();
		} else if(rightType == QANY) {
			if(stmt1->getFollows() == NULL) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(!(stmt1->isFollowsTransitive(stmtNode))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QINT) {
			if(stmt2->getFollowedBy() == NULL) clearTable();
		} else if(rightType == QANY) {
			bool found = false;
			for(int i = 0; i < st->getSize(); i++) {
				TNode* stmtNode = st->getStmtNode(i+1);
				if(stmtNode->getFollows() != NULL) { found = true; break; }
			}
			if(!found) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(stmtNode->getFollowedBy() == NULL) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QINT) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(!(stmtNode->isFollowsTransitive(stmt2))) deleteRow(it--);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* stmtNode = st->getStmtNode((*it)[aIdx]);
				if(stmtNode->getFollows() == NULL) deleteRow(it--);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode* s1 = st->getStmtNode((*it)[aIdx1]);
				TNode* s2 = st->getStmtNode((*it)[aIdx2]);
				if(!(s1->isFollowsTransitive(s2))) deleteRow(it--);
			}
		}
	}
}

void handleModifies(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QINT) {
		if(rightType == QSTRING) {
			if(!(m->isModifiesStmt(constLeft,varIdx))) clearTable();
		} else if(rightType == QANY) {
			if(m->getVarModifiedByStmt(constLeft).size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(m->isModifiesStmt(constLeft,(*it)[aIdx]))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QSTRING) {
			if(m->getStmtModifiesVar(varIdx).size() == 0) clearTable();
		} else if(rightType == QANY) {
			if(st->getAllAssign().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(m->getStmtModifiesVar((*it)[aIdx]).size() == 0) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		int entType = SynTable::getSynTable()->getSyn(synIdxLeft).second;

		if(entType != QPROC) {
			if(rightType == QSTRING) {
				int aIdx = mapper[synIdxLeft];			
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(m->isModifiesStmt((*it)[aIdx],varIdx))) deleteRow(it--);
				}
			} else if(rightType == QANY) {
				int aIdx = mapper[synIdxLeft];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(m->getVarModifiedByStmt((*it)[aIdx]).size() == 0) deleteRow(it--);
				}
			} else if(rightType == QSYN) {
				int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(m->isModifiesStmt((*it)[aIdx1],(*it)[aIdx2]))) deleteRow(it--);
				}
			}
		} else {
			if(rightType == QSTRING) {
				int aIdx = mapper[synIdxLeft];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(m->isModifiesProc((*it)[aIdx],varIdx))) deleteRow(it--);
				}
			} else if(rightType == QANY) {
				int aIdx = mapper[synIdxLeft];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(m->getVarModifiedByProc((*it)[aIdx]).size() == 0) deleteRow(it--);
				}
			} else if(rightType == QSYN) {
				int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(m->isModifiesProc((*it)[aIdx1],(*it)[aIdx2]))) deleteRow(it--);
				}
			}
		}
	} else if(leftType == QSTRING) {
		if(rightType == QSTRING) {
			if(!(m->isModifiesProc(procIdx,varIdx))) clearTable();
		} else if(rightType == QANY) {
			if(m->getVarModifiedByProc(procIdx).size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(m->isModifiesProc(procIdx,(*it)[aIdx]))) deleteRow(it--);
			}
		}
	}
}

void handleUses(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }
	if(leftType == QINT) {
		if(rightType == QSTRING) {
			if(!(u->isUsesStmt(constLeft,varIdx))) clearTable();
		} else if(rightType == QANY) {
			if(u->getVarUsedByStmt(constLeft).size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(u->isUsesStmt(constLeft,(*it)[aIdx]))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QSTRING) {
			if(u->getStmtUsesVar(varIdx).size() == 0) clearTable();
		} else if(rightType == QANY) {
			bool found = false;
			for(int i = 0; i < st->getSize(); i++) {
				if(u->getVarUsedByStmt(i+1).size() > 0) { found = true; break; }
			}
			if(!found) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(u->getStmtUsesVar((*it)[aIdx]).size() == 0) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		int entType = SynTable::getSynTable()->getSyn(synIdxLeft).second;

		if(entType != QPROC) {
			if(rightType == QSTRING) {
				int aIdx = mapper[synIdxLeft];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(u->isUsesStmt((*it)[aIdx],varIdx))) deleteRow(it--);
				}
			} else if(rightType == QANY) {
				int aIdx = mapper[synIdxLeft];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(u->getVarUsedByStmt((*it)[aIdx]).size() == 0) deleteRow(it--);
				}
			} else if(rightType == QSYN) {
				int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(u->isUsesStmt((*it)[aIdx1],(*it)[aIdx2]))) deleteRow(it--);
				}
			}
		} else {
			if(rightType == QSTRING) {
				int aIdx = mapper[synIdxLeft];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(u->isUsesProc((*it)[aIdx],varIdx))) deleteRow(it--);
				}
			} else if(rightType == QANY) {
				int aIdx = mapper[synIdxLeft];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(u->getVarUsedByProc((*it)[aIdx]).size() == 0) deleteRow(it--);
				}
			} else if(rightType == QSYN) {
				int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(u->isUsesProc((*it)[aIdx1],(*it)[aIdx2]))) deleteRow(it--);
				}
			}
		}
	} else if(leftType == QSTRING) {
		if(rightType == QSTRING) {
			if(!(u->isUsesProc(procIdx,varIdx))) clearTable();
		} else if(rightType == QANY) {
			if(u->getVarUsedByProc(procIdx).size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(u->isUsesProc(procIdx,(*it)[aIdx]))) deleteRow(it--);
			}
		}
	}
}

void handleCalls(QNode* query) {
	initVarsForCalls(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }
	if(leftType == QSTRING) {
		if(rightType == QSTRING) {
			if(!(callst->procCallsProc(procIdxLeft,procIdxRight))) clearTable();
		} else if(rightType == QANY) {
			if(callst->getProcCalledByProc(procIdxLeft).size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(callst->procCallsProc(procIdxLeft,(*it)[aIdx]))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QSTRING) {
			if(callst->getProcCallsProc(procIdxRight).size() == 0) clearTable();
		} else if(rightType == QANY) {
			if(callst->getAllCall().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(callst->getProcCallsProc((*it)[aIdx]).size() == 0) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QSTRING) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(callst->procCallsProc((*it)[aIdx],procIdxRight))) deleteRow(it--);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(callst->getProcCalledByProc((*it)[aIdx]).size() == 0) deleteRow(it--);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(callst->procCallsProc((*it)[aIdx1],(*it)[aIdx2]))) deleteRow(it--);
			}
		}
	}
}

void handleCallsT(QNode* query) {
	initVarsForCalls(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }
	if(leftType == QSTRING) {
		if(rightType == QSTRING) {
			if(!(callst->procCallsProcTransitive(procIdxLeft,procIdxRight))) clearTable();
		} else if(rightType == QANY) {
			if(callst->getProcCalledByProc(procIdxLeft).size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(callst->procCallsProcTransitive(procIdxLeft,(*it)[aIdx]))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QSTRING) {
			if(callst->getProcCallsProc(procIdxRight).size() == 0) clearTable();
		} else if(rightType == QANY) {
			if(callst->getAllCall().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(callst->getProcCallsProcTransitive((*it)[aIdx]).size() == 0) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QSTRING) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(callst->procCallsProcTransitive((*it)[aIdx],procIdxRight))) deleteRow(it--);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(callst->getProcCalledByProc((*it)[aIdx]).size() == 0) deleteRow(it--);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(callst->procCallsProcTransitive((*it)[aIdx1],(*it)[aIdx2]))) deleteRow(it--);
			}
		}
	}
}

void handleNext(QNode* query) {
	initVarsForNext(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QINT) {
		if(rightType == QINT) {
			if(!(line1->isNext(line2))) clearTable();
		} else if(rightType == QANY) {
			if(line1->getNext().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(!(line1->isNext(lineNode))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QINT) {
			if(line2->getPrev().size() == 0) clearTable();
		} else if(rightType == QANY) {
			bool found = false;
			for(ui i = 0; i < st->getAllProgline().size(); i++) {
				GNode* lineNode = cfg->getNode(i+1);
				if(lineNode->getNext().size() > 0) { found = true; break; }
			}
			if(!found) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(lineNode->getPrev().size() == 0) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QINT) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(!(lineNode->isNext(line2))) deleteRow(it--);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(lineNode->getNext().size() == 0) deleteRow(it--);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* l1 = cfg->getNode((*it)[aIdx1]);
				GNode* l2 = cfg->getNode((*it)[aIdx2]);
				if(!(l1->isNext(l2))) deleteRow(it--);
			}
		}
	}
}

void handleNextT(QNode* query) {
	initVarsForNext(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QINT) {
		if(rightType == QINT) {
			if(!(line1->isNextTransitive(line2))) clearTable();
		} else if(rightType == QANY) {
			if(line1->getNext().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(!(line1->isNextTransitive(lineNode))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QINT) {
			if(line2->getPrev().size() == 0) clearTable();
		} else if(rightType == QANY) {
			bool found = false;
			for(ui i = 0; i < st->getAllProgline().size(); i++) {
				GNode* lineNode = cfg->getNode(i+1);
				if(lineNode->getNext().size() > 0) { found = true; break; }
			}
			if(!found) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(lineNode->getPrev().size() == 0) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QINT) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(!(lineNode->isNextTransitive(line2))) deleteRow(it--);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(lineNode->getNext().size() == 0) deleteRow(it--);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* l1 = cfg->getNode((*it)[aIdx1]);
				GNode* l2 = cfg->getNode((*it)[aIdx2]);
				if(!(l1->isNextTransitive(l2))) deleteRow(it--);
			}
		}
	}
}

void handleNextBIP(QNode* query) {
	initVarsForNext(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QINT) {
		if(rightType == QINT) {
			if(!(line1->isNextBIP(line2))) clearTable();
		} else if(rightType == QANY) {
			if(line1->getNextBIP().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(!(line1->isNextBIP(lineNode))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QINT) {
			if(line2->getPrevBIP().size() == 0) clearTable();
		} else if(rightType == QANY) {
			bool found = false;
			for(ui i = 0; i < st->getAllProgline().size(); i++) {
				GNode* lineNode = cfg->getNode(i+1);
				if(lineNode->getNextBIP().size() > 0) { found = true; break; }
			}
			if(!found) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(lineNode->getPrevBIP().size() == 0) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QINT) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(!(lineNode->isNextBIP(line2))) deleteRow(it--);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(lineNode->getNextBIP().size() == 0) deleteRow(it--);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* l1 = cfg->getNode((*it)[aIdx1]);
				GNode* l2 = cfg->getNode((*it)[aIdx2]);
				if(!(l1->isNextBIP(l2))) deleteRow(it--);
			}
		}
	}
}

void handleNextBIPT(QNode* query) {
	initVarsForNext(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QINT) {
		if(rightType == QINT) {
			if(!(line1->isNextBIPTransitive(line2))) clearTable();
		} else if(rightType == QANY) {
			if(line1->getNextBIP().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(!(line1->isNextBIPTransitive(lineNode))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QINT) {
			if(line2->getPrevBIP().size() == 0) clearTable();
		} else if(rightType == QANY) {
			bool found = false;
			for(ui i = 0; i < st->getAllProgline().size(); i++) {
				GNode* lineNode = cfg->getNode(i+1);
				if(lineNode->getNextBIP().size() > 0) { found = true; break; }
			}
			if(!found) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(lineNode->getPrevBIP().size() == 0) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QINT) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(!(lineNode->isNextBIPTransitive(line2))) deleteRow(it--);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* lineNode = cfg->getNode((*it)[aIdx]);
				if(lineNode->getNextBIP().size() == 0) deleteRow(it--);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				GNode* l1 = cfg->getNode((*it)[aIdx1]);
				GNode* l2 = cfg->getNode((*it)[aIdx2]);
				if(!(l1->isNextBIPTransitive(l2))) deleteRow(it--);
			}
		}
	}
}

void handleAffects(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QINT) {
		if(rightType == QINT) {
			if(!(a->isAffects(constLeft,constRight))) clearTable();
		} else if(rightType == QANY) {
			if(a->getAffects(constLeft).size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(a->isAffects(constLeft,(*it)[aIdx]))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QINT) {
			if(a->getAffectedBy(constRight).size() == 0) clearTable();
		} else if(rightType == QANY) {
			bool exist=false;
			vector<STMT_NO> stmts = st->getAllAssign();
			for(unsigned i=0;i< stmts.size();i++){
				if(a->getAffects(stmts[i]).size()!=0){
					exist = true;
					break;
				}
			}
			if(!exist)
				clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(a->getAffectedBy((*it)[aIdx]).size() == 0) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QINT) {
				int aIdx = mapper[synIdxLeft];			
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(a->isAffects((*it)[aIdx],constRight))) deleteRow(it--);
				}
			} else if(rightType == QANY) {
				int aIdx = mapper[synIdxLeft];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(a->getAffects((*it)[aIdx]).size() == 0) deleteRow(it--);
				}
			} else if(rightType == QSYN) {
				int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(a->isAffects((*it)[aIdx1],(*it)[aIdx2]))) deleteRow(it--);
				}
			}
		} 
}

void handleAffectsT(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QINT) {
		if(rightType == QINT) {
			if(!(a->isAffectsTransitive(constLeft,constRight))) clearTable();
		} else if(rightType == QANY) {
			if(a->getAffectsTransitive(constLeft).size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(a->isAffectsTransitive(constLeft,(*it)[aIdx]))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QINT) {
			if(a->getAffectedByTransitive(constRight).size() == 0) clearTable();
		} else if(rightType == QANY) {
			bool exist=false;
			vector<STMT_NO> stmts = st->getAllAssign();
			for(unsigned i=0;i< stmts.size();i++){
				if(a->getAffects(stmts[i]).size()!=0){
					exist = true;
					break;
				}
			}
			if(!exist)
				clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(a->getAffectedByTransitive((*it)[aIdx]).size() == 0) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QINT) {
				int aIdx = mapper[synIdxLeft];			
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(a->isAffectsTransitive((*it)[aIdx],constRight))) deleteRow(it--);
				}
			} else if(rightType == QANY) {
				int aIdx = mapper[synIdxLeft];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(a->getAffectsTransitive((*it)[aIdx]).size() == 0) deleteRow(it--);
				}
			} else if(rightType == QSYN) {
				int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(a->isAffectsTransitive((*it)[aIdx1],(*it)[aIdx2]))) deleteRow(it--);
				}
			}
		} 
}

void handleAffectsBIP(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QINT) {
		if(rightType == QINT) {
			if(!(ab->isAffects(constLeft,constRight))) clearTable();
		} else if(rightType == QANY) {
			if(ab->getAffects(constLeft).size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(ab->isAffects(constLeft,(*it)[aIdx]))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QINT) {
			if(ab->getAffectedBy(constRight).size() == 0) clearTable();
		} else if(rightType == QANY) {
			bool exist=false;
			vector<STMT_NO> stmts = st->getAllAssign();
			for(unsigned i=0;i< stmts.size();i++){
				if(ab->getAffects(stmts[i]).size()!=0){
					exist = true;
					break;
				}
			}
			if(!exist)
				clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(ab->getAffectedBy((*it)[aIdx]).size() == 0) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QINT) {
				int aIdx = mapper[synIdxLeft];			
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(ab->isAffects((*it)[aIdx],constRight))) deleteRow(it--);
				}
			} else if(rightType == QANY) {
				int aIdx = mapper[synIdxLeft];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(ab->getAffects((*it)[aIdx]).size() == 0) deleteRow(it--);
				}
			} else if(rightType == QSYN) {
				int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(ab->isAffects((*it)[aIdx1],(*it)[aIdx2]))) deleteRow(it--);
				}
			}
		} 
}

void handleAffectsBIPT(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QINT) {
		if(rightType == QINT) {
			if(!(ab->isAffectsTransitive(constLeft,constRight))) clearTable();
		} else if(rightType == QANY) {
			if(ab->getAffectsTransitive(constLeft).size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(ab->isAffectsTransitive(constLeft,(*it)[aIdx]))) deleteRow(it--);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QINT) {
			if(ab->getAffectedByTransitive(constRight).size() == 0) clearTable();
		} else if(rightType == QANY) {
			bool exist=false;
			vector<STMT_NO> stmts = st->getAllAssign();
			for(unsigned i=0;i< stmts.size();i++){
				if(ab->getAffects(stmts[i]).size()!=0){
					exist = true;
					break;
				}
			}
			if(!exist)
				clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(ab->getAffectedByTransitive((*it)[aIdx]).size() == 0) deleteRow(it--);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QINT) {
				int aIdx = mapper[synIdxLeft];			
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(ab->isAffectsTransitive((*it)[aIdx],constRight))) deleteRow(it--);
				}
			} else if(rightType == QANY) {
				int aIdx = mapper[synIdxLeft];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(ab->getAffectsTransitive((*it)[aIdx]).size() == 0) deleteRow(it--);
				}
			} else if(rightType == QSYN) {
				int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
				for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
					if(!(ab->isAffectsTransitive((*it)[aIdx1],(*it)[aIdx2]))) deleteRow(it--);
				}
			}
		} 
}

void handleContains(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QSYN) {
		int aIdx = mapper[synIdxLeft];
		int leftEntType = syn->getSyn(synIdxLeft).second;
		if(rightType == QINT){
		}
		else if(rightType ==QSYN){
			int aIdx2 = mapper[synIdxRight];
			int rightEntType = syn->getSyn(synIdxRight).second;
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				if(!(ast->contains((QNodeType)leftEntType,aIdx,(QNodeType)rightEntType,aIdx2))) deleteRow(it--);
			}
		}
	}
	else if(leftType == QINT){
		if(rightType == QINT){
		}
		else if(rightType ==QSYN){
		}
	}
}

void handleContainsT(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }
}

void handleSibling(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }
}

vector<string> QueryEvaluator::evaluate() {
	qt = QueryTree::getQueryTree();
	syn = SynTable::getSynTable();
	st = StmtTable::getStmtTable();
	pt = ProcTable::getProcTable();
	m = ModifiesTable::getModifiesTable();
	var = VarTable::getVarTable();
	u = UsesTable::getUsesTable();
	ast = AST::getAST();
	cfg = CFG::getCFG();
	ct = ConstantTable::getConstantTable();
	a = AffectsTable::getAffectsTable();
	a->init();
	ab = AffectsBIPTable::getAffectsBIPTable();
	ab->init();
	callst = CallsTable::getCallsTable();

	initTable();
	initResultTable();

	resultString.clear();
	
	processClauses();

	PQLParser::cleanUp();
	return resultString;
}