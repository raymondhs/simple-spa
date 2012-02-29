#include "TestModifies.h"

#include <iostream>
#include <string>
#include <set>

using namespace std;

#include <cppunit/config/SourcePrefix.h>
#include <SPA/PKB/UsesTable.h>
#include <SPA/PKB/ModifiesTable.h>
#include <SPA/PKB/VarTable.h>
#include <SPA/PKB/ProcTable.h>
#include <SPA/PKB/StmtTable.h>
#include <SPA/PKB/TNode.h>
#include <SPA/PKB/PKBParser.h>

void TestModifies::setUp(){
	modifies = ModifiesTable::getModifiesTable();
	stmtMod = StmtTable::getStmtTable();
	varMod = VarTable::getVarTable();
	procMod = ProcTable::getProcTable();
	node1 = new TNode();
	node2 = new TNode();
	node3 = new TNode();
	node4 = new TNode();
}

void TestModifies::tearDown(){
	PKBParser::cleanUp();
	delete node1;
	delete node2;
	delete node3;
	delete node4;
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestModifies );

void TestModifies::testGetStmtModifiesVar(){
	cout << "testModifies:testGetStmtModifiesVar =  ";
	//STMT_SET ModifiesTable::getStmtModifiesVar(VAR_IDX var)
	varMod->insertVar("a");
	varMod->insertVar("b");
	varMod->insertVar("hahaha");
	varMod->insertVar("c");
	stmtMod->insertStmt(node1);
	stmtMod->insertStmt(node2);
	stmtMod->insertStmt(node3);
	stmtMod->insertStmt(node4);
	modifies->insertStmt(1,1);
	modifies->insertStmt(2,1);
	modifies->insertStmt(3,2);
	set<int> stmtSet0;
	set<int> stmtSet1;
	set<int> stmtSet2;
    stmtSet1.insert(1);
	stmtSet1.insert(2);
	stmtSet2.insert(3);
	CPPUNIT_ASSERT(modifies->getStmtModifiesVar(0)==stmtSet0);
	CPPUNIT_ASSERT(modifies->getStmtModifiesVar(1)==stmtSet1);
	CPPUNIT_ASSERT(modifies->getStmtModifiesVar(2)==stmtSet2);
	CPPUNIT_ASSERT(modifies->getStmtModifiesVar(3)==stmtSet0);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestModifies::testGetProcModifiesVar(){
	cout << "testModifies:testGetProcModifiesVar =  ";
	//PROC_SET ModifiesTable::getProcModifiesVar(VAR_IDX var)
	varMod->insertVar("a");
	varMod->insertVar("b");
	varMod->insertVar("hahaha");
	varMod->insertVar("c");
	procMod->insertProc("proc1");
	procMod->insertProc("proc2");
	procMod->insertProc("proc3");
	procMod->insertProc("proc4");
	modifies->insertProc(1,1);
	modifies->insertProc(2,1);
	modifies->insertProc(3,2);
	modifies->insertProc(2,2);
	modifies->insertProc(2,3);
	set<int> procSet0;
	set<int> procSet1;
	set<int> procSet2;
	set<int> procSet3;
    procSet1.insert(1);
	procSet1.insert(2);
	procSet2.insert(3);
	procSet2.insert(2);
	procSet3.insert(2);
	CPPUNIT_ASSERT(modifies->getProcModifiesVar(0)==procSet0);
	CPPUNIT_ASSERT(modifies->getProcModifiesVar(1)==procSet1);
	CPPUNIT_ASSERT(modifies->getProcModifiesVar(2)==procSet2);
	CPPUNIT_ASSERT(modifies->getProcModifiesVar(3)==procSet3);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestModifies::testGetVarModifiedByStmt(){
	cout << "testModifies:testGetVarModifiesByStmt =  ";
	//VAR_SET ModifiesTable::getVarModifiedByStmt(STMT_NO stmt)
	varMod->insertVar("a");
	varMod->insertVar("b");
	varMod->insertVar("hahaha");
	varMod->insertVar("c");
	stmtMod->insertStmt(node1);
	stmtMod->insertStmt(node2);
	stmtMod->insertStmt(node3);
	modifies->insertStmt(1,0);
	modifies->insertStmt(1,1);
	modifies->insertStmt(2,1);
	modifies->insertStmt(2,2);
	modifies->insertStmt(3,2);
	set<int> varStmtSet1;
	set<int> varStmtSet2;
	set<int> varStmtSet3;
	varStmtSet1.insert(0);
	varStmtSet1.insert(1);
	varStmtSet2.insert(1);
	varStmtSet2.insert(2);
	varStmtSet3.insert(2);
	CPPUNIT_ASSERT(modifies->getVarModifiedByStmt(1)==varStmtSet1);
	CPPUNIT_ASSERT(modifies->getVarModifiedByStmt(2)==varStmtSet2);
	CPPUNIT_ASSERT(modifies->getVarModifiedByStmt(3)==varStmtSet3);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestModifies::testGetVarModifiedByProc(){
	cout << "testModifies:testGetVarModifiesByProc =  ";
	//VAR_SET ModifiesTable::getVarModifiedByProc(PROC_IDX proc)
	varMod->insertVar("a");
	varMod->insertVar("b");
	varMod->insertVar("hahaha");
	varMod->insertVar("c");
	procMod->insertProc("proc1");
	procMod->insertProc("proc2");
	procMod->insertProc("proc3");
	procMod->insertProc("proc4");
	modifies->insertProc(1,1);
	modifies->insertProc(2,1);
	modifies->insertProc(3,2);
	modifies->insertProc(2,2);
	modifies->insertProc(2,3);
	set<int> varSet0;
	set<int> varSet1;
	set<int> varSet2;
	set<int> varSet3;
    varSet1.insert(1);
	varSet2.insert(1);
	varSet2.insert(2);
	varSet2.insert(3);
	varSet3.insert(2);
	CPPUNIT_ASSERT(modifies->getVarModifiedByProc(0)==varSet0);
	CPPUNIT_ASSERT(modifies->getVarModifiedByProc(1)==varSet1);
	CPPUNIT_ASSERT(modifies->getVarModifiedByProc(2)==varSet2);
	CPPUNIT_ASSERT(modifies->getVarModifiedByProc(3)==varSet3);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestModifies::testIsModifiesStmt(){
	cout << "testModifies:testIsModifiesStmt =  ";
	//bool ModifiesTable::isModifiesStmt(STMT_NO stmt, VAR_IDX var)
	varMod->insertVar("a");
	varMod->insertVar("b");
	varMod->insertVar("hahaha");
	varMod->insertVar("c");
	stmtMod->insertStmt(node1);
	stmtMod->insertStmt(node2);
	stmtMod->insertStmt(node3);
	stmtMod->insertStmt(node4);
	modifies->insertStmt(1,1);
	modifies->insertStmt(2,1);
	modifies->insertStmt(3,2);
	CPPUNIT_ASSERT(modifies->isModifiesStmt(1,1)==true);
	CPPUNIT_ASSERT(modifies->isModifiesStmt(1,2)==false);
	CPPUNIT_ASSERT(modifies->isModifiesStmt(2,1)==true);
	CPPUNIT_ASSERT(modifies->isModifiesStmt(3,3)==false);
	CPPUNIT_ASSERT(modifies->isModifiesStmt(3,2)==true);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestModifies::testIsModifiesProc(){
	cout << "testModifies:testIsModifiesProc =  ";
	//bool ModifiesTable::isModifiesProc(PROC_IDX proc, VAR_IDX var)
	varMod->insertVar("a");
	varMod->insertVar("b");
	varMod->insertVar("hahaha");
	varMod->insertVar("c");
	procMod->insertProc("proc1");
	procMod->insertProc("proc2");
	procMod->insertProc("proc3");
	procMod->insertProc("proc4");
	modifies->insertProc(1,1);
	modifies->insertProc(2,1);
	modifies->insertProc(3,2);
	modifies->insertProc(2,2);
	modifies->insertProc(2,3);
	CPPUNIT_ASSERT(modifies->isModifiesProc(1,1)==true);
	CPPUNIT_ASSERT(modifies->isModifiesProc(1,2)==false);
	CPPUNIT_ASSERT(modifies->isModifiesProc(2,1)==true);
	CPPUNIT_ASSERT(modifies->isModifiesProc(3,3)==false);
	CPPUNIT_ASSERT(modifies->isModifiesProc(3,2)==true);
	CPPUNIT_ASSERT(modifies->isModifiesProc(2,2)==true);
	CPPUNIT_ASSERT(modifies->isModifiesProc(2,3)==true);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestModifies::testIsModifiesStmtUsingParser(){
	cout << "testModifies:testIsModifiesStmtUsingParser =  ";
	/*

	procedure Second {

	while i { //1
	x = 2 + x+y+z; //2
	i = 1 + i; }//3
	x = 0;//4
	i = 5; //5
	z = z + x + i; //6
	y = 2 + z;//7
	}

	*/
	PKBParser::parse( "testcases/testPKB1.txt" );
	CPPUNIT_ASSERT (modifies->isModifiesStmt(1,varMod-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(1,varMod-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(2,varMod-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(3,varMod-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(4,varMod-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(5,varMod-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(6,varMod-> getVarIndex("z"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(7,varMod-> getVarIndex("y"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(1,varMod-> getVarIndex("y"))==false);
	cout <<"SUCCESS! OK! :)"<<endl;
	//PKBParser::cleanUp();
}

void TestModifies::testIsModifiesStmtUsingParser2(){
	cout << "testModifies:testIsModifiesStmtUsingParser2 =  ";
	/*
	procedure Second {
	while i {			//1
	x = 2 + x +y +z;	//2
	i = 1 + i;			//3
		while p {		//4
			q=r+s+t;	//5
			t=u+v;		//6
		}
	}
	x = 0;				//7
	i = 5;				//8
	z = z + x + i;		//9
	y = 2 + z;			//10
	}
	*/
	PKBParser::parse( "testcases/testPKB2.txt" );
	CPPUNIT_ASSERT (modifies->isModifiesStmt(1,varMod-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(1,varMod-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(2,varMod-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(3,varMod-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(7,varMod-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(8,varMod-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(9,varMod-> getVarIndex("z"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(10,varMod-> getVarIndex("y"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(1,varMod-> getVarIndex("y"))==false);

	CPPUNIT_ASSERT (modifies->isModifiesStmt(1,varMod-> getVarIndex("q"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(1,varMod-> getVarIndex("t"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(4,varMod-> getVarIndex("q"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(4,varMod-> getVarIndex("t"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(5,varMod-> getVarIndex("q"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(6,varMod-> getVarIndex("t"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(7,varMod-> getVarIndex("q"))==false);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(8,varMod-> getVarIndex("t"))==false);
	//PKBParser::cleanUp();
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestModifies::testIsModifiesStmtUsingParser3(){
	cout << "testModifies:testIsModifiesStmtUsingParser3 =  ";
	PKBParser::parse( "testcases/testPKB3.txt" );
	/*
	procedure Second {

	while i {			//1
	  x = 2 + x +y +z;	//2
	  i = 1 + i;		//3
	   while p {		//4
		q=r+s+t;		//5
		t=u+v;			//6
		}				
	}
	x = 0;				//7
	  i = 5;			//8
	  z = z + x + i;	//9
	  y = 2 + z;		//10
	}

	procedure Third {

	while i {			//11
	  x = 2 + x +y +z;	//12
	  i = 1 + i;		//13
	   while p {		//14
		if x then {		//15
			if x then {	//16
				a=b+c+d;//17
				e=f+g;}	//18
			else {		
				q=r+s+t;//19
			}			
			q=r+s+t;	//20
			t=u+v;}		//21
		else {			
			q=r+s+t;	//22
			}
		}
	}
	x = 0;				//23
	  i = 5;			//24
	  z = z + x + i;	//25
	  y = 2 + z;		//26
	}
	*/
	CPPUNIT_ASSERT (modifies->isModifiesProc(0,varMod-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesProc(0,varMod-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesProc(0,varMod-> getVarIndex("q"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesProc(0,varMod-> getVarIndex("t"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesProc(0,varMod-> getVarIndex("z"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesProc(0,varMod-> getVarIndex("y"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesProc(0,varMod-> getVarIndex("a"))==false);
	CPPUNIT_ASSERT (modifies->isModifiesProc(0,varMod-> getVarIndex("e"))==false);

	CPPUNIT_ASSERT (modifies->isModifiesProc(1,varMod-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesProc(1,varMod-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesProc(1,varMod-> getVarIndex("a"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesProc(1,varMod-> getVarIndex("e"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesProc(1,varMod-> getVarIndex("q"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesProc(1,varMod-> getVarIndex("t"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesProc(1,varMod-> getVarIndex("z"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesProc(1,varMod-> getVarIndex("y"))==true);

	CPPUNIT_ASSERT (modifies->isModifiesStmt(11,varMod-> getVarIndex("q"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(11,varMod-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(11,varMod-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(11,varMod-> getVarIndex("a"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(11,varMod-> getVarIndex("e"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(11,varMod-> getVarIndex("t"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(11,varMod-> getVarIndex("z"))==false);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(11,varMod-> getVarIndex("y"))==false);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(15,varMod-> getVarIndex("a"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(15,varMod-> getVarIndex("e"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(15,varMod-> getVarIndex("q"))==true);
	CPPUNIT_ASSERT (modifies->isModifiesStmt(16,varMod-> getVarIndex("q"))==true);
	//PKBParser::cleanUp();
	cout <<"SUCCESS! OK! :)"<<endl;
}