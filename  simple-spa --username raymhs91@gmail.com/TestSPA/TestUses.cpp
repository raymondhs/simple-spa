#include "TestUses.h"

#include <iostream>
#include <string>
#include <set>

using namespace std;

#include <cppunit/config/SourcePrefix.h>
#include <SPA/PKB/ModifiesTable.h>
#include <SPA/PKB/VarTable.h>
#include <SPA/PKB/StmtTable.h>
#include <SPA/PKB/ProcTable.h>
#include <SPA/PKB/UsesTable.h>
#include <SPA/PKB/TNode.h>
#include <SPA/PKB/PKBParser.h>

void TestUses::setUp(){
	var = VarTable::getVarTable();
	stmt = StmtTable::getStmtTable();
	proc = ProcTable::getProcTable();
	uses = UsesTable::getUsesTable();
	node1 = new TNode();
	node2 = new TNode();
	node3 = new TNode();
	node4 = new TNode();

}

void TestUses::tearDown(){
	PKBParser::cleanUp();
	delete node1;
	delete node2;
	delete node3;
	delete node4;
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestUses );

void TestUses::testGetStmtUsesVar(){
	cout << "testUses:testGetStmtUsesVar =  ";
	var->insertVar("a");
	var->insertVar("b");
	var->insertVar("hahaha");
	var->insertVar("c");
	stmt->insertStmt(node1);
	stmt->insertStmt(node2);
	stmt->insertStmt(node3);
	stmt->insertStmt(node4);
	uses->insertStmt(1,1);
	uses->insertStmt(3,1);
	uses->insertStmt(4,2);
	uses->insertStmt(2,2);
	uses->insertStmt(3,3);
	set<int> stmtSet0;
	set<int> stmtSet1;
	set<int> stmtSet2;
	set<int> stmtSet3;
	stmtSet1.insert(1);
	stmtSet1.insert(3);
	stmtSet2.insert(2);
	stmtSet2.insert(4);
	stmtSet3.insert(3);
	CPPUNIT_ASSERT(uses->getStmtUsesVar(0)==stmtSet0);
	CPPUNIT_ASSERT(uses->getStmtUsesVar(1)==stmtSet1);
	CPPUNIT_ASSERT(uses->getStmtUsesVar(2)==stmtSet2);
	CPPUNIT_ASSERT(uses->getStmtUsesVar(3)==stmtSet3);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestUses::testGetProcUsesVar(){
	cout << "testUses:testGetProcUsesVar =  ";
	var->insertVar("a");
	var->insertVar("b");
	var->insertVar("hahaha");
	var->insertVar("c");
	proc->insertProc("proc1");
	proc->insertProc("proc2");
	proc->insertProc("proc3");
	proc->insertProc("proc4");
	uses->insertProc(2,1);
	uses->insertProc(3,1);
	uses->insertProc(1,2);
	uses->insertProc(2,2);
	uses->insertProc(0,3);
	set<int> procSet0;
	set<int> procSet1;
	set<int> procSet2;
	set<int> procSet3;
	procSet1.insert(2);
	procSet1.insert(3);
	procSet2.insert(1);
	procSet2.insert(2);
	procSet3.insert(0);
	CPPUNIT_ASSERT(uses->getProcUsesVar(0)==procSet0);
	CPPUNIT_ASSERT(uses->getProcUsesVar(1)==procSet1);
	CPPUNIT_ASSERT(uses->getProcUsesVar(2)==procSet2);
	CPPUNIT_ASSERT(uses->getProcUsesVar(3)==procSet3);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestUses::testGetVarUsedByStmt(){
	cout << "testUses:testGetVarUsedByStmt =  ";
	var->insertVar("a");
	var->insertVar("b");
	var->insertVar("hahaha");
	var->insertVar("c");
	stmt->insertStmt(node1);
	stmt->insertStmt(node2);
	stmt->insertStmt(node3);
	uses->insertStmt(1,0);
	uses->insertStmt(1,1);
	uses->insertStmt(2,1);
	uses->insertStmt(2,2);
	uses->insertStmt(3,2);
	set<int> varStmtSet1;
	set<int> varStmtSet2;
	set<int> varStmtSet3;
	varStmtSet1.insert(0);
	varStmtSet1.insert(1);
	varStmtSet2.insert(1);
	varStmtSet2.insert(2);
	varStmtSet3.insert(2);
	CPPUNIT_ASSERT(uses->getVarUsedByStmt(1)==varStmtSet1);
	CPPUNIT_ASSERT(uses->getVarUsedByStmt(2)==varStmtSet2);
	CPPUNIT_ASSERT(uses->getVarUsedByStmt(3)==varStmtSet3);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestUses::testGetVarUsedByProc(){
	cout << "testUses:testGetVarUsedByProc =  ";
	var->insertVar("a");
	var->insertVar("b");
	var->insertVar("hahaha");
	var->insertVar("c");
	proc->insertProc("proc1");
	proc->insertProc("proc2");
	proc->insertProc("proc3");
	proc->insertProc("proc4");
	uses->insertProc(1,2);
	uses->insertProc(1,3);
	uses->insertProc(2,0);
	uses->insertProc(2,1);
	uses->insertProc(3,2);
	set<int> varProcSet0;
	set<int> varProcSet1;
	set<int> varProcSet2;
	set<int> varProcSet3;
	varProcSet1.insert(2);
	varProcSet1.insert(3);
	varProcSet2.insert(0);
	varProcSet2.insert(1);
	varProcSet3.insert(2);
	CPPUNIT_ASSERT(uses->getVarUsedByProc(0)==varProcSet0);
	CPPUNIT_ASSERT(uses->getVarUsedByProc(1)==varProcSet1);
	CPPUNIT_ASSERT(uses->getVarUsedByProc(2)==varProcSet2);
	CPPUNIT_ASSERT(uses->getVarUsedByProc(3)==varProcSet3);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestUses ::testIsUsesStmt(){
	cout << "testUses:testIsUsesStmt =  ";
	var->insertVar("a");
	var->insertVar("b");
	var->insertVar("hahaha");
	var->insertVar("c");
	stmt->insertStmt(node1);
	stmt->insertStmt(node2);
	stmt->insertStmt(node3);
	stmt->insertStmt(node4);
	uses->insertStmt(1,1);
	uses->insertStmt(3,1);
	uses->insertStmt(4,2);
	uses->insertStmt(2,2);
	uses->insertStmt(3,3);
	CPPUNIT_ASSERT(uses->isUsesStmt(1,1)==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(1,0)==false);
	CPPUNIT_ASSERT(uses->isUsesStmt(3,1)==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(4,2)==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(2,2)==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(3,3)==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(4,0)==false);
	CPPUNIT_ASSERT(uses->isUsesStmt(2,3)==false);
	cout <<"SUCCESS! OK! :)"<<endl;
}
void TestUses::testIsUsesStmtUsingParser(){
	cout << "testUses:testIsUsesStmtUsingParser =  ";
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
	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("y"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("z"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(2,var-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(2,var-> getVarIndex("y"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(2,var-> getVarIndex("z"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(3,var-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(4,var-> getVarIndex("x"))==false);
	CPPUNIT_ASSERT(uses->isUsesStmt(6,var-> getVarIndex("z"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(6,var-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(6,var-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(7,var-> getVarIndex("z"))==true);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestUses::testIsUsesProc(){
	cout << "testUses:testIsUsesProc =  ";
	var->insertVar("a");
	var->insertVar("b");
	var->insertVar("hahaha");
	var->insertVar("c");
	proc->insertProc("proc1");
	proc->insertProc("proc2");
	proc->insertProc("proc3");
	proc->insertProc("proc4");
	uses->insertProc(1,2);
	uses->insertProc(1,3);
	uses->insertProc(2,0);
	uses->insertProc(2,1);
	uses->insertProc(3,2);
	CPPUNIT_ASSERT(uses->isUsesProc(1,2)==true);
	CPPUNIT_ASSERT(uses->isUsesProc(1,3)==true);
	CPPUNIT_ASSERT(uses->isUsesProc(2,0)==true);
	CPPUNIT_ASSERT(uses->isUsesProc(2,1)==true);
	CPPUNIT_ASSERT(uses->isUsesProc(3,2)==true);
	CPPUNIT_ASSERT(uses->isUsesProc(0,2)==false);
	CPPUNIT_ASSERT(uses->isUsesProc(3,1)==false);
	CPPUNIT_ASSERT(uses->isUsesProc(1,1)==false);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestUses::testIsUsesStmtUsingParser2(){
	cout << "testUses:testIsUsesStmtUsingParser2 =  ";
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
	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("p"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("r"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("s"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("t"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("u"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("v"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(4,var-> getVarIndex("p"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(5,var-> getVarIndex("r"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(5,var-> getVarIndex("s"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(5,var-> getVarIndex("t"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(6,var-> getVarIndex("u"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(6,var-> getVarIndex("v"))==true);

	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("y"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("z"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(2,var-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(2,var-> getVarIndex("y"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(2,var-> getVarIndex("z"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(3,var-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(7,var-> getVarIndex("x"))==false);
	CPPUNIT_ASSERT(uses->isUsesStmt(9,var-> getVarIndex("z"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(9,var-> getVarIndex("x"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(9,var-> getVarIndex("i"))==true);
	CPPUNIT_ASSERT(uses->isUsesStmt(10,var-> getVarIndex("z"))==true);
	
	CPPUNIT_ASSERT(uses->isUsesStmt(1,var-> getVarIndex("q"))==false);
	cout <<"SUCCESS! OK! :)"<<endl;
}