#include <iostream>
#include <sstream>
#include <map>
#include "QueryEvaluator.h"
#include "QueryTree.h"
#include "../PKB/TNode.h"
#include "../PKB/ModifiesTable.h"
#include "../PKB/UsesTable.h"
#include "../PKB/AST.h"
#include "../PKB/VarTable.h"
#include "../PKB/ProcTable.h"
#include "../PKB/StmtTable.h"
#include "SynTable.h"
#include "../PKB/ConstantTable.h"
#include "PQLParser.h"

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
static ConstantTable *ct;
static vector< vector<int> > table;
static map< int, int > mapper;

static vector< vector<int> > cartesianProduct(vector< vector<int> > table1, vector< vector<int> > table2);
static vector<int> allEntitiesWithType(int type);

static void initTable();
static void addAttribute(int synIdx);
static void clearTable();
static bool isEmptyResult();

static void evaluateSuchThat();
static void evaluatePattern();
static void handleParent(QNode* query);
static void handleParentT(QNode* query);
static void handleFollows(QNode* query);
static void handleFollowsT(QNode* query);
static void handleModifies(QNode* query);
static void handleUses(QNode* query);

static int leftType, rightType;
static int synIdxLeft, synIdxRight;
static int constLeft, constRight;
static int varIdx;
static TNode *stmt1, *stmt2;
static bool valid;

void initVars(QNode* leftArg, QNode* rightArg) {
	valid = true;

	leftType = leftArg->getType();
	rightType = rightArg->getType();

	if(leftType == QSYN) synIdxLeft = leftArg->getIntVal();
	if(leftType == QCONST) {
		constLeft = leftArg->getIntVal();
		stmt1 = st->getStmtNode(constLeft);
		if(stmt1 == NULL) valid = false;
	}

	if(rightType == QSYN) synIdxRight = rightArg->getIntVal();
	if(rightType == QSTRING) {
		varIdx = var->getVarIndex(rightArg->getStrVal());
		if(varIdx == -1) valid = false;
	}
	if(rightType == QCONST) {
		constRight = rightArg->getIntVal();
		stmt2 = st->getStmtNode(constRight);
		if(stmt2 == NULL) valid = false;
	}
}

vector< vector<int> > cartesianProduct(vector< vector<int> > table1, vector< vector<int> > table2) {
	vector< vector<int> > result;
	
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
	
	return result;
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
		case QCONST:
			result = ct->getAllConstant(); break;
		case QPROGLINE:
			result = st->getAllProgline(); break;
		default:
			break;
	}
	return result;
}

void initTable() {
	table.clear();
	mapper.clear();

	QNode* sel = qt->getResult()->getLeftChild();
	int selIdx = sel->getIntVal();
	
	if(mapper.count(selIdx) == 0) {
		addAttribute(selIdx);
	}
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

	vector< vector<int> > newCol;
	newCol.push_back(vector<int>());
	newCol[0].push_back(synIdx);
	for(unsigned i = 0; i < allEnt.size(); i++) {
		newCol[0].push_back(allEnt[i]);
	}

	if(table.size() == 0) {
		table = newCol;
	} else {
		table = cartesianProduct(table,newCol);
	}

	mapper.insert(pair<int,int>(synIdx,mapper.size()));
}

void clearTable() {
	for(ui i = 0; i < table.size(); i++) {
		table[i].erase(table[i].begin()+1,table[i].end());
	}
}

bool isEmptyResult() {
	return table[0].size() <= 1;
}

void deleteRow(int row) {
	for(ui i = 0; i < table.size(); i++) {
		table[i].erase(table[i].begin()+row);
	}
}

void evaluateWith(){
	QNode* with = qt->getWith()->getLeftChild(); // ONLY 1 WITH
	while(with != NULL){
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

		/*TODO
		*/
		if(typeLeft==QVAR){
			if(typeRight==QSTRING){
				int aIdx = mapper[synIdxLeft];
				for(ui i = table[aIdx].size()-1; i >= 1; i--) {
					string name=VarTable::getVarTable()->getVarName(table[aIdx][i]);
					if(name!=rightArg->getStrVal()) deleteRow(i);
				}
			} else if(typeRight==QVAR){
				int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
				for(ui i = table[aIdx1].size()-1; i >= 1; i--) {
					if(table[aIdx1][i]!=table[aIdx2][i]) deleteRow(i);
				}
			} else if(typeRight==QPROC){
				int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
				for(ui i = table[aIdx1].size()-1; i >= 1; i--) {
					string name1=VarTable::getVarTable()->getVarName(table[aIdx1][i]);
					string name2=ProcTable::getProcTable()->getProcName(table[aIdx2][i]);				
					if(name1!=name2) deleteRow(i);
				}
			}
		} else if(typeLeft==QPROC){
			if(typeRight==QSTRING){
				int aIdx = mapper[synIdxLeft];
				for(ui i = table[aIdx].size()-1; i >= 1; i--) {
					string name=ProcTable::getProcTable()->getProcName(table[aIdx][i]);
					if(name!=rightArg->getStrVal()) deleteRow(i);
				}
			} else if(typeRight==QVAR){
				int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
				for(ui i = table[aIdx1].size()-1; i >= 1; i--) {
					string name1=ProcTable::getProcTable()->getProcName(table[aIdx1][i]);
					string name2=VarTable::getVarTable()->getVarName(table[aIdx2][i]);
					if(name1!=name2) deleteRow(i);
				}
			} else if(typeRight==QPROC){
				int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
				for(ui i = table[aIdx1].size()-1; i >= 1; i--) {
					if(table[aIdx1][i]!=table[aIdx2][i]) deleteRow(i);
				}
			}
		} else if(typeLeft==QSTMT){
			if(typeRight==QCONST){
				int aIdx1 = mapper[synIdxLeft];
				for(ui i = table[aIdx1].size()-1; i >= 1; i--) {
					if(table[aIdx1][i]!=rightArg->getIntVal()) deleteRow(i);
				}
			} else if(typeRight==QSTMT){
				int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
				for(ui i = table[aIdx1].size()-1; i >= 1; i--) {
					if(table[aIdx1][i]!=table[aIdx2][i]) deleteRow(i);
				}
			} 
		}
		with = with->getRightSibling();
	}
}

void evaluateSuchThat() {
	QNode* such = qt->getSuchThat()->getLeftChild(); // ONLY 1 SUCH THAT
	while(such != NULL){
		/*if (AbstractWrapper::GlobalStop) {
			// do cleanup 
			PQLParser::cleanUp();
			return;
		}*/
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
			default:
				break;
		}
		such = such->getRightSibling();
	}
}

void evaluatePattern() {
	QNode* patt = qt->getPattern()->getLeftChild(); // ONLY 1 PATTERN
			
	while(patt != NULL) {
		/*if (AbstractWrapper::GlobalStop) {
			// do cleanup 
			PQLParser::cleanUp();
			return;
		}*/
		QNode *copy = new QNode();
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
				return;
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

		copy->setLeftChild(NULL);
		copy->setRightChild(NULL);
		delete copy;
		patt = patt->getRightSibling();
	}
}

void handleParent(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }
	if(leftType == QCONST) {
		if(rightType == QCONST) {
			if(!(stmt1->isParent(stmt2))) clearTable();
		} else if(rightType == QANY) {
			if(stmt1->getParentedBy().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(!(stmt1->isParent(stmtNode))) deleteRow(i);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QCONST) {
			if(stmt2->getParent() == NULL) clearTable();
		} else if(rightType == QANY) {
			if(st->getAllWhile().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(stmtNode->getParent() == NULL) deleteRow(i);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QCONST) {
			int aIdx = mapper[synIdxLeft];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(!(stmtNode->isParent(stmt2))) deleteRow(i);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(stmtNode->getParentedBy().size() == 0) deleteRow(i);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(ui i = table[aIdx1].size()-1; i >= 1; i--) {
				TNode* s1 = st->getStmtNode(table[aIdx1][i]);
				TNode* s2 = st->getStmtNode(table[aIdx2][i]);
				if(!(s1->isParent(s2))) deleteRow(i);
			}
		}
	}
}

void handleParentT(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }
	if(leftType == QCONST) {
		if(rightType == QCONST) {
			if(!(stmt1->isParentTransitive(stmt2))) clearTable();
		} else if(rightType == QANY) {
			if(stmt1->getParentedBy().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(!(stmt1->isParentTransitive(stmtNode))) deleteRow(i);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QCONST) {
			if(stmt2->getParent() == NULL) clearTable();
		} else if(rightType == QANY) {
			if(st->getAllWhile().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(stmtNode->getParent() == NULL) deleteRow(i);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QCONST) {
			int aIdx = mapper[synIdxLeft];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(!(stmtNode->isParentTransitive(stmt2))) deleteRow(i);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(stmtNode->getParentedBy().size() == 0) deleteRow(i);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(ui i = table[aIdx1].size()-1; i >= 1; i--) {
				TNode* s1 = st->getStmtNode(table[aIdx1][i]);
				TNode* s2 = st->getStmtNode(table[aIdx2][i]);
				if(!(s1->isParentTransitive(s2))) deleteRow(i);
			}
		}
	}
}

void handleFollows(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }
	if(leftType == QCONST) {
		if(rightType == QCONST) {
			if(!(stmt1->isFollows(stmt2))) clearTable();
		} else if(rightType == QANY) {
			if(stmt1->getFollows() == NULL) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(!(stmt1->isFollows(stmtNode))) deleteRow(i);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QCONST) {
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
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(stmtNode->getFollowedBy() == NULL) deleteRow(i);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QCONST) {
			int aIdx = mapper[synIdxLeft];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(!(stmtNode->isFollows(stmt2))) deleteRow(i);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(stmtNode->getFollows() == NULL) deleteRow(i);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(ui i = table[aIdx1].size()-1; i >= 1; i--) {
				TNode* s1 = st->getStmtNode(table[aIdx1][i]);
				TNode* s2 = st->getStmtNode(table[aIdx2][i]);
				if(!(s1->isFollows(s2))) deleteRow(i);
			}
		}
	}
}

void handleFollowsT(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }
	if(leftType == QCONST) {
		if(rightType == QCONST) {
			if(!(stmt1->isFollowsTransitive(stmt2))) clearTable();
		} else if(rightType == QANY) {
			if(stmt1->getFollows() == NULL) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(!(stmt1->isFollowsTransitive(stmtNode))) deleteRow(i);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QCONST) {
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
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(stmtNode->getFollowedBy() == NULL) deleteRow(i);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QCONST) {
			int aIdx = mapper[synIdxLeft];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(!(stmtNode->isFollowsTransitive(stmt2))) deleteRow(i);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				TNode* stmtNode = st->getStmtNode(table[aIdx][i]);
				if(stmtNode->getFollows() == NULL) deleteRow(i);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(ui i = table[aIdx1].size()-1; i >= 1; i--) {
				TNode* s1 = st->getStmtNode(table[aIdx1][i]);
				TNode* s2 = st->getStmtNode(table[aIdx2][i]);
				if(!(s1->isFollowsTransitive(s2))) deleteRow(i);
			}
		}
	}
}

void handleModifies(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }
	if(leftType == QCONST) {
		if(rightType == QSTRING) {
			if(!(m->isModifiesStmt(constLeft,varIdx))) clearTable();
		} else if(rightType == QANY) {
			if(m->getVarModifiedByStmt(constLeft).size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				if(!(m->isModifiesStmt(constLeft,table[aIdx][i]))) deleteRow(i);
			}
		}
	} else if(leftType == QANY) {
		if(rightType == QSTRING) {
			if(m->getStmtModifiesVar(varIdx).size() == 0) clearTable();
		} else if(rightType == QANY) {
			if(st->getAllAssign().size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				if(m->getStmtModifiesVar(table[aIdx][i]).size() == 0) deleteRow(i);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QSTRING) {
			int aIdx = mapper[synIdxLeft];			
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				if(!(m->isModifiesStmt(table[aIdx][i],varIdx))) deleteRow(i);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				if(m->getVarModifiedByStmt(table[aIdx][i]).size() == 0) deleteRow(i);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(ui i = table[aIdx1].size()-1; i >= 1; i--) {
				if(!(m->isModifiesStmt(table[aIdx1][i],table[aIdx2][i]))) deleteRow(i);
			}
		}
	}
}

void handleUses(QNode* query) {
	initVars(query->getLeftChild(),query->getRightChild());
	if(!valid) { clearTable(); return; }
	if(leftType == QCONST) {
		if(rightType == QSTRING) {
			if(!(u->isUsesStmt(constLeft,varIdx))) clearTable();
		} else if(rightType == QANY) {
			if(u->getVarUsedByStmt(constLeft).size() == 0) clearTable();
		} else if(rightType == QSYN) {
			int aIdx = mapper[synIdxRight];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				if(!(u->isUsesStmt(constLeft,table[aIdx][i]))) deleteRow(i);
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
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				if(u->getStmtUsesVar(table[aIdx][i]).size() == 0) deleteRow(i);
			}
		}
	} else if(leftType == QSYN) {
		if(rightType == QSTRING) {
			int aIdx = mapper[synIdxLeft];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				if(!(u->isUsesStmt(table[aIdx][i],varIdx))) deleteRow(i);
			}
		} else if(rightType == QANY) {
			int aIdx = mapper[synIdxLeft];
			for(ui i = table[aIdx].size()-1; i >= 1; i--) {
				if(u->getVarUsedByStmt(table[aIdx][i]).size() == 0) deleteRow(i);
			}
		} else if(rightType == QSYN) {
			int aIdx1 = mapper[synIdxLeft], aIdx2 = mapper[synIdxRight];
			for(ui i = table[aIdx1].size()-1; i >= 1; i--) {
				if(!(u->isUsesStmt(table[aIdx1][i],table[aIdx2][i]))) deleteRow(i);
			}
		}
	}
}

vector<string> QueryEvaluator::evaluate() {
	qt = QueryTree::getQueryTree();
	syn = SynTable::getSynTable();
	st = StmtTable::getStmtTable();
	m = ModifiesTable::getModifiesTable();
	var = VarTable::getVarTable();
	u = UsesTable::getUsesTable();
	ast = AST::getAST();
	ct = ConstantTable::getConstantTable();

	initTable();
	
	evaluateSuchThat();
	
	evaluatePattern();

	evaluateWith();

	QNode* sel = qt->getResult()->getLeftChild();
	int selIdx = sel->getIntVal();
	int selType = syn->getSyn(selIdx).second;
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
	for(unsigned i = 1; i < table[aSelIdx].size(); i++) {
		unique.insert(table[aSelIdx][i]);
	}

	vector<string> resultString;
	for(set<int>::iterator it = unique.begin(); it != unique.end(); it++) {
		if(selType == QVAR) {
			resultString.push_back(var->getVarName(*it));
		} else {
			stringstream out;
			out << *it;
			resultString.push_back(out.str());
		}
	}
	
	/*for(ui i = 0; i < resultString.size(); i++) {
		cout << resultString[i] << " ";
	}
	cout << endl;*/

	PQLParser::cleanUp();
	return resultString;
}