#ifndef TestQueryEvaluator_h
#define TestQueryEvaluator_h

#include <cppunit/extensions/HelperMacros.h>

class PKBParser;
class PQLParser;

class TestQueryEvaluator : public CPPUNIT_NS::TestFixture
{
CPPUNIT_TEST_SUITE( TestQueryEvaluator );
CPPUNIT_TEST( testFollows );
CPPUNIT_TEST( testFollowsT );
CPPUNIT_TEST( testParent );
CPPUNIT_TEST( testParentT );
CPPUNIT_TEST( testModifies );
CPPUNIT_TEST( testUses );
CPPUNIT_TEST( testPattern );
CPPUNIT_TEST( testAnd );
CPPUNIT_TEST( testWith );
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
	void testFollows();
	void testFollowsT();
	void testParent();
	void testParentT();
	void testModifies();
	void testUses();
	void testPattern();
	void testAnd();
	void testWith();
};
#endif

