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
static list< vector<int> > table;
static map< int, int > mapper;
static AffectsTable *a;

static void cartesianProduct(list< vector<int> >& table1, list< vector<int> >& table2, list< vector<int> >& result);
static vector<int> allEntitiesWithType(int type);
static vector<string> resultString;

static void initVars(QNode* leftArg, QNode* rightArg);
static void initVarsForCalls(QNode* leftArg, QNode* rightArg);
static void initVarsForNext(QNode* leftArg, QNode* rightArg);

static void initTable();
static void addAttribute(int synIdx);
static void clearTable();
static bool isEmptyResult();

static void evaluateWith();
static void evaluateSuchThat();
static void evaluatePattern();
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
static void handleAffects(QNode* query);
static void handleAffectsT(QNode* query);

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
	/*
	result.assign(table1.size()+table2.size(),vector<int>());
	for(unsigned k = 0; k < table1.size(); k++) { // for each attribute
	if(result[k].size() == 0) {
	result[k].push_back(table1[k][0]);
	}
	}
	int currSz = table1.size();
	for(unsigned k = 0; k < table2.size(); k++) {
	if(result[currSz].size() == 0) {
	result[currSz].push_back(table2[k][0]);
	}
	}

	for(unsigned i = 1; i < table1[0].size(); i++) { // for each row in table 1
	for(unsigned j = 1; j < table2[0].size(); j++) { // for each row in table 2
	for(unsigned k = 0; k < table1.size(); k++) { // for each attribute
	result[k].push_back(table1[k][i]);
	}
	currSz = table1.size();
	for(unsigned k = 0; k < table2.size(); k++) {
	result[currSz].push_back(table2[k][j]);
	currSz ++;
	}
	}
	}
	*/
}

vector<int> allEntitiesWithType(int type) {
	vector<int> result;
	switch(type) {
	case QSTMT:
		result = st->getAllStmt(); break;
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

	/*QNode* sel = qt->getResult()->getLeftChild();
	QNode* suchthat = qt->getSuchThat()->getLeftChild();
	QNode* pattern = qt->getPattern()->getLeftChild();

	set<int> attribs;
	attribs.insert(sel->getIntVal());

	while(suchthat != NULL) {
	QNode* leftArg = suchthat->getLeftChild();
	QNode* rightArg = suchthat->getRightChild();
	if(leftArg->getType() == QSYN) {
	attribs.insert(leftArg->getIntVal());
	}
	if(rightArg->getType() == QSYN) {
	attribs.insert(rightArg->getIntVal());
	}
	suchthat = suchthat->getRightSibling();
	}

	if(pattern != NULL) {
	attribs.insert(pattern->getIntVal());
	}

	vector< vector<int> > result;
	set<int>::iterator it;
	int count = 0;
	for(it = attribs.begin(); it != attribs.end(); it++) {
	mapper.insert(pair<int,int>(*it,count++));
	int entType = syn->getSyn(*it).second;
	vector<int> allEnt = allEntitiesWithType(entType);
	if(it == attribs.begin()) {
	result.push_back(vector<int>());
	result[0].push_back(*it);
	for(unsigned i = 0; i < allEnt.size(); i++) {
	result[0].push_back(allEnt[i]);
	}
	} else {
	vector< vector<int> > newCol;
	newCol.push_back(vector<int>());
	newCol[0].push_back(*it);
	for(unsigned i = 0; i < allEnt.size(); i++) {
	newCol[0].push_back(allEnt[i]);
	}
	result = cartesianProduct(result,newCol);
	}
	}
	table = result;*/
}

void addAttribute(int synIdx) {
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

	if(table.size() == 0) {
		table = newCol;
	} else {
		list< vector<int> > result;
		cartesianProduct(table,newCol,result);
		table=result;
	}

	mapper.insert(pair<int,int>(synIdx,mapper.size()));
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
			addAttribute(leftArg->getIntVal());
		}
	}
	if(rightArg->getType() == QSYN) {
		if(mapper.count(rightArg->getIntVal()) == 0) {
			addAttribute(rightArg->getIntVal());
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
			addAttribute(leftArg->getIntVal());
		}
	}

	if(rightArg->getType() == QSYN) {
		if(mapper.count(rightArg->getIntVal()) == 0) {
			addAttribute(rightArg->getIntVal());
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
	default:
		break;
	}
}

