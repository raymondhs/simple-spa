#include "TestAST.h"

#include <iostream>
#include <string>

#include <cppunit/config/SourcePrefix.h>
#include <SPA/PKB/ModifiesTable.h>
#include <SPA/PKB/VarTable.h>
#include <SPA/PKB/ProcTable.h>
#include <SPA/PKB/AST.h>
#include <SPA/PKB/StmtTable.h>
#include <SPA/PKB/UsesTable.h>
#include <SPA/PKB/PKBParser.h>

using namespace std;

void TestAST::setUp(){
	stmt = StmtTable::getStmtTable();
	ast = AST::getAST();
}

void  TestAST::tearDown(){
	ast->destroy();
	PKBParser::cleanUp();
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( TestAST );


void TestAST::testIsParentUsingParser(){
	cout << "testAST:testIsParentUsingParser = ";
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
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParent(stmt->getStmtNode(2))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParent(stmt->getStmtNode(3))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParent(stmt->getStmtNode(1))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParent(stmt->getStmtNode(4))==false);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestAST::testIsParentTransitiveUsingParser(){
	cout << "testAST:testIsParentTransitiveUsingParser = ";
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
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(2))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(3))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(1))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(4))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(4)->isParentTransitive(stmt->getStmtNode(5))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(4)->isParentTransitive(stmt->getStmtNode(6))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(5))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(6))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(7))==false);
	cout <<"SUCCESS! OK! :)"<<endl;
}

void TestAST::testIsFollowsUsingParser(){
	cout << "testAST:testIsFollowstUsingParser = ";
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
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollows(stmt->getStmtNode(7))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(7)->isFollows(stmt->getStmtNode(8))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(8)->isFollows(stmt->getStmtNode(9))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(9)->isFollows(stmt->getStmtNode(10))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollows(stmt->getStmtNode(2))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollows(stmt->getStmtNode(4))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(4)->isFollows(stmt->getStmtNode(4))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(4)->isFollows(stmt->getStmtNode(5))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollows(stmt->getStmtNode(8))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(2)->isFollows(stmt->getStmtNode(3))==true);
	cout <<"SUCCESS! OK! :)"<<endl;
}



void TestAST::testIsFollowsTransitiveUsingParser(){
	cout << "testAST:testIsFollowsTransitiveUsingParser = ";
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
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollowsTransitive(stmt->getStmtNode(7))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(7)->isFollowsTransitive(stmt->getStmtNode(8))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(8)->isFollowsTransitive(stmt->getStmtNode(9))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(9)->isFollowsTransitive(stmt->getStmtNode(10))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollowsTransitive(stmt->getStmtNode(2))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollowsTransitive(stmt->getStmtNode(4))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(4)->isFollowsTransitive(stmt->getStmtNode(4))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(4)->isFollowsTransitive(stmt->getStmtNode(5))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollowsTransitive(stmt->getStmtNode(8))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollowsTransitive(stmt->getStmtNode(10))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(2)->isFollowsTransitive(stmt->getStmtNode(3))==true);
	cout <<"SUCCESS! OK! :)"<<endl;
}