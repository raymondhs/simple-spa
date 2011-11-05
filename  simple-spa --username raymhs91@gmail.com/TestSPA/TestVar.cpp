/*
 * Author: Peter
 */
#include "TestVar.h"

#include <iostream>
#include <string>
#include <cppunit/config/SourcePrefix.h>
#include <SPA/PKB/VarTable.h>

using namespace std;

void TestVar::setUp(){
	var = VarTable::getVarTable();	
}

void TestVar::tearDown(){
	var->clearTable();
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestVar );

void TestVar::testInsertVar(){
	cout << "testVar:testInsertVar =  ";
	CPPUNIT_ASSERT(var->insertVar("a")==0);
	CPPUNIT_ASSERT(var->insertVar("a")==0);
	CPPUNIT_ASSERT(var->insertVar("b")==1);
	CPPUNIT_ASSERT(var->insertVar("a")==0);
	CPPUNIT_ASSERT(var->insertVar("c")==2);
	CPPUNIT_ASSERT(var->insertVar("bca")==3);
	CPPUNIT_ASSERT(var->insertVar("b")==1);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestVar::testGetVarIdx(){
	cout << "testVar:testGetVarIdx =  ";
	var->insertVar("a");
	var->insertVar("b");
	var->insertVar("hahaha");
	var->insertVar("c");
	CPPUNIT_ASSERT(var->getVarIndex("a")==0);
	CPPUNIT_ASSERT(var->getVarIndex("b")==1);
	CPPUNIT_ASSERT(var->getVarIndex("hahaha")==2);
	CPPUNIT_ASSERT(var->getVarIndex("c")==3);
	CPPUNIT_ASSERT(var->getVarIndex("d")==-1);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestVar::testGetVarName(){
	cout << "testVar:testGetVarName =  ";
	var->insertVar("a");
	var->insertVar("b");
	var->insertVar("hahaha");
	var->insertVar("c");
	CPPUNIT_ASSERT(var->getVarName(0)=="a");
	CPPUNIT_ASSERT(var->getVarName(1)=="b");
	CPPUNIT_ASSERT(var->getVarName(2)=="hahaha");
	CPPUNIT_ASSERT(var->getVarName(3)=="c");
	cout <<"SUCCESS! OK! :)"<<endl;
}