void evaluatePatternNode(QNode* patt){
	//cout << "pat" << endl;
	if(!booleanAnswer) return;
	if(mapper.count(patt->getIntVal()) == 0) {
		addAttribute(patt->getIntVal());
	}
	SynTable *synT = SynTable::getSynTable();
	int type = synT->getSyn(patt->getIntVal()).second;
	int aIdx = mapper[patt->getIntVal()];
	QNode *leftPatt = patt->getLeftChild();
	int type2 = leftPatt->getType();
	int aIdx2;
	if(type2==QSYN){
		if(mapper.count(leftPatt->getIntVal()) == 0)
			addAttribute(leftPatt->getIntVal());
		aIdx2 = mapper[leftPatt->getIntVal()];
	}
	if (type == QASSIGN){
		if(type2 == QSYN){
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode *assignNode = st->getStmtNode((*it)[aIdx2]);
				if(*(ModifiesTable::getModifiesTable()->getVarModifiedByStmt((*it)[aIdx]).begin())!=(*it)[aIdx2]) deleteRow(it--);
			}
			leftPatt->setType(QANY);
		}
		for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
			TNode *assignNode = st->getStmtNode((*it)[aIdx]);
			if(!(st->doesMatchPattern(assignNode,patt))) deleteRow(it--);
		}
	} else if (type == QWHILE){
		if(type2==QANY && st->getAllWhile().size()==0) clearTable();
		else if(type2 == QSYN){
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode *whileNode = st->getStmtNode((*it)[aIdx]);
				int varIdx = (*it)[aIdx2];
				if(!(whileNode->getFirstChild()->getAttrib() == varIdx)) deleteRow(it--);
			}
		} else {
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode *whileNode = st->getStmtNode((*it)[aIdx]);
				int varIdx = VarTable::getVarTable()->getVarIndex(patt->getLeftChild()->getStrVal());
				if(!(whileNode->getFirstChild()->getAttrib() == varIdx)) deleteRow(it--);
			}
		}
	} else if (type == QIF){
		if(type2==QANY && st->getAllIf().size()==0) clearTable();
		else if(type2 == QSYN){
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode *ifNode = st->getStmtNode((*it)[aIdx]);
				int varIdx = (*it)[aIdx2];
				if(!(ifNode->getFirstChild()->getAttrib() == varIdx)) deleteRow(it--);
			}
		} else {
			for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
				TNode *ifNode = st->getStmtNode((*it)[aIdx]);
				int varIdx = VarTable::getVarTable()->getVarIndex(patt->getLeftChild()->getStrVal());
				if(!(ifNode->getFirstChild()->getAttrib() == varIdx)) deleteRow(it--);
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
			initTable();
			addAttribute(selIdx);
		}
		int aSelIdx = mapper[selIdx];

		/*
		for(ui i = 0; i < table.size(); i++) {
		for(ui j = 0; j < table[i].size(); j++) {
		cout << table[i][j] << " ";
		}
		cout << endl;
		}
		*/

		set<int> unique;
		for(list<vector<int> >::iterator it = ++table.begin(); it != table.end(); it++) {
			if( (selType == QCALL)&&(sel->getLeftChild()->getStrVal()=="procName")){
				unique.insert(callst->getProcCalledByStmt((*it)[aSelIdx]));
			} else
				unique.insert((*it)[aSelIdx]);
		}

		for(set<int>::iterator it = unique.begin(); it != unique.end(); it++) {
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
		}
	}
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
		evaluateNode(cluster[i]);
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
	if(!booleanAnswer)
		resultString.clear();
	if (qt->isBoolean()){
		if(booleanAnswer) {
			resultString.push_back("true");
		}
		else{
			resultString.push_back("false");
		}
	}
}

void evaluateWith(){
	QNode* with = qt->getWith()->getLeftChild(); // ONLY 1 WITH

	while(with != NULL){
		if(!booleanAnswer) return;
		/*if (AbstractWrapper::GlobalStop) {
		// do cleanup 
		PQLParser::cleanUp();
		return;
		}*/
		evaluateWithNode(with);
		with = with->getRightSibling();
	}
}

void evaluateSuchThat() {
	QNode* such = qt->getSuchThat()->getLeftChild(); // ONLY 1 SUCH THAT
	while(such != NULL){
		if(!booleanAnswer) return;
		/*if (AbstractWrapper::GlobalStop) {
		// do cleanup 
		PQLParser::cleanUp();
		return;
		}*/
		evaluateSuchThatNode(such);
		such = such->getRightSibling();
	}
}

void evaluatePattern() {
	QNode* patt = qt->getPattern()->getLeftChild();
	while(patt != NULL) {
		if(!booleanAnswer) return;
		/*if (AbstractWrapper::GlobalStop) {
		// do cleanup 
		PQLParser::cleanUp();
		return;
		}*/

		evaluatePatternNode(patt);

		/*QNode *copy = new QNode();
		QNode *left = patt->getLeftChild();
		QNode *right = patt->getRightChild();
		QNode *var = NULL;

		if(right->getType() == QANY) {
		if(right->getRightSibling() != NULL) {
		var = right->getRightSibling();
		}
		}

		copy->setLeftChild(patt);

		if(mapper.count(patt->getIntVal()) == 0) {
		addAttribute(patt->getIntVal());
		}

		copy->setRightChild(left);
		handleModifies(copy);

		if(right->getType() == QANY) {
		if(right->getRightSibling() == NULL) {
		copy->setLeftChild(NULL);
		copy->setRightChild(NULL);
		delete copy;
		patt = patt->getRightSibling();
		continue;
		}
		}
		QNode *arg;
		if(var != NULL) {
		arg = new QNode(QSTRING);
		if(var->getIntVal() != -1)
		arg->setStrVal(VarTable::getVarTable()->getVarName(var->getIntVal()));
		copy->setRightChild(arg);
		} else {
		copy->setRightChild(right);
		}
		handleUses(copy);

		/*
		if(patt->getRightChild()->getType() == QANY) {
		if(patt->getRightChild()->getLeftChild() == NULL) {
		copy->setRightChild(patt->getLeftChild());
		return handleModifies(copy);
		}
		}

		copy->setRightChild(patt->getLeftChild());
		handleModifies(copy);

		copy->setRightChild(patt->getRightChild());
		handleUses(copy);
		*/
		/*
		copy->setLeftChild(NULL);
		copy->setRightChild(NULL);
		delete copy;*/
		patt = patt->getRightSibling();
	}
}

void evaluateSelect(){
	QNode* sel = qt->getResult()->getLeftChild();

	evaluateSelectNode(sel);
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

void handleAffects(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }

	if(leftType == QINT) {
		if(rightType == QINT) {
			if(!(a->isAffects(constLeft,constRight))) clearTable();
		} else if(rightType == QANY) {
			if(a->getAffectedBy(constLeft).size() == 0) clearTable();
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
			if(a->getAffectedByTransitive(constLeft).size() == 0) clearTable();
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
	callst = CallsTable::getCallsTable();

	initTable();

	resultString.clear();
	
	processClauses();
	/*
	evaluateSuchThat();
	evaluatePattern();
	evaluateWith();
	evaluateSelect();
	*/
	/*for(ui i = 0; i < resultString.size(); i++) {
	cout << resultString[i] << " ";
	}
	cout << endl;*/

	PQLParser::cleanUp();
	return resultString;
}