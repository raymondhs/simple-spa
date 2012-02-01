/*
 * Author: Peter
 */
#include "TestCallsTable.h"

#include <iostream>
#include <string>
#include <cppunit/config/SourcePrefix.h>
#include <SPA/PKB/CallsTable.h>

using namespace std;

void TestCallsTable::setUp(){
	call = CallsTable::getCallsTable();
}

void TestCallsTable::tearDown(){
	call->clearTable();
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestCallsTable );

void TestCallsTable::testStmt(){
	cout << "TestCallsTable::testStmt =  ";
	call->insertStmt(3,0);
	call->insertStmt(4,1);
	call->insertStmt(5,2);
	call->insertStmt(6,0);
	call->insertStmt(7,1);
	CPPUNIT_ASSERT(call->stmtCallsProc(3,0));
	CPPUNIT_ASSERT(call->stmtCallsProc(4,1));
	CPPUNIT_ASSERT(call->stmtCallsProc(5,2));
	CPPUNIT_ASSERT(call->stmtCallsProc(6,0));
	CPPUNIT_ASSERT(call->stmtCallsProc(7,1));
	CPPUNIT_ASSERT(call->getProcCalledByStmt(3)==0);
	CPPUNIT_ASSERT(call->getProcCalledByStmt(5)==2);
	CPPUNIT_ASSERT(call->getProcCalledByStmt(6)==0);
	result.clear();
	result.insert(3);
	result.insert(6);
	CPPUNIT_ASSERT(call->getStmtCallsProc(0)==result);
	result.clear();
	result.insert(4);
	result.insert(7);
	CPPUNIT_ASSERT(call->getStmtCallsProc(1)==result);
	result.clear();
	result.insert(5);
	CPPUNIT_ASSERT(call->getStmtCallsProc(2)==result);
	result.clear();
	cout << "SUCCESS!(^o^)/ OK!" << endl;
}

void TestCallsTable::testProc(){
	cout << "TestCallsTable::testProc =  ";
	call->insertProc(0,1);
	call->insertProc(1,2);
	call->insertProc(2,3);
	call->insertProc(0,3);
	CPPUNIT_ASSERT(call->procCallsProc(0,1));
	CPPUNIT_ASSERT(call->procCallsProc(1,2));
	CPPUNIT_ASSERT(call->procCallsProc(2,3));
	CPPUNIT_ASSERT(call->procCallsProc(0,3));
	result.insert(1);
	result.insert(3);
	CPPUNIT_ASSERT(call->getProcCalledByProc(0)==result);
	result.clear();
	result.insert(2);
	CPPUNIT_ASSERT(call->getProcCalledByProc(1)==result);
	result.clear();
	result.insert(3);
	CPPUNIT_ASSERT(call->getProcCalledByProc(2)==result);
	result.clear();
	CPPUNIT_ASSERT(call->getProcCallsProc(0)==result);
	result.insert(0);
	CPPUNIT_ASSERT(call->getProcCallsProc(1)==result);
	result.clear();
	result.insert(0);
	result.insert(2);
	CPPUNIT_ASSERT(call->getProcCallsProc(3)==result);
	result.clear();
	result.insert(1);
	result.insert(2);
	result.insert(3);
	CPPUNIT_ASSERT(call->getProcCalledByProcTransitive(0)==result);
	result.clear();
	result.insert(2);
	result.insert(3);
	CPPUNIT_ASSERT(call->getProcCalledByProcTransitive(1)==result);
	result.clear();
	result.insert(0);
	result.insert(1);
	result.insert(2);
	CPPUNIT_ASSERT(call->getProcCallsProcTransitive(3)==result);
	result.clear();
	cout << "SUCCESS!(^o^)/ OK!" << endl;
}