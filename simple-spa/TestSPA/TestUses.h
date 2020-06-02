#ifndef TestUses_h
#define TestUses_h

#include <cppunit/extensions/HelperMacros.h>

class UsesTable;
class StmtTable;
class ProcTable;
class VarTable;
class TNode;

class TestUses : public CPPUNIT_NS::TestFixture
{ 

CPPUNIT_TEST_SUITE( TestUses );
CPPUNIT_TEST( testIsUsesStmtUsingParser );
CPPUNIT_TEST( testIsUsesStmtUsingParser2 );
CPPUNIT_TEST( testIsUsesStmtUsingParser3 );
CPPUNIT_TEST( testGetStmtUsesVar );
CPPUNIT_TEST( testGetProcUsesVar );
CPPUNIT_TEST( testGetVarUsedByStmt );
CPPUNIT_TEST( testGetVarUsedByProc );
CPPUNIT_TEST( testIsUsesStmt );

CPPUNIT_TEST( testIsUsesProc );
CPPUNIT_TEST_SUITE_END();
;

private:
VarTable* var;
StmtTable* stmt;
ProcTable* proc;
UsesTable* uses;
TNode* node1;
TNode* node2;
TNode* node3;
TNode* node4;

public:
void setUp();
void tearDown();

void testGetStmtUsesVar();
void testGetProcUsesVar();
void testGetVarUsedByStmt();
void testGetVarUsedByProc();
void testIsUsesStmt();
void testIsUsesStmtUsingParser();
void testIsUsesStmtUsingParser2();
void testIsUsesStmtUsingParser3();
void testIsUsesProc();

};
#endif