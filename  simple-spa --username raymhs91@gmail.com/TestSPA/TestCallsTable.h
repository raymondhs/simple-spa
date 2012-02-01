/*
 * @author: Peter
 */

#ifndef TestCallsTable_h
#define TestCallsTable_h
#include <cppunit/extensions/HelperMacros.h>
class CallsTable;

class TestCallsTable : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestCallsTable );
	CPPUNIT_TEST(testStmt);
	CPPUNIT_TEST(testProc);
	CPPUNIT_TEST_SUITE_END();
private:
	CallsTable* call;
	std::set<int> result;
public:
	void setUp();
	void tearDown();
	void testStmt();
	void testProc();
};
#endif