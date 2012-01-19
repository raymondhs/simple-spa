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

void TestAST::testIsParentUsingParser2(){
	cout << "testAST:testIsParentUsingParser2 = ";
	/*
	procedure Second {
		while i {				#1
			x = 2 + x +y +z;	#2
			i = 1 + i;			#3
			while p {			#4
				q=r+s+t;		#5
				t=u+v;			#6
			}
		}
		x = 0;					#7
		i = 5;					#8
		z = z + x + i;			#9
		y = 2 + z;				#10
	}

	procedure Third {
		while i {				#11
			x = 2 + x +y +z;	#12
			i = 1 + i;			#13
			while p {			#14
				if x then {		#15
					if x then {	#16
						a=b+c+d;#17
						e=f+g;}	#18
					else {
						q=r+s+t;#19
					}
					q=r+s+t;	#20
					t=u+v;}		#21
				else {
					q=r+s+t;	#22
				}
			}
		}
		x = 0;					#23
		i = 5;					#24
		z = z + x + i;			#25
		y = 2 + z;				#26
	}
	*/
	PKBParser::parse( "testcases/testPKB3.txt" );
	//proc Second
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParent(stmt->getStmtNode(2))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParent(stmt->getStmtNode(4))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParent(stmt->getStmtNode(1))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParent(stmt->getStmtNode(5))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(4)->isParent(stmt->getStmtNode(6))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(4)->isParent(stmt->getStmtNode(7))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(2)->isParent(stmt->getStmtNode(10))==false);
	//proc Third
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isParent(stmt->getStmtNode(12))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isParent(stmt->getStmtNode(14))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(15)->isParent(stmt->getStmtNode(16))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(15)->isParent(stmt->getStmtNode(21))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(15)->isParent(stmt->getStmtNode(22))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isParent(stmt->getStmtNode(26))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isParent(stmt->getStmtNode(15))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(15)->isParent(stmt->getStmtNode(19))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(14)->isParent(stmt->getStmtNode(17))==false);
	//cross procedure
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParent(stmt->getStmtNode(11))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParent(stmt->getStmtNode(12))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParent(stmt->getStmtNode(14))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParent(stmt->getStmtNode(16))==false);

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

void TestAST::testIsParentTransitiveUsingParser2(){
	cout << "testAST:testIsParentTransitiveUsingParser2 = ";
	/*
	procedure Second {
		while i {				#1
			x = 2 + x +y +z;	#2
			i = 1 + i;			#3
			while p {			#4
				q=r+s+t;		#5
				t=u+v;			#6
			}
		}
		x = 0;					#7
		i = 5;					#8
		z = z + x + i;			#9
		y = 2 + z;				#10
	}

	procedure Third {
		while i {				#11
			x = 2 + x +y +z;	#12
			i = 1 + i;			#13
			while p {			#14
				if x then {		#15
					if x then {	#16
						a=b+c+d;#17
						e=f+g;}	#18
					else {
						q=r+s+t;#19
					}
					q=r+s+t;	#20
					t=u+v;}		#21
				else {
					q=r+s+t;	#22
				}
			}
		}
		x = 0;					#23
		i = 5;					#24
		z = z + x + i;			#25
		y = 2 + z;				#26
	}
	*/
	PKBParser::parse( "testcases/testPKB3.txt" );
	//proc Second
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(2))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(4))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(1))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(5))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(6))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(4)->isParentTransitive(stmt->getStmtNode(5))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(4)->isParentTransitive(stmt->getStmtNode(6))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(7))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(10))==false);
	//proc Third
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isParentTransitive(stmt->getStmtNode(12))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isParentTransitive(stmt->getStmtNode(14))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isParentTransitive(stmt->getStmtNode(15))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isParentTransitive(stmt->getStmtNode(16))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isParentTransitive(stmt->getStmtNode(17))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isParentTransitive(stmt->getStmtNode(19))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(15)->isParentTransitive(stmt->getStmtNode(18))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(15)->isParentTransitive(stmt->getStmtNode(19))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(15)->isParentTransitive(stmt->getStmtNode(22))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(16)->isParentTransitive(stmt->getStmtNode(19))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isParentTransitive(stmt->getStmtNode(23))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isParentTransitive(stmt->getStmtNode(26))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(14)->isParentTransitive(stmt->getStmtNode(26))==false);
	//cross procedure
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(11))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isParentTransitive(stmt->getStmtNode(15))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(3)->isParentTransitive(stmt->getStmtNode(22))==false);

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


void TestAST::testIsFollowsUsingParser2(){
	cout << "testAST:testIsFollowstUsingParser2 = ";
	/*
	procedure Second {
		while i {				#1
			x = 2 + x +y +z;	#2
			i = 1 + i;			#3
			while p {			#4
				q=r+s+t;		#5
				t=u+v;			#6
			}
		}
		x = 0;					#7
		i = 5;					#8
		z = z + x + i;			#9
		y = 2 + z;				#10
	}

	procedure Third {
		while i {				#11
			x = 2 + x +y +z;	#12
			i = 1 + i;			#13
			while p {			#14
				if x then {		#15
					if x then {	#16
						a=b+c+d;#17
						e=f+g;}	#18
					else {
						q=r+s+t;#19
					}
					q=r+s+t;	#20
					t=u+v;}		#21
				else {
					q=r+s+t;	#22
				}
			}
		}
		x = 0;					#23
		i = 5;					#24
		z = z + x + i;			#25
		y = 2 + z;				#26
	}
	*/
	PKBParser::parse( "testcases/testPKB3.txt" );
	//proc Second
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollows(stmt->getStmtNode(7))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(9)->isFollows(stmt->getStmtNode(10))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(2)->isFollows(stmt->getStmtNode(3))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(5)->isFollows(stmt->getStmtNode(6))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(10)->isFollows(stmt->getStmtNode(11))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollows(stmt->getStmtNode(10))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(4)->isFollows(stmt->getStmtNode(5))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollows(stmt->getStmtNode(2))==false);
	//proc Third
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isFollows(stmt->getStmtNode(12))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isFollows(stmt->getStmtNode(23))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(25)->isFollows(stmt->getStmtNode(26))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(12)->isFollows(stmt->getStmtNode(13))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(13)->isFollows(stmt->getStmtNode(14))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(14)->isFollows(stmt->getStmtNode(15))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(15)->isFollows(stmt->getStmtNode(16))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(16)->isFollows(stmt->getStmtNode(17))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(16)->isFollows(stmt->getStmtNode(20))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(16)->isFollows(stmt->getStmtNode(21))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(16)->isFollows(stmt->getStmtNode(22))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(17)->isFollows(stmt->getStmtNode(18))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(18)->isFollows(stmt->getStmtNode(19))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(20)->isFollows(stmt->getStmtNode(21))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(25)->isFollows(stmt->getStmtNode(26))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(21)->isFollows(stmt->getStmtNode(22))==false);
	//cross proc
	CPPUNIT_ASSERT (stmt->getStmtNode(10)->isFollows(stmt->getStmtNode(11))==false);
	
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

void TestAST::testIsFollowsTransitiveUsingParser2(){
	cout << "testAST:testIsFollowsTransitiveUsingParser2 = ";
	/*
	procedure Second {
		while i {				#1
			x = 2 + x +y +z;	#2
			i = 1 + i;			#3
			while p {			#4
				q=r+s+t;		#5
				t=u+v;			#6
			}
		}
		x = 0;					#7
		i = 5;					#8
		z = z + x + i;			#9
		y = 2 + z;				#10
	}

	procedure Third {
		while i {				#11
			x = 2 + x +y +z;	#12
			i = 1 + i;			#13
			while p {			#14
				if x then {		#15
					if x then {	#16
						a=b+c+d;#17
						e=f+g;}	#18
					else {
						q=r+s+t;#19
					}
					q=r+s+t;	#20
					t=u+v;}		#21
				else {
					q=r+s+t;	#22
				}
			}
		}
		x = 0;					#23
		i = 5;					#24
		z = z + x + i;			#25
		y = 2 + z;				#26
	}
*/
	PKBParser::parse( "testcases/testPKB3.txt" );
	//proc Second
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollowsTransitive(stmt->getStmtNode(7))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollowsTransitive(stmt->getStmtNode(10))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(2)->isFollowsTransitive(stmt->getStmtNode(3))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(2)->isFollowsTransitive(stmt->getStmtNode(4))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(1)->isFollowsTransitive(stmt->getStmtNode(2))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(5)->isFollowsTransitive(stmt->getStmtNode(6))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(6)->isFollowsTransitive(stmt->getStmtNode(7))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(7)->isFollowsTransitive(stmt->getStmtNode(10))==true);
	//proc Third
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isFollowsTransitive(stmt->getStmtNode(23))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isFollowsTransitive(stmt->getStmtNode(26))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(24)->isFollowsTransitive(stmt->getStmtNode(25))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(17)->isFollowsTransitive(stmt->getStmtNode(18))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(20)->isFollowsTransitive(stmt->getStmtNode(21))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(12)->isFollowsTransitive(stmt->getStmtNode(14))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(13)->isFollowsTransitive(stmt->getStmtNode(14))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(16)->isFollowsTransitive(stmt->getStmtNode(20))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(16)->isFollowsTransitive(stmt->getStmtNode(21))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(20)->isFollowsTransitive(stmt->getStmtNode(21))==true);
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isFollowsTransitive(stmt->getStmtNode(12))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(11)->isFollowsTransitive(stmt->getStmtNode(15))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(16)->isFollowsTransitive(stmt->getStmtNode(22))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(22)->isFollowsTransitive(stmt->getStmtNode(23))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(21)->isFollowsTransitive(stmt->getStmtNode(22))==false);
	//cross proc
	CPPUNIT_ASSERT (stmt->getStmtNode(10)->isFollowsTransitive(stmt->getStmtNode(11))==false);
	CPPUNIT_ASSERT (stmt->getStmtNode(10)->isFollowsTransitive(stmt->getStmtNode(26))==false);
	cout <<"SUCCESS! OK! :)"<<endl;
}