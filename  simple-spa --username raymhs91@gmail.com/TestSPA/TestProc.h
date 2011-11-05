/*
 * @author: Peter
 */
#ifndef TestProc_h
#define TestProc_h

class ProcTable;
#include <cppunit/extensions/HelperMacros.h>

class TestProc : public CPPUNIT_NS::TestFixture
{ 
CPPUNIT_TEST_SUITE( TestProc ); // Note 3 
CPPUNIT_TEST( testInsertProc );
CPPUNIT_TEST( testGetProcIdx );
CPPUNIT_TEST( testGetProcName );
CPPUNIT_TEST_SUITE_END();
private: 
ProcTable* proc;

public:
void setUp();
void tearDown();

void testInsertProc();
void testGetProcIdx();
void testGetProcName();

};
#endif