#ifndef TestAST_h
#define TestAST_h

#include <cppunit/extensions/HelperMacros.h>

class AST;
class StmtTable;

class TestAST : public CPPUNIT_NS::TestFixture
{ 
CPPUNIT_TEST_SUITE( TestAST ); // Note 3 
CPPUNIT_TEST (testIsParentUsingParser);
CPPUNIT_TEST (testIsParentUsingParser2);
CPPUNIT_TEST (testIsParentTransitiveUsingParser);
CPPUNIT_TEST (testIsParentTransitiveUsingParser2);
CPPUNIT_TEST (testIsFollowsUsingParser);
CPPUNIT_TEST (testIsFollowsUsingParser2);
CPPUNIT_TEST (testIsFollowsTransitiveUsingParser);
CPPUNIT_TEST (testIsFollowsTransitiveUsingParser2);
CPPUNIT_TEST_SUITE_END();

private:
AST* ast;
StmtTable* stmt;

public:
void setUp();
void tearDown();
void testIsParentUsingParser();
void testIsParentUsingParser2();
void testIsParentTransitiveUsingParser();
void testIsParentTransitiveUsingParser2();
void testIsFollowsUsingParser();
void testIsFollowsUsingParser2();
void testIsFollowsTransitiveUsingParser();
void testIsFollowsTransitiveUsingParser2();
};
#endif

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