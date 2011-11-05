/*
 * @author: Peter
 */
#include "TestProc.h"
#include <string>
#include <cppunit/config/SourcePrefix.h>
#include <SPA/PKB/ProcTable.h>
#include <iostream>

using namespace std;

void TestProc::setUp(){
	proc = ProcTable::getProcTable();	
}

void TestProc::tearDown(){
	proc->clearTable();
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestProc );

void TestProc::testInsertProc(){
	cout << "testProc:testInsertProc =  ";
	CPPUNIT_ASSERT(proc->insertProc("a")==0);
	CPPUNIT_ASSERT(proc->insertProc("a")==0);
	CPPUNIT_ASSERT(proc->insertProc("b")==1);
	CPPUNIT_ASSERT(proc->insertProc("a")==0);
	CPPUNIT_ASSERT(proc->insertProc("c")==2);
	CPPUNIT_ASSERT(proc->insertProc("bca")==3);
	CPPUNIT_ASSERT(proc->insertProc("b")==1);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestProc::testGetProcIdx(){
	cout <<"testProc::testGetProcIdx = ";
	proc->insertProc("a");
	proc->insertProc("b");
	proc->insertProc("hahaha");
	proc->insertProc("c");
	CPPUNIT_ASSERT(proc->getProcIndex("a")==0);
	CPPUNIT_ASSERT(proc->getProcIndex("b")==1);
	CPPUNIT_ASSERT(proc->getProcIndex("hahaha")==2);
	CPPUNIT_ASSERT(proc->getProcIndex("c")==3);
	CPPUNIT_ASSERT(proc->getProcIndex("d")==-1);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestProc::testGetProcName(){
	cout <<"testProc::testGetProcName = ";
	proc->insertProc("a");
	proc->insertProc("b");
	proc->insertProc("hahaha");
	proc->insertProc("c");
	CPPUNIT_ASSERT(proc->getProcName(0)=="a");
	CPPUNIT_ASSERT(proc->getProcName(1)=="b");
	CPPUNIT_ASSERT(proc->getProcName(2)=="hahaha");
	CPPUNIT_ASSERT(proc->getProcName(3)=="c");
	CPPUNIT_ASSERT(proc->getProcName(1)=="b");
	cout <<"SUCCESS! OK! :)"<<endl;
}
