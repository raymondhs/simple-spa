#ifndef TestQueryEvaluator_h
#define TestQueryEvaluator_h

#include <cppunit/extensions/HelperMacros.h>

class PKBParser;
class PQLParser;

class TestQueryEvaluator : public CPPUNIT_NS::TestFixture
{
CPPUNIT_TEST_SUITE( TestQueryEvaluator );
CPPUNIT_TEST( testBoolFollows );
CPPUNIT_TEST( testFollows );
CPPUNIT_TEST( testBoolFollowsT );
CPPUNIT_TEST( testBoolFollowsTPattern );
CPPUNIT_TEST( testFollowsT );
CPPUNIT_TEST( testBoolParent );
CPPUNIT_TEST( testParent );
CPPUNIT_TEST( testBoolParentT );
CPPUNIT_TEST( testParentT );
CPPUNIT_TEST( testBoolModifies );
CPPUNIT_TEST( testModifies );
CPPUNIT_TEST( testModifiesP );
CPPUNIT_TEST( testBoolUses );
CPPUNIT_TEST( testUses );
CPPUNIT_TEST( testUsesP );
CPPUNIT_TEST( testBoolPattern );
CPPUNIT_TEST( testPattern );
CPPUNIT_TEST( testPatternAssignComplete );
CPPUNIT_TEST( testBoolAnd );
CPPUNIT_TEST( testAnd );
CPPUNIT_TEST( testBoolWith );
CPPUNIT_TEST( testWith );
CPPUNIT_TEST( testCalls );
CPPUNIT_TEST( testCallsT );
CPPUNIT_TEST( testNext );
CPPUNIT_TEST( testNextT );
CPPUNIT_TEST( testAffects );
CPPUNIT_TEST( testAffectsT );
CPPUNIT_TEST( testContains );
CPPUNIT_TEST( testContainsT );
CPPUNIT_TEST( testSibling );
CPPUNIT_TEST_SUITE_END();

private:
	std::string fileName;
	std::string declaration;
	std::string query;
	std::vector<std::string> result;
	std::vector<std::string> ans;

public:
	void setUp();
	void tearDown();
	void testBoolFollows();
	void testFollows();
	void testBoolFollowsT();
	void testBoolFollowsTPattern();
	void testFollowsT();
	void testBoolParent();
	void testParent();
	void testBoolParentT();
	void testParentT();
	void testBoolModifies();
	void testModifies();
	void testModifiesP();
	void testBoolUses();
	void testUses();
	void testUsesP();
	void testBoolPattern();
	void testPattern();
	void testPatternAssignComplete();
	void testBoolAnd();
	void testAnd();
	void testBoolWith();
	void testWith();
	void testCalls();
	void testCallsT();
	void testNext();
	void testNextT();
	void testAffects();
	void testAffectsT();
	void testContains();
	void testContainsT();
	void testSibling();
};
#endif

