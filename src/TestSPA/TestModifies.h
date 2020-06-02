#ifndef TestModifies_h
#define TestModifies_h

#include <cppunit/extensions/HelperMacros.h>

class ModifiesTable;
class StmtTable;
class ProcTable;
class VarTable;
class TNode;

class TestModifies : public CPPUNIT_NS::TestFixture
{ 
CPPUNIT_TEST_SUITE( TestModifies ); // Note 3 
CPPUNIT_TEST( testGetStmtModifiesVar );
CPPUNIT_TEST( testGetProcModifiesVar );
CPPUNIT_TEST( testGetVarModifiedByStmt );
CPPUNIT_TEST( testGetVarModifiedByProc );
CPPUNIT_TEST( testIsModifiesStmt );
CPPUNIT_TEST( testIsModifiesStmtUsingParser );
CPPUNIT_TEST( testIsModifiesStmtUsingParser2 );
CPPUNIT_TEST( testIsModifiesStmtUsingParser3 );
CPPUNIT_TEST( testIsModifiesProc );
CPPUNIT_TEST_SUITE_END();

private:
ModifiesTable* modifies;
StmtTable* stmtMod;
ProcTable* procMod;
VarTable* varMod;
TNode* node1;
TNode* node2;
TNode* node3;
TNode* node4;


public:
void setUp();
void tearDown();

void testGetStmtModifiesVar();
void testGetProcModifiesVar();
void testGetVarModifiedByStmt();
void testGetVarModifiedByProc();
void testIsModifiesStmt();
void testIsModifiesStmtUsingParser();
void testIsModifiesStmtUsingParser2();
void testIsModifiesStmtUsingParser3();
void testIsModifiesProc();

};
#endif