/*
 * Author: Peter
 */
#ifndef TestVar_h
#define TestVar_h
#include <cppunit/extensions/HelperMacros.h>

class VarTable;

class TestVar : public CPPUNIT_NS::TestFixture
{ 
CPPUNIT_TEST_SUITE( TestVar ); // Note 3 
CPPUNIT_TEST( testInsertVar );
CPPUNIT_TEST( testGetVarIdx );
CPPUNIT_TEST( testGetVarName );
CPPUNIT_TEST_SUITE_END();

private:
VarTable* var;
public:
void setUp();
void tearDown();

void testInsertVar();
void testGetVarIdx();
void testGetVarName();

};
#endif