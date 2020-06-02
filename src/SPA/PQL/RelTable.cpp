#include "RelTable.h"

using namespace std;

RelTable::RelTable() {}

RelTable* RelTable::getRelTable(){
	static RelTable relTable;
	return &relTable;
}

void RelTable::clearTable() {
	mapper.clear();
}

void RelTable::insertRow(string relName, int arg1, int arg2) {	
	vector<int> newlist;
	newlist.push_back(arg1);
	newlist.push_back(arg2);
	mapper[relName].push_back(newlist);
}

void RelTable::init() {
	mapper.insert(pair<string, vector< vector<int> > >("Parent",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("Parent*",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("Follows",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("Follows*",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("Modifies",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("Uses",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("Calls",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("Calls*",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("Next",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("Next*",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("Affects",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("Affects*",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("AffectsBip",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("AffectsBip*",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("Contains",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("Contains*",vector< vector<int> >()));
	mapper.insert(pair<string, vector< vector<int> > >("Sibling",vector< vector<int> >()));

	int allStmt = QSTMT|QASSIGN|QWHILE|QPROGLINE|QIF|QCALL;
	insertRow("Parent",allStmt,allStmt);
	insertRow("Parent*",allStmt,allStmt);
	insertRow("Follows",allStmt,allStmt);
	insertRow("Follows*",allStmt,allStmt);
	insertRow("Modifies",allStmt,QVAR);
	insertRow("Uses",allStmt,QVAR);
	insertRow("Modifies",QPROC,QVAR);
	insertRow("Uses",QPROC,QVAR);
	insertRow("Calls",QPROC,QPROC);
	insertRow("Calls*",QPROC,QPROC);
	insertRow("Next",QPROGLINE,QPROGLINE);
	insertRow("Next*",QPROGLINE,QPROGLINE);
	insertRow("NextBip",QPROGLINE,QPROGLINE);
	insertRow("NextBip*",QPROGLINE,QPROGLINE);
	insertRow("Affects",allStmt,allStmt);
	insertRow("Affects*",allStmt,allStmt);
	insertRow("AffectsBip",allStmt,allStmt);
	insertRow("AffectsBip*",allStmt,allStmt);
	int allNode = QSTMTLST|QSTMT|QASSIGN|QCALL|QWHILE|QIF|QPLUS|QMINUS|QTIMES|QVAR|QCONST;
	int allStmtNode = QSTMT|QASSIGN|QCALL|QWHILE|QIF;
	int allOpNode = QPLUS|QMINUS|QTIMES;
	insertRow("Contains",QPROC,QSTMTLST|QSTMT);
	insertRow("Contains",QSTMTLST,allStmtNode);
	insertRow("Contains",QSTMT,allNode);
	insertRow("Contains",QASSIGN,allOpNode|QVAR|QCONST);
	insertRow("Contains",QWHILE|QIF,QSTMTLST|QVAR|QSTMT);
	insertRow("Contains",allOpNode,allOpNode|QVAR|QCONST);
	insertRow("Contains*",QPROC,allNode);
	insertRow("Contains*",QSTMTLST,allNode);
	insertRow("Contains*",QSTMT,allNode);
	insertRow("Contains*",QASSIGN,allOpNode|QVAR|QCONST);
	insertRow("Contains*",QWHILE|QIF,allNode);
	insertRow("Contains*",allOpNode,allOpNode|QVAR|QCONST);
	insertRow("Sibling",QPROC,QPROC);
	insertRow("Sibling",QSTMTLST,QSTMTLST|QVAR|QSTMT);
	insertRow("Sibling",allStmtNode,allStmtNode);
	insertRow("Sibling",allOpNode,allOpNode|QVAR|QCONST);
	insertRow("Sibling",QVAR,allOpNode|QVAR|QCONST|QSTMTLST);
	insertRow("Sibling",QCONST,allOpNode|QVAR|QCONST);
}

bool RelTable::validate(std::string relName, int arg1, int arg2) {
	if(mapper.count(relName) == 0) return false;
	vector < vector<int> > list = mapper[relName];
	vector < vector<int> >::iterator it;
	for(it = list.begin(); it < list.end(); it++) {
		if(( ( (*it)[0] & arg1 ) != 0)
		&& ( ( (*it)[1] & arg2 ) != 0)) {
			return true;
		}
	}
	return false;
}