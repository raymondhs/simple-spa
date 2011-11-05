#ifndef TestAST_h
#define TestAST_h

#include <cppunit/extensions/HelperMacros.h>

class AST;
class StmtTable;

class TestAST : public CPPUNIT_NS::TestFixture
{ 
CPPUNIT_TEST_SUITE( TestAST ); // Note 3 
CPPUNIT_TEST (testIsParentUsingParser);
CPPUNIT_TEST (testIsParentTransitiveUsingParser);
CPPUNIT_TEST (testIsFollowsUsingParser);
CPPUNIT_TEST (testIsFollowsTransitiveUsingParser);
CPPUNIT_TEST_SUITE_END();

private:
AST* ast;
StmtTable* stmt;

public:
void setUp();
void tearDown();
void testIsParentUsingParser();
void testIsParentTransitiveUsingParser();
void testIsFollowsUsingParser();
void testIsFollowsTransitiveUsingParser();
};
#endif