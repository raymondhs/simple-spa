#include "TestQueryEvaluator.h"

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <SPA/PKB/PKBParser.h>
#include <SPA/PQL/PQLParser.h>
#include <SPA/PQL/QueryTree.h>
#include <SPA/PQL/QueryEvaluator.h>
#include <SPA/PQL/SynTable.h>
#include <SPA/PKB/ModifiesTable.h>
#include <SPA/PKB/VarTable.h>
#include <SPA/PKB/ProcTable.h>
#include <SPA/PKB/StmtTable.h>
#include <SPA/PKB/UsesTable.h>
#include <SPA/PKB/ConstantTable.h>

using namespace std;

void TestQueryEvaluator::setUp() {
	declaration = "procedure p,p1,p2,p3,p4; while w1,w2,w3,w4; assign a,a1,a2,a3,a4; stmt s,s#,s1,s2,s3,s4; variable v1,v2,v3,v4; prog_line n1, n2, n3,n4; constant c1, c2, c3,c4; call ca1,ca2,ca3,ca4; if i1,i2,i3,i4;";
}

void TestQueryEvaluator::tearDown() {
	PKBParser::cleanUp();
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestQueryEvaluator );

void TestQueryEvaluator::testBoolFollows() {
	try {
		PKBParser::parse("testcases/follows_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testBoolFollows: ";

	/* Test BOOL 1 */

	query = declaration + "Select BOOLEAN such that Follows(1, s1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();	

	/* Test BOOL 2 */
	query = declaration + "Select BOOLEAN pattern a1(_,_) such that Follows(1, s1) ";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 3 */

	query = declaration + "Select BOOLEAN such that Follows(1, s1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 4 */

	query = declaration + "Select BOOLEAN such that Follows(s1, 9) pattern a1(\"y\",_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();
	
	/* Test BOOL 5 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_) such that Follows(s1, 11)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();
	
	/* Test BOOL 6 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_) such that Follows(s1, 8)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 7 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_) such that Follows(a1, 8)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 8 */

	query = declaration + "Select BOOLEAN pattern a1(\"i\",_) such that Follows(a1, 8)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 9 */

	query = declaration + "Select BOOLEAN such that Follows(s1, 7) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 10 */

	query = declaration + "Select BOOLEAN such that Follows(a1, 9) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 11 */

	query = declaration + "Select BOOLEAN such that Follows(a1, 9) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 12 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_\"x\"_) such that Follows(s1, 5)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 13 */

	query = declaration + "Select BOOLEAN such that Follows(s1, 11) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 13" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 14 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_\"x\"_) such that Follows(a1, 1)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 14" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 15 */

	query = declaration + "Select BOOLEAN such that Follows(4, s1) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 15" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 16 */

	query = declaration + "Select BOOLEAN such that Follows(4, a1) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 16" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 17 */

	query = declaration + "Select BOOLEAN such that Follows(4, s1) pattern a1(_,_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 17" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 18 */

	query = declaration + "Select BOOLEAN such that Follows(1, 6) pattern a1(\"x\", _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 18" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 19 */

	query = declaration + "Select BOOLEAN such that Follows(1, 6) pattern a1(\"y\", _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 19" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 1 */
	query = declaration + "Select BOOLEAN such that Follows(1, s1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 2 */
	query = declaration + "Select BOOLEAN such that Follows(s1, 5)"; 
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 3 */
	query = declaration + "Select BOOLEAN such that Follows(s1, 11)"; 
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 4 */
	query = declaration + "Select BOOLEAN such that Follows(s1, 10)"; 
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 5 */
	query = declaration + "Select BOOLEAN such that Follows(s1, 1)"; 
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 6 */
	query = declaration + "Select BOOLEAN such that Follows(5, s1)"; 
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 7 */
	query = declaration + "Select BOOLEAN such that Follows(10, s1)"; 
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 8 */
	query = declaration + "Select BOOLEAN such that Follows(11, s1)"; 
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 9 */
	query = declaration + "Select BOOLEAN such that Follows(s1, s1)"; 
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 10 */
	query = declaration + "Select BOOLEAN such that Follows(1, 6)"; 
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 11 */
	query = declaration + "Select BOOLEAN such that Follows(1, 2)"; 
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 12 */
	query = declaration + "Select BOOLEAN such that Follows(10, 11)"; 
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 13 */
	query = declaration + "Select BOOLEAN such that Follows(9, 10)"; 
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 14 */
	query = declaration + "Select BOOLEAN such that Follows(s1, _)"; 
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 15 */
	query = declaration + "Select BOOLEAN such that Follows(_, s1)"; 
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 16 */
	query = declaration + "Select BOOLEAN such that Follows(_, _)"; 
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 17 */

	query = declaration + "Select BOOLEAN such that Follows(1, s1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 18 */

	query = declaration + "Select BOOLEAN pattern a1(_,_) such that Follows(1, s1) ";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 19 */

	query = declaration + "Select BOOLEAN such that Follows(1, s1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 20 */

	query = declaration + "Select BOOLEAN such that Follows(s1, 9) pattern a1(\"z\",_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 21 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_) such that Follows(s1, 11)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 22 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_) such that Follows(s1, 8)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 23 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_) such that Follows(a1, 8)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 24 */

	query = declaration + "Select BOOLEAN pattern a1(\"i\",_) such that Follows(a1, 8)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 25 */

	query = declaration + "Select BOOLEAN such that Follows(s1, 7) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 26 */

	query = declaration + "Select BOOLEAN such that Follows(a1, 9) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 27 */

	query = declaration + "Select BOOLEAN such that Follows(a1, 9) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 28 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_\"x\"_) such that Follows(s1, 5)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 29 */

	query = declaration + "Select BOOLEAN such that Follows(s1, 11) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 30 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_\"x\"_) such that Follows(a1, 1)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 31 */

	query = declaration + "Select BOOLEAN such that Follows(4, s1) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 32 */

	query = declaration + "Select BOOLEAN such that Follows(4, a1) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 33 */

	query = declaration + "Select BOOLEAN such that Follows(4, s1) pattern a1(_,_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 34 */

	query = declaration + "Select BOOLEAN such that Follows(1, 6) pattern a1(\"x\", _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 35 */

	query = declaration + "Select BOOLEAN such that Follows(1, 6) pattern a1(\"y\", _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	cout << "SUCCESS ! testBoolFollows :D" << endl;
}

void TestQueryEvaluator::testFollows() {
	try {
		PKBParser::parse("testcases/follows_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testFollows: ";
	/* Test 1 */
	query = declaration + "Select s1 such that Follows(1, s1)";
	PQLParser::parse(query);
	result.push_back("6");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 2 */
	query = declaration + "Select s1 such that Follows(s1, 5)"; 
	PQLParser::parse(query);
	result.push_back("4");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 3 */
	query = declaration + "Select s1 such that Follows(s1, 11)"; 
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 4 */
	query = declaration + "Select s1 such that Follows(s1, 10)"; 
	PQLParser::parse(query);
	result.push_back("9");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 5 */
	query = declaration + "Select s1 such that Follows(s1, 1)"; 
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 6 */
	query = declaration + "Select s1 such that Follows(5, s1)"; 
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 7 */
	query = declaration + "Select s1 such that Follows(10, s1)"; 
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 8 */
	query = declaration + "Select s1 such that Follows(11, s1)"; 
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 9 */
	query = declaration + "Select s1 such that Follows(s1, s1)"; 
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 10 */
	query = declaration + "Select s1 such that Follows(1, 6)"; 
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 11 */
	query = declaration + "Select s1 such that Follows(1, 2)"; 
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 12 */
	query = declaration + "Select s1 such that Follows(10, 11)"; 
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 13 */
	query = declaration + "Select s1 such that Follows(9, 10)"; 
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 14 */
	query = declaration + "Select s1 such that Follows(s1, _)"; 
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 15 */
	query = declaration + "Select s1 such that Follows(_, s1)"; 
	PQLParser::parse(query);
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 16 */
	query = declaration + "Select s1 such that Follows(_, _)"; 
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;

	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 17 */

	query = declaration + "Select s1 such that Follows(1, s1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("6");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 18 */

	query = declaration + "Select s1 pattern a1(_,_) such that Follows(1, s1) ";
	PQLParser::parse(query);
	result.push_back("6");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 19 */

	query = declaration + "Select a1 such that Follows(1, s1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 20 */

	query = declaration + "Select s1 such that Follows(s1, 9) pattern a1(\"z\",_)";
	PQLParser::parse(query);
	result.push_back("8");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 21 */

	query = declaration + "Select a1 pattern a1(\"x\",_) such that Follows(s1, 11)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 22 */

	query = declaration + "Select a1 pattern a1(\"x\",_) such that Follows(s1, 8)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 23 */

	query = declaration + "Select a1 pattern a1(\"x\",_) such that Follows(a1, 8)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 24 */

	query = declaration + "Select a1 pattern a1(\"i\",_) such that Follows(a1, 8)";
	PQLParser::parse(query);
	result.push_back("7");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 25 */

	query = declaration + "Select s1 such that Follows(s1, 7) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("6");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 26 */

	query = declaration + "Select a1 such that Follows(a1, 9) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("8");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 27 */

	query = declaration + "Select s1 such that Follows(a1, 9) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 28 */

	query = declaration + "Select a1 pattern a1(\"x\",_\"x\"_) such that Follows(s1, 5)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 29 */

	query = declaration + "Select s1 such that Follows(s1, 11) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 30 */

	query = declaration + "Select a1 pattern a1(\"x\",_\"x\"_) such that Follows(a1, 1)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 31 */

	query = declaration + "Select a1 such that Follows(4, s1) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("8");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 32 */

	query = declaration + "Select a1 such that Follows(4, a1) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 33 */

	query = declaration + "Select a1 such that Follows(4, s1) pattern a1(_,_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("8");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 34 */

	query = declaration + "Select s1 such that Follows(1, 6) pattern a1(\"x\", _)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 35 */

	query = declaration + "Select a1 such that Follows(1, 6) pattern a1(\"y\", _)";
	PQLParser::parse(query);
	result.push_back("9");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	cout << "SUCCESS! testFollows :D" <<endl;

}

void TestQueryEvaluator::testBoolFollowsT() {
	try {
		PKBParser::parse("testcases/followsT_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testBoolFollows* = ";

	/* Test BOOL 1 */

	query = declaration + "Select BOOLEAN such that Follows*(1, s1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 2 */

	query = declaration + "Select BOOLEAN such that Follows*(s1, 5)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 3 */

	query = declaration + "Select BOOLEAN such that Follows*(s1, 11)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 4 */

	query = declaration + "Select BOOLEAN such that Follows*(s1, 10)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 5 */

	query = declaration + "Select BOOLEAN such that Follows*(s1, 1)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 6 */

	query = declaration + "Select BOOLEAN such that Follows*(5, s1)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 7 */

	query = declaration + "Select BOOLEAN such that Follows*(10, s1)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 8 */

	query = declaration + "Select BOOLEAN such that Follows*(11, s1)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 9 */

	query = declaration + "Select BOOLEAN such that Follows*(s1, s1)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 10 */

	query = declaration + "Select BOOLEAN such that Follows*(1, 2)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 11 */

	query = declaration + "Select BOOLEAN such that Follows*(1, 6)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 12 */

	query = declaration + "Select BOOLEAN such that Follows*(3, 10)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 13 */

	query = declaration + "Select BOOLEAN such that Follows*(3, 5)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 13" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 14 */

	query = declaration + "Select BOOLEAN such that Follows*(6, 11)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 14" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 15 */

	query = declaration + "Select BOOLEAN such that Follows*(5, 10)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 15" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 16 */

	query = declaration + "Select BOOLEAN such that Follows*(s1, _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 16" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 17 */

	query = declaration + "Select BOOLEAN such that Follows*(_, s1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 17" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 18 */

	query = declaration + "Select BOOLEAN such that Follows(_, _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 18" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	cout << "SUCCESS ! testBoolFollows :D" << endl;
}

void TestQueryEvaluator::testBoolFollowsTPattern() {
	try {
		PKBParser::parse("testcases/follows_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testBoolFollows*Pattern: ";

	/* Test BOOL 1 */

	query = declaration + "Select BOOLEAN such that Follows*(1, s1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 2 */

	query = declaration + "Select BOOLEAN pattern a1(_,_) such that Follows*(1, s1) ";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 3 */

	query = declaration + "Select BOOLEAN such that Follows*(1, s1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 4 */

	query = declaration + "Select BOOLEAN such that Follows*(s1, 9) pattern a1(\"y\",_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 5 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_) such that Follows*(s1, 11)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 6 */

	query = declaration + "Select BOOLEAN such that Follows*(s1, 11) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 7 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_) such that Follows*(s1, 8)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 8 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_) such that Follows*(a1, 8)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 9 */

	query = declaration + "Select BOOLEAN pattern a1(\"i\",_) such that Follows*(a1, 8)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 10 */

	query = declaration + "Select BOOLEAN such that Follows*(s1, 7) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 11 */

	query = declaration + "Select BOOLEAN such that Follows*(a1, 9) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 12 */

	query = declaration + "Select BOOLEAN such that Follows*(a1, 10) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 13 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_\"x\"_) such that Follows*(s1, 5)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 13" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 14 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_\"x\"_) such that Follows*(a1, 1)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 14" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 15 */

	query = declaration + "Select BOOLEAN such that Follows*(4, s1) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 15" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 16 */

	query = declaration + "Select BOOLEAN such that Follows*(2, a1) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 16" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 17 */

	query = declaration + "Select BOOLEAN such that Follows*(4, s1) pattern a1(_,_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 17" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 18 */

	query = declaration + "Select BOOLEAN such that Follows*(1, 6) pattern a1(\"x\", _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 18" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 19 */

	query = declaration + "Select BOOLEAN such that Follows*(1, 10) pattern a1(\"y\", _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 19" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	cout << "SUCCESS ! testFollows*Pattern :D" << endl;
}

void TestQueryEvaluator::testFollowsT() {
	try {
		PKBParser::parse("testcases/followsT_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testFollows* = ";

	/* Test 1*/
	query = declaration + "Select s1 such that Follows*(1, s1)";
	PQLParser::parse(query);
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 2*/

	query = declaration + "Select s1 such that Follows*(s1, 5)";
	PQLParser::parse(query);
	result.push_back("2");
	result.push_back("4");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 3*/

	query = declaration + "Select s1 such that Follows*(s1, 11)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 4*/

	query = declaration + "Select s1 such that Follows*(s1, 10)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 5*/

	query = declaration + "Select s1 such that Follows*(s1, 1)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 6*/

	query = declaration + "Select s1 such that Follows*(5, s1)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 7*/

	query = declaration + "Select s1 such that Follows*(10, s1)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 8*/

	query = declaration + "Select s1 such that Follows*(11, s1)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 9*/

	query = declaration + "Select s1 such that Follows*(s1, s1)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 10*/

	query = declaration + "Select s1 such that Follows*(1, 2)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 11*/

	query = declaration + "Select s1 such that Follows*(1, 6)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 12*/

	query = declaration + "Select s1 such that Follows*(3, 10)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 13*/

	query = declaration + "Select s1 such that Follows*(3, 5)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 14*/

	query = declaration + "Select s1 such that Follows*(6, 11)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 15*/

	query = declaration + "Select s1 such that Follows*(5, 10)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 16*/

	query = declaration + "Select s1 such that Follows*(s1, _)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 17*/

	query = declaration + "Select s1 such that Follows*(_, s1)";
	PQLParser::parse(query);
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 18*/

	query = declaration + "Select s1 such that Follows(_, _)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 19 */

	query = declaration + "Select s1 such that Follows*(1, s1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 20 */

	query = declaration + "Select s1 pattern a1(_,_) such that Follows*(1, s1) ";
	PQLParser::parse(query);
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 21 */

	query = declaration + "Select a1 such that Follows*(1, s1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 22 */

	query = declaration + "Select s1 such that Follows*(s1, 9) pattern a1(\"y\",_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 23 */

	query = declaration + "Select a1 pattern a1(\"x\",_) such that Follows*(s1, 11)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 24 */

	query = declaration + "Select s1 such that Follows*(s1, 11) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 25 */

	query = declaration + "Select a1 pattern a1(\"x\",_) such that Follows*(s1, 8)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 26 */

	query = declaration + "Select a1 pattern a1(\"x\",_) such that Follows*(a1, 8)";
	PQLParser::parse(query);
	result.push_back("6");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 27 */

	query = declaration + "Select a1 pattern a1(\"i\",_) such that Follows*(a1, 8)";
	PQLParser::parse(query);
	result.push_back("7");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 28 */

	query = declaration + "Select s1 such that Follows*(s1, 7) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("6");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 29 */

	query = declaration + "Select a1 such that Follows*(a1, 9) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("8");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 30 */

	query = declaration + "Select s1 such that Follows*(a1, 10) pattern a1(\"z\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 31 */

	query = declaration + "Select a1 pattern a1(\"x\",_\"x\"_) such that Follows*(s1, 5)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 32 */

	query = declaration + "Select a1 pattern a1(\"x\",_\"x\"_) such that Follows*(a1, 1)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 33 */

	query = declaration + "Select a1 such that Follows*(4, s1) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("8");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 34 */

	query = declaration + "Select a1 such that Follows*(2, a1) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 35 */

	query = declaration + "Select a1 such that Follows*(4, s1) pattern a1(_,_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("8");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 36 */

	query = declaration + "Select s1 such that Follows*(1, 6) pattern a1(\"x\", _)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 37 */

	query = declaration + "Select a1 such that Follows*(1, 10) pattern a1(\"y\", _)";
	PQLParser::parse(query);
	result.push_back("9");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();




	cout << "SUCCESS testFollows*! :D" <<endl;
}

void TestQueryEvaluator::testBoolParent(){
	try {
		PKBParser::parse("testcases/parent_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testBoolParent = ";


	// Test 1
	query = declaration + "Select BOOLEAN such that Parent(1, 1)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 2
	query = declaration + "Select BOOLEAN such that Parent(1, 2)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 3
	query = declaration + "Select BOOLEAN such that Parent(1, 12)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 4
	query = declaration + "Select BOOLEAN such that Parent(1, 2)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 5
	query = declaration + "Select BOOLEAN such that Parent(1, n1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 6
	query = declaration + "Select BOOLEAN such that Parent(1, 2)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 7
	query = declaration + "Select BOOLEAN such that Parent(s1,s1)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 8
	query = declaration + "Select BOOLEAN such that Parent(2, 3)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 9
	query = declaration + "Select BOOLEAN such that Parent(10,11)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 10
	query = declaration + "Select BOOLEAN such that Parent(1, w1)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 11
	query = declaration + "Select BOOLEAN such that Parent(w1, 2)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 12
	query = declaration + "Select BOOLEAN such that Parent(w1, w2)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 13
	query = declaration + "Select BOOLEAN such that Parent(w1, w2)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 14
	query = declaration + "Select BOOLEAN such that Parent(a1, a2)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 15
	query = declaration + "Select BOOLEAN such that Parent(a1, a2)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 16
	query = declaration + "Select BOOLEAN such that Parent(_, 2)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 17
	query = declaration + "Select BOOLEAN such that Parent(_, 1)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	// Test 18
	query = declaration + "Select BOOLEAN such that Parent(_, _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 19
	query = declaration + "Select BOOLEAN such that Parent(s1,3)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 20
	query = declaration + "Select BOOLEAN such that Parent(10, s1)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 21*/

	query = declaration + "Select BOOLEAN such that Parent(s1,3) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 22*/

	query = declaration + "Select BOOLEAN such that Parent(s1,3) pattern a1(\"b\",_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 23*/

	query = declaration + "Select BOOLEAN such that Parent(s1,3) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 24*/

	query = declaration + "Select BOOLEAN such that Parent(s1,2) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 25*/

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_) such that Parent(s1,3)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 26*/

	query = declaration + "Select BOOLEAN pattern a1(\"b\",_) such that Parent(s1,3)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 27*/

	query = declaration + "Select BOOLEAN such that Parent(_,_) pattern a1(\"i\",_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 28*/

	query = declaration + "Select BOOLEAN pattern a1(\"i\",_\"x\"_) such that Parent(1,_)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 29*/

	query = declaration + "Select BOOLEAN such that Parent(_,_) pattern a1(\"x\",_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 30*/

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_\"x\"_) such that Parent(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 31*/

	query = declaration + "Select BOOLEAN pattern a1(\"x#3\",_\"x\"_) such that Parent(_,_)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 32*/

	query = declaration + "Select BOOLEAN such that Parent(_,11) pattern a1(\"y\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 33*/

	query = declaration + "Select BOOLEAN pattern a1(\"y\",_\"z\"_) such that Parent(_,11)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 34*/

	query = declaration + "Select BOOLEAN such that Parent(1,5) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 35*/

	query = declaration + "Select BOOLEAN pattern a1(_,_\"z\"_) such that Parent(1,5)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 36*/

	query = declaration + "Select BOOLEAN such that Parent(1,4) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 37*/

	query = declaration + "Select BOOLEAN pattern a1(_,_\"z\"_) such that Parent(1,5)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 38*/

	query = declaration + "Select BOOLEAN pattern a1(_,_\"z\"_) such that Parent(_,3)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 39*/

	query = declaration + "Select BOOLEAN such that Parent(_,3) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 40*/

	query = declaration + "Select BOOLEAN such that Parent(_,3) pattern a2(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 41*/

	query = declaration + "Select BOOLEAN pattern a2(_,_\"z\"_) such that Parent(_,3)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 42*/

	query = declaration + "Select BOOLEAN such that Parent(_,3) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test BOOL 1 */

	query = declaration + "Select BOOLEAN such that Parent(s1,3) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}
	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test BOOL 2 */

	query = declaration + "Select BOOLEAN such that Parent(s1,3) pattern a1(\"b\",_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 3 */

	query = declaration + "Select BOOLEAN such that Parent(s1,3) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test BOOL 4 */

	query = declaration + "Select BOOLEAN such that Parent(s1,2) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test BOOL 5 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_) such that Parent(s1,3)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test BOOL 6 */

	query = declaration + "Select BOOLEAN pattern a1(\"b\",_) such that Parent(s1,3)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 7 */

	query = declaration + "Select BOOLEAN such that Parent(_,_) pattern a1(\"i\",_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 8 */

	query = declaration + "Select BOOLEAN pattern a1(\"i\",_\"x\"_) such that Parent(1,_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 9 */

	query = declaration + "Select BOOLEAN such that Parent(_,_) pattern a1(\"x\",_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 10 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_\"x\"_) such that Parent(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test BOOL 11 */

	query = declaration + "Select BOOLEAN pattern a1(\"x#3\",_\"x\"_) such that Parent(_,_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 12 */

	query = declaration + "Select BOOLEAN such that Parent(_,11) pattern a1(\"y\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 13 */

	query = declaration + "Select BOOLEAN pattern a1(\"y\",_\"z\"_) such that Parent(_,11)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 13" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 14 */

	query = declaration + "Select BOOLEAN such that Parent(1,5) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 14" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 15 */

	query = declaration + "Select BOOLEAN pattern a1(_,_\"z\"_) such that Parent(1,5)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 15" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 16 */

	query = declaration + "Select BOOLEAN such that Parent(1,4) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 16" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 17 */

	query = declaration + "Select BOOLEAN pattern a1(_,_\"z\"_) such that Parent(1,5)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 17" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 18 */

	query = declaration + "Select BOOLEAN pattern a1(_,_\"z\"_) such that Parent(_,3)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 18" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 19 */

	query = declaration + "Select BOOLEAN such that Parent(_,3) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 19" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 20 */

	query = declaration + "Select BOOLEAN such that Parent(_,3) pattern a2(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 20" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 21 */

	query = declaration + "Select BOOLEAN pattern a2(_,_\"z\"_) such that Parent(_,3)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 21" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 22 */

	query = declaration + "Select BOOLEAN such that Parent(_,3) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 22" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();



	cout << "SUCCESS ! testBoolParent :D" << endl;
}

void TestQueryEvaluator::testParent() {
	try {
		PKBParser::parse("testcases/parent_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testParent = ";
	// Test 1
	query = declaration + "Select s1 such that Parent(1, 1)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 2
	query = declaration + "Select s2 such that Parent(1, 2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 3
	query = declaration + "Select s1 such that Parent(1, 12)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 4
	query = declaration + "Select v1 such that Parent(1, 2)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 5
	query = declaration + "Select n1 such that Parent(1, n1)";
	PQLParser::parse(query);
	result.push_back("2");
	result.push_back("4");
	result.push_back("5");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 6
	query = declaration + "Select n1 such that Parent(1, 2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 7
	query = declaration + "Select s1 such that Parent(s1,s1)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 8
	query = declaration + "Select a1 such that Parent(2, 3)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 9
	query = declaration + "Select c1 such that Parent(10,11)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("5");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 10
	query = declaration + "Select w1 such that Parent(1, w1)";
	PQLParser::parse(query);
	result.push_back("2");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 11
	query = declaration + "Select w1 such that Parent(w1, 2)";
	PQLParser::parse(query);
	result.push_back("1");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 12
	query = declaration + "Select w1 such that Parent(w1, w2)";
	PQLParser::parse(query);
	result.push_back("1");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 13
	query = declaration + "Select w2 such that Parent(w1, w2)";
	PQLParser::parse(query);
	result.push_back("2");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 14
	query = declaration + "Select a2 such that Parent(a1, a2)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 15
	query = declaration + "Select a1 such that Parent(a1, a2)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 16
	query = declaration + "Select w2 such that Parent(_, 2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("10");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 17
	query = declaration + "Select w1 such that Parent(_, 1)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	// Test 18
	query = declaration + "Select a1 such that Parent(_, _)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 19
	query = declaration + "Select s1 such that Parent(s1,3)";
	PQLParser::parse(query);
	result.push_back("2");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 20
	query = declaration + "Select s1 such that Parent(10, s1)";
	PQLParser::parse(query);
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 21*/

	query = declaration + "Select s1 such that Parent(s1,3) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("2");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 22*/

	query = declaration + "Select s1 such that Parent(s1,3) pattern a1(\"b\",_)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 23*/

	query = declaration + "Select s1 such that Parent(s1,3) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("2");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 24*/

	query = declaration + "Select s1 such that Parent(s1,2) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("1");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 25*/

	query = declaration + "Select s1 pattern a1(\"x\",_) such that Parent(s1,3)";
	PQLParser::parse(query);
	result.push_back("2");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 26*/

	query = declaration + "Select s1 pattern a1(\"b\",_) such that Parent(s1,3)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 27*/

	query = declaration + "Select a1 such that Parent(_,_) pattern a1(\"i\",_\"x\"_)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 28*/

	query = declaration + "Select a1 pattern a1(\"i\",_\"x\"_) such that Parent(1,_)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 29*/

	query = declaration + "Select a1 such that Parent(_,_) pattern a1(\"x\",_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 30*/

	query = declaration + "Select a1 pattern a1(\"x\",_\"x\"_) such that Parent(_,_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 31*/

	query = declaration + "Select a1 pattern a1(\"x#3\",_\"x\"_) such that Parent(_,_)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 32*/

	query = declaration + "Select v1 such that Parent(_,11) pattern a1(\"y\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 33*/

	query = declaration + "Select v1 pattern a1(\"y\",_\"z\"_) such that Parent(_,11)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 34*/

	query = declaration + "Select w1 such that Parent(1,5) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("10");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 35*/

	query = declaration + "Select w1 pattern a1(_,_\"z\"_) such that Parent(1,5)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("10");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 36*/

	query = declaration + "Select c1 such that Parent(1,4) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("5");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 37*/

	query = declaration + "Select c1 pattern a1(_,_\"z\"_) such that Parent(1,5)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("5");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 38*/

	query = declaration + "Select n1 pattern a1(_,_\"z\"_) such that Parent(_,3)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 39*/

	query = declaration + "Select n1 such that Parent(_,3) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 40*/

	query = declaration + "Select a1 such that Parent(_,3) pattern a2(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 41*/

	query = declaration + "Select a1 pattern a2(_,_\"z\"_) such that Parent(_,3)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 42*/

	query = declaration + "Select a1 such that Parent(_,3) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("8");
	result.push_back("9");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();
	cout << "SUCCESS! testParent :D:D:D:D" <<endl;
}

void TestQueryEvaluator::testBoolParentT() {
	try {
		PKBParser::parse("testcases/parentT_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testBoolParent* = ";


	// Test 1
	query = declaration + "Select BOOLEAN such that Parent*(1, 1)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 2
	query = declaration + "Select BOOLEAN such that Parent*(1, 2)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 3
	query = declaration + "Select BOOLEAN such that Parent*(1, 12)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 4
	query = declaration + "Select BOOLEAN such that Parent*(1, 2)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 5
	query = declaration + "Select BOOLEAN such that Parent*(1, n1)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 6
	query = declaration + "Select BOOLEAN such that Parent*(1, 2)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 7
	query = declaration + "Select BOOLEAN such that Parent*(s1,s1)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 8
	query = declaration + "Select BOOLEAN such that Parent*(2, 3)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 9
	query = declaration + "Select BOOLEAN such that Parent*(10,11)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 10
	query = declaration + "Select BOOLEAN such that Parent*(1, w1)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 11
	query = declaration + "Select BOOLEAN such that Parent*(w1, 2)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 12
	query = declaration + "Select BOOLEAN such that Parent*(w1, w2)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 13
	query = declaration + "Select BOOLEAN such that Parent*(w1, w2)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 14
	query = declaration + "Select BOOLEAN such that Parent*(a1, a2)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 15
	query = declaration + "Select BOOLEAN such that Parent*(a1, a2)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 16
	query = declaration + "Select BOOLEAN such that Parent*(_, 2)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 17
	query = declaration + "Select BOOLEAN such that Parent*(_, 1)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	// Test 18
	query = declaration + "Select BOOLEAN such that Parent*(_, _)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 19
	query = declaration + "Select BOOLEAN such that Parent*(s1,3)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 20
	query = declaration + "Select BOOLEAN such that Parent*(10, s1)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 21*/

	query = declaration + "Select BOOLEAN such that Parent*(s1,3) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 22*/

	query = declaration + "Select BOOLEAN such that Parent*(s1,3) pattern a1(\"b\",_)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 23*/

	query = declaration + "Select BOOLEAN such that Parent*(s1,3) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 24*/

	query = declaration + "Select BOOLEAN such that Parent*(s1,2) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 25*/

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_) such that Parent*(s1,3)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 26*/

	query = declaration + "Select BOOLEAN pattern a1(\"b\",_) such that Parent*(s1,3)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 27*/

	query = declaration + "Select BOOLEAN such that Parent*(_,_) pattern a1(\"i\",_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 28*/

	query = declaration + "Select BOOLEAN pattern a1(\"i\",_\"x\"_) such that Parent*(1,_)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 29*/

	query = declaration + "Select BOOLEAN such that Parent*(_,_) pattern a1(\"x\",_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 30*/

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_\"x\"_) such that Parent*(_,_)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 31*/

	query = declaration + "Select BOOLEAN pattern a1(\"x#3\",_\"x\"_) such that Parent*(_,_)";
	PQLParser::parse(query);
	result.push_back("false");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 32*/

	query = declaration + "Select BOOLEAN such that Parent*(_,11) pattern a1(\"y\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 33*/

	query = declaration + "Select BOOLEAN pattern a1(\"y\",_\"z\"_) such that Parent*(_,11)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 34*/

	query = declaration + "Select BOOLEAN such that Parent*(1,5) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 35*/

	query = declaration + "Select BOOLEAN pattern a1(_,_\"z\"_) such that Parent*(1,5)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 36*/

	query = declaration + "Select BOOLEAN such that Parent*(1,4) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 37*/

	query = declaration + "Select BOOLEAN pattern a1(_,_\"z\"_) such that Parent*(1,5)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 38*/

	query = declaration + "Select BOOLEAN pattern a1(_,_\"z\"_) such that Parent*(_,3)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 39*/

	query = declaration + "Select BOOLEAN such that Parent*(_,3) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 40*/

	query = declaration + "Select BOOLEAN such that Parent*(_,3) pattern a2(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 41*/

	query = declaration + "Select BOOLEAN pattern a2(_,_\"z\"_) such that Parent*(_,3)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 42*/

	query = declaration + "Select BOOLEAN such that Parent*(_,3) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test BOOL 1 */

	query = declaration + "Select BOOLEAN such that Parent*(s1,3) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 2 */

	query = declaration + "Select BOOLEAN such that Parent*(s1,3) pattern a1(\"b\",_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 3 */

	query = declaration + "Select BOOLEAN such that Parent*(s1,3) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 4 */

	query = declaration + "Select BOOLEAN such that Parent*(s1,2) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 5 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_) such that Parent*(s1,3)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 6 */

	query = declaration + "Select BOOLEAN pattern a1(\"b\",_) such that Parent*(s1,3)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 7 */

	query = declaration + "Select BOOLEAN such that Parent*(_,_) pattern a1(\"i\",_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 8 */

	query = declaration + "Select BOOLEAN pattern a1(\"i\",_\"x\"_) such that Parent*(1,_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 9 */

	query = declaration + "Select BOOLEAN such that Parent*(_,_) pattern a1(\"x\",_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 10 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_\"x\"_) such that Parent*(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 11 */

	query = declaration + "Select BOOLEAN pattern a1(\"x#3\",_\"x\"_) such that Parent*(_,_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 12 */

	query = declaration + "Select BOOLEAN such that Parent*(_,11) pattern a1(\"y\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 13 */

	query = declaration + "Select BOOLEAN pattern a1(\"y\",_\"z\"_) such that Parent*(_,11)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 13" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 14 */

	query = declaration + "Select BOOLEAN such that Parent*(1,5) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 14" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 15 */

	query = declaration + "Select BOOLEAN pattern a1(_,_\"z\"_) such that Parent*(1,5)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 15" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 16 */

	query = declaration + "Select BOOLEAN such that Parent*(1,4) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 16" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 17 */

	query = declaration + "Select BOOLEAN pattern a1(_,_\"z\"_) such that Parent*(1,5)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 17" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 18 */

	query = declaration + "Select BOOLEAN pattern a1(_,_\"z\"_) such that Parent*(_,3)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 18" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 19 */

	query = declaration + "Select BOOLEAN such that Parent*(_,3) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 19" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 20 */

	query = declaration + "Select BOOLEAN such that Parent*(_,3) pattern a2(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 20" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 21 */

	query = declaration + "Select BOOLEAN pattern a2(_,_\"z\"_) such that Parent*(_,3)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 21" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 22 */

	query = declaration + "Select BOOLEAN such that Parent*(_,3) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 22" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();



	cout << "SUCCESS ! testBoolParent* :D" << endl;
}

void TestQueryEvaluator::testParentT() {
	try {
		PKBParser::parse("testcases/parentT_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testParent* = ";
	// Test 1
	query = declaration + "Select s1 such that Parent*(1, 1)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 2
	query = declaration + "Select s2 such that Parent*(1, 2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 3
	query = declaration + "Select s1 such that Parent*(1, 12)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 4
	query = declaration + "Select v1 such that Parent*(1, 2)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 5
	query = declaration + "Select n1 such that Parent*(1, n1)";
	PQLParser::parse(query);
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 6
	query = declaration + "Select n1 such that Parent*(1, 2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 7
	query = declaration + "Select s1 such that Parent*(s1,s1)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 8
	query = declaration + "Select a1 such that Parent*(2, 3)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 9
	query = declaration + "Select c1 such that Parent*(10,11)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("5");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 10
	query = declaration + "Select w1 such that Parent*(1, w1)";
	PQLParser::parse(query);
	result.push_back("2");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 11
	query = declaration + "Select w1 such that Parent*(w1, 2)";
	PQLParser::parse(query);
	result.push_back("1");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 12
	query = declaration + "Select w1 such that Parent*(w1, w2)";
	PQLParser::parse(query);
	result.push_back("1");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 13
	query = declaration + "Select w2 such that Parent*(w1, w2)";
	PQLParser::parse(query);
	result.push_back("2");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 14
	query = declaration + "Select a2 such that Parent*(a1, a2)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 15
	query = declaration + "Select a1 such that Parent*(a1, a2)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 16
	query = declaration + "Select w2 such that Parent*(_, 2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("10");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 17
	query = declaration + "Select w1 such that Parent*(_, 1)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	// Test 18
	query = declaration + "Select a1 such that Parent*(_, _)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 19
	query = declaration + "Select s1 such that Parent*(s1,3)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	// Test 20
	query = declaration + "Select s1 such that Parent*(10, s1)";
	PQLParser::parse(query);
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 21*/

	query = declaration + "Select s1 such that Parent*(s1,3) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 22*/

	query = declaration + "Select s1 such that Parent*(s1,3) pattern a1(\"b\",_)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 23*/

	query = declaration + "Select s1 such that Parent*(s1,3) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 24*/

	query = declaration + "Select s1 such that Parent*(s1,2) pattern a1(_,_\"i\"_)";
	PQLParser::parse(query);
	result.push_back("1");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 25*/

	query = declaration + "Select s1 pattern a1(\"x\",_) such that Parent*(s1,3)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 26*/

	query = declaration + "Select s1 pattern a1(\"b\",_) such that Parent*(s1,3)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 27*/

	query = declaration + "Select a1 such that Parent*(_,_) pattern a1(\"i\",_\"x\"_)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 28*/

	query = declaration + "Select a1 pattern a1(\"i\",_\"x\"_) such that Parent*(1,_)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 29*/

	query = declaration + "Select a1 such that Parent*(_,_) pattern a1(\"x\",_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 30*/

	query = declaration + "Select a1 pattern a1(\"x\",_\"x\"_) such that Parent*(_,_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 31*/

	query = declaration + "Select a1 pattern a1(\"x#3\",_\"x\"_) such that Parent*(_,_)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 32*/

	query = declaration + "Select v1 such that Parent*(_,11) pattern a1(\"y\",_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 33*/

	query = declaration + "Select v1 pattern a1(\"y\",_\"z\"_) such that Parent*(_,11)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 34*/

	query = declaration + "Select w1 such that Parent*(1,5) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("10");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 35*/

	query = declaration + "Select w1 pattern a1(_,_\"z\"_) such that Parent*(1,5)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("10");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 36*/

	query = declaration + "Select c1 such that Parent*(1,4) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("5");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 37*/

	query = declaration + "Select c1 pattern a1(_,_\"z\"_) such that Parent*(1,5)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("5");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 38*/

	query = declaration + "Select n1 pattern a1(_,_\"z\"_) such that Parent*(_,3)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 39*/

	query = declaration + "Select n1 such that Parent*(_,3) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 40*/

	query = declaration + "Select a1 such that Parent*(_,3) pattern a2(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 41*/

	query = declaration + "Select a1 pattern a2(_,_\"z\"_) such that Parent*(_,3)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 42*/

	query = declaration + "Select a1 such that Parent*(_,3) pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("8");
	result.push_back("9");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();
	cout << "SUCCESS! testParent* :D:D:D:)" <<endl;
}

void TestQueryEvaluator::testBoolModifies() {
	try {
		PKBParser::parse("testcases/modifies_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testBoolModifies = ";

	/* Test BOOL 1 */

	query = declaration + "Select BOOLEAN";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 2 */

	query = declaration + "Select BOOLEAN such that Modifies(s1,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 3 */

	query = declaration + "Select BOOLEAN such that Modifies(s1,\"x\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 4 */

	query = declaration + "Select BOOLEAN such that Modifies(s1,\"y\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 5 */

	query = declaration + "Select BOOLEAN such that Modifies(s1,\"j\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 6 */

	query = declaration + "Select BOOLEAN such that Modifies(s1,\"p\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 7 */

	query = declaration + "Select BOOLEAN such that Modifies(w1,\"x\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 8 */

	query = declaration + "Select BOOLEAN";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 9 */

	query = declaration + "Select BOOLEAN such that Modifies(s1,v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 10 */

	query = declaration + "Select BOOLEAN such that Modifies(3,v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 11 */

	query = declaration + "Select BOOLEAN such that Modifies(1,v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 12 */

	query = declaration + "Select BOOLEAN such that Modifies(w1,v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 13 */

	query = declaration + "Select BOOLEAN such that Modifies(a1,v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 13" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 14 */

	query = declaration + "Select BOOLEAN";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 14" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 15 */

	query = declaration + "Select BOOLEAN such that Modifies(a1,\"x\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 15" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 16 */

	query = declaration + "Select BOOLEAN such that Modifies(a1,v1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 16" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 17 */

	query = declaration + "Select BOOLEAN such that Modifies(a1,v1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 17" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 18 */

	query = declaration + "Select BOOLEAN such that Modifies(a1,v1) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 18" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 19 */

	query = declaration + "Select BOOLEAN such that Modifies(a1,v1) pattern a1(\"j\",_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 19" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 20 */

	query = declaration + "Select BOOLEAN such that Modifies(a1,v1) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 20" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 21 */

	query = declaration + "Select BOOLEAN such that Modifies(a1,v1) pattern a1(_,_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 21" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 22 */

	query = declaration + "Select BOOLEAN such that Modifies(a1,v1) pattern a1(\"x\",_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 22" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	cout << "SUCCESS ! testBoolModifies :D" << endl;
}

void TestQueryEvaluator::testModifies() {
	try {
		PKBParser::parse("testcases/modifies_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testModifies = ";
	/* Test 1*/

	query = declaration + "Select s1";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 2*/

	query = declaration + "Select s2 such that Modifies(s1,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 3*/

	query = declaration + "Select s1 such that Modifies(s1,\"x\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 4*/

	query = declaration + "Select s1 such that Modifies(s1,\"y\")";
	PQLParser::parse(query);
	result.push_back("9");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 5*/

	query = declaration + "Select s1 such that Modifies(s1,\"j\")";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 6*/

	query = declaration + "Select s1 such that Modifies(s1,\"p\")";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 7*/

	query = declaration + "Select w1 such that Modifies(w1,\"x\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("10");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 8*/

	query = declaration + "Select c1";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("5");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 9*/

	query = declaration + "Select v1 such that Modifies(s1,v1)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 10*/

	query = declaration + "Select v1 such that Modifies(3,v1)";
	PQLParser::parse(query);
	result.push_back("x");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 11*/

	query = declaration + "Select v1 such that Modifies(1,v1)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("x");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 12*/

	query = declaration + "Select v1 such that Modifies(w1,v1)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("x");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 13*/

	query = declaration + "Select v1 such that Modifies(a1,v1)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 14*/

	query = declaration + "Select a1";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 15*/

	query = declaration + "Select a1 such that Modifies(a1,\"x\")";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 16*/

	query = declaration + "Select v1 such that Modifies(a1,v1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 17*/

	query = declaration + "Select v1 such that Modifies(a1,v1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 18*/

	query = declaration + "Select v1 such that Modifies(a1,v1) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("x");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 19*/

	query = declaration + "Select v1 such that Modifies(a1,v1) pattern a1(\"j\",_)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 20*/

	query = declaration + "Select a1 such that Modifies(a1,v1) pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 21*/

	query = declaration + "Select a1 such that Modifies(a1,v1) pattern a1(_,_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("8");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 22*/

	query = declaration + "Select a1 such that Modifies(a1,v1) pattern a1(\"x\",_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();




	cout << "SUCCESS! testModifies :j" <<endl;
}

void TestQueryEvaluator::testModifiesP() {
	try {
		PKBParser::parse("testcases/calls_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testModifiesP = ";
	/* Test 1 */

	query = declaration + "Select p such that Modifies(p, \"k\")";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 2 */

	query = declaration + "Select p such that Modifies(p, \"a\")";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 3 */

	query = declaration + "Select p such that Modifies(p, \"zz\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 4 */

	query = declaration + "Select p such that Modifies(p, _)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 5 */

	query = declaration + "Select p such that Modifies(p, v1) with v1.varName=\"a\"";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 6 */

	query = declaration + "Select p such that Modifies(p, v1) and Modifies(w1, v1)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 7 */

	query = declaration + "Select p such that Modifies(p, v1) and Modifies(i1, v1)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 8 */

	query = declaration + "Select p such that Modifies(p, v1) and Modifies(i1, v1) and  Modifies(w1, v1)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}
	
	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 9 */

	query = declaration + "Select p such that Modifies(p, v1) and Uses(s1, v1) pattern a1(v1, \"1\")";
	PQLParser::parse(query);
	result.push_back("Gamma");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 10 */

	query = declaration + "Select p such that Modifies(p, v1) and Uses(a1, v1) pattern a1(\"a\",_\"b\"_)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 11 */

	query = declaration + "Select p such that Modifies(p, v1) and Uses(a1, v1) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 12 */

	query = declaration + "Select p such that Modifies(p, v1) and Uses(a1, v1) pattern a1(\"zz\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 13 */

	query = declaration + "Select p such that Modifies(p, v1) and Uses(a1, v1) pattern a1(_,\"zz\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 13" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 14 */

	query = declaration + "Select p such that Modifies(p, v1) and Uses(w1, v1)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 14" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 15 */

	query = declaration + "Select p such that Modifies(p, v1) and Uses(w1, v1) with v1.varName=\"x\"";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 15" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 16 */

	query = declaration + "Select p such that Modifies(p, v1) and Uses(w1, v1) with v1.varName=\"x\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 16" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 17 */

	query = declaration + "Select p such that Modifies(p, v1) and Uses(i1, v1)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 17" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 18 */

	query = declaration + "Select p such that Modifies(p, v1) and Uses(i1, v1) with v1.varName=\"i\"";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 18" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 19 */

	query = declaration + "Select p such that Modifies(p, v1) and Uses(i1, v1) with v1.varName=\"j\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 19" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 20 */

	query = declaration + "Select p such that Modifies(p, v1) and Uses(s1, v1) and Uses(w1, v1) and Uses(i1, v1)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 20" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 21 */

	query = declaration + "Select v1 such that Modifies(5, v1)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 21" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 22 */

	query = declaration + "Select v1 such that Modifies(20, v1)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("k");
	result.push_back("l");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 22" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 23 */

	query = declaration + "Select v1 such that Modifies(28, v1)";
	PQLParser::parse(query);
	result.push_back("x");
	result.push_back("i");
	result.push_back("j");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("z");
	result.push_back("y");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 23" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 24 */

	query = declaration + "Select v1 such that Modifies(5, v1) and v1.varName=\"zz\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 24" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 25 */

	query = declaration + "Select v1 such that Modifies(5, v1) and v1.varName=\"a\"";
	PQLParser::parse(query);
	result.push_back("a");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 25" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 26 */

	query = declaration + "Select v1 such that Modifies(28, v1) and Modifies(29, v1) and Modifies(30, v1)";
	PQLParser::parse(query);
	result.push_back("i");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 26" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 27 */

	query = declaration + "Select BOOLEAN such that Modifies(\"Alpha\", \"x\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 27" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 28 */

	query = declaration + "Select BOOLEAN such that Modifies(\"Alpha\", v1) with v1.varName = \"k\"";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 28" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 29 */

	query = declaration + "Select v1 such that Modifies(\"Alpha\", v1)";
	PQLParser::parse(query);
	result.push_back("x");
	result.push_back("i");
	result.push_back("j");
	result.push_back("k");
	result.push_back("l");
	result.push_back("y");
	result.push_back("z");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 29" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 30 */

	query = declaration + "Select BOOLEAN such that Modifies(\"Alpha\", v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 30" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 31 */

	query = declaration + "Select BOOLEAN such that Modifies(\"Caller\", v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 31" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 32 */

	query = declaration + "Select v1 such that Modifies(\"Caller\", v1)";
	PQLParser::parse(query);
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("x");
	result.push_back("y");
	result.push_back("z");
	result.push_back("i");
	result.push_back("j");
	result.push_back("k");
	result.push_back("l");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 32" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 33 */

	query = declaration + "Select BOOLEAN such that Modifies(\"Caller\", _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 33" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 34 */

	query = declaration + "Select BOOLEAN such that Modifies(\"Gamma\", \"a\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 34" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 35 */

	query = declaration + "Select BOOLEAN such that Modifies(\"Gamma\", v1) and Modifies(\"Caller\", \"x\") and Modifies(\"Alpha\", \"a\") with v1.varName=\"j\"";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 35" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();



	cout << "SUCCESS ! testModifiesP." << endl;
}

void TestQueryEvaluator::testBoolUses() {
	try {
		PKBParser::parse("testcases/uses_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testBoolUses = ";
	/* Test BOOL 1 */

	query = declaration + "Select BOOLEAN such that Uses (s1, _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 2 */

	query = declaration + "Select BOOLEAN such that Uses (w1, _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 3 */

	query = declaration + "Select BOOLEAN such that Uses (a1, v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 4 */

	query = declaration + "Select BOOLEAN such that Uses (s1, v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 5 */

	query = declaration + "Select BOOLEAN such that Uses (w1, v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 6 */

	query = declaration + "Select BOOLEAN such that Uses (1, v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 7 */

	query = declaration + "Select BOOLEAN such that Uses (1, v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 8 */

	query = declaration + "Select BOOLEAN such that Uses (2, v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 9 */

	query = declaration + "Select BOOLEAN such that Uses (6, v1)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 10 */

	query = declaration + "Select BOOLEAN such that Uses (s1, \"i\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 11 */

	query = declaration + "Select BOOLEAN such that Uses (w1, \"i\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 12 */

	query = declaration + "Select BOOLEAN such that Uses (n1, \"x\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 13 */

	query = declaration + "Select BOOLEAN such that Uses (s1, \"b\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 13" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 14 */

	query = declaration + "Select BOOLEAN such that Uses (15, v1)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 14" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 15 */

	query = declaration + "Select BOOLEAN such that Uses (s1, \"z\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 15" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 16 */

	query = declaration + "Select BOOLEAN such that Uses (s1, _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 16" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 17 */

	query = declaration + "Select BOOLEAN such that Uses (1, \"x\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 17" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 18 */

	query = declaration + "Select BOOLEAN such that Uses (4, \"x\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 18" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 19 */

	query = declaration + "Select BOOLEAN such that Uses (8, \"j\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 19" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 20 */

	query = declaration + "Select BOOLEAN such that Uses (8, _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 20" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 21 */

	query = declaration + "Select BOOLEAN such that Uses (7, _)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 21" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 22 */

	query = declaration + "Select BOOLEAN pattern a1 (\"y\",_) such that Uses (a1, v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 22" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 23 */

	query = declaration + "Select BOOLEAN pattern a1(_,_\"z\"_) such that Uses (a1, v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 23" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 24 */

	query = declaration + "Select BOOLEAN pattern a1(_,_\"z\"_) such that Uses (15, v1)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 24" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 25 */

	query = declaration + "Select BOOLEAN pattern a1(\"z\",_\"z\"_) such that Uses (1, \"i\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 25" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 26 */

	query = declaration + "Select BOOLEAN pattern a1(_,_\"i\"_) such that Uses (1, \"i\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 26" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 27 */

	query = declaration + "Select BOOLEAN pattern a1(_,_\"i\"_) such that Uses (1, \"y\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 27" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 28 */

	query = declaration + "Select BOOLEAN pattern a1(_,_\"i\"_) such that Uses (1, \"x\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 28" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 29 */

	query = declaration + "Select BOOLEAN pattern a1 (\"y\",_) such that Uses (w1, \"i\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 29" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 30 */

	query = declaration + "Select BOOLEAN pattern a1 (\"n\",_) such that Uses (w1, \"i\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 30" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 31 */

	query = declaration + "Select BOOLEAN pattern a1 (\"x\",_) such that Uses (w1, \"i\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 31" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();



	cout << "SUCCESS ! testBoolUses :D" << endl;
}

void TestQueryEvaluator::testUses() {
	try {
		PKBParser::parse("testcases/uses_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testUses = ";
	/* Test 1 */

	query = declaration + "Select s1 such that Uses (s1, _)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 2 */

	query = declaration + "Select w1 such that Uses (w1, _)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("10");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 3 */

	query = declaration + "Select a1 such that Uses (a1, v1)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 4 */

	query = declaration + "Select s1 such that Uses (s1, v1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 5 */

	query = declaration + "Select c1 such that Uses (w1, v1)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("5");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 6 */
	query = declaration + "Select w1 such that Uses (1, v1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("10");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 7 */

	query = declaration + "Select v1 such that Uses (1, v1)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 8 */

	query = declaration + "Select v1 such that Uses (2, v1)";
	PQLParser::parse(query);
	result.push_back("j");
	result.push_back("x");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 9 */

	query = declaration + "Select v1 such that Uses (6, v1)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 10 */

	query = declaration + "Select s1 such that Uses (s1, \"i\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("5");
	result.push_back("8");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 11 */

	query = declaration + "Select s1 such that Uses (w1, \"i\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 12 */

	query = declaration + "Select n1 such that Uses (n1, \"x\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("8");
	result.push_back("10");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 11 */

	query = declaration + "Select s1 such that Uses (s1, \"b\")";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 12 */

	query = declaration + "Select v1 such that Uses (15, v1)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 13 */

	query = declaration + "Select w1 such that Uses (s1, \"z\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("10");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 14 */

	query = declaration + "Select c1 such that Uses (s1, _)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("5");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 15 */

	query = declaration + "Select v1 such that Uses (1, \"x\")";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 16 */

	query = declaration + "Select c1 such that Uses (4, \"x\")";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("5");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 17 */

	query = declaration + "Select c1 such that Uses (8, \"j\")";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 18 */

	query = declaration + "Select c1 such that Uses (8, _)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("5");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 19 */

	query = declaration + "Select c1 such that Uses (7, _)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 20 */

	query = declaration + "Select a1 pattern a1 (\"y\",_) such that Uses (a1, v1)";
	PQLParser::parse(query);
	result.push_back("9");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 21 */

	query = declaration + "Select a1 pattern a1(_,_\"z\"_) such that Uses (a1, v1)";
	PQLParser::parse(query);
	result.push_back("8");
	result.push_back("9");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 22 */

	query = declaration + "Select a1 pattern a1(_,_\"z\"_) such that Uses (15, v1)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 23 */

	query = declaration + "Select a1 pattern a1(\"z\",_\"z\"_) such that Uses (1, \"i\")";
	PQLParser::parse(query);
	result.push_back("8");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 24 */

	query = declaration + "Select a1 pattern a1(_,_\"i\"_) such that Uses (1, \"i\")";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("8");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 25 */

	query = declaration + "Select a1 pattern a1(_,_\"i\"_) such that Uses (1, \"y\")";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 26 */

	query = declaration + "Select a1 pattern a1(_,_\"i\"_) such that Uses (1, \"x\")";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("8");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 27 */

	query = declaration + "Select w1 pattern a1 (\"y\",_) such that Uses (w1, \"i\")";
	PQLParser::parse(query);
	result.push_back("1");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 28 */

	query = declaration + "Select w1 pattern a1 (\"n\",_) such that Uses (w1, \"i\")";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 29 */

	query = declaration + "Select a1 pattern a1 (\"x\",_) such that Uses (w1, \"i\")";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	cout << "SUCCESS! testUses :P" <<endl;
}

void TestQueryEvaluator::testUsesP() {
	try {
		PKBParser::parse("testcases/calls_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testUses = ";
	/* Test 1 */

	query = declaration + "Select p";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 2 */

	query = declaration + "Select p such that Uses(p, _)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 3 */

	query = declaration + "Select p such that Uses(p, \"x\")";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 4 */

	query = declaration + "Select p such that Uses(p, \"zz\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 5 */

	query = declaration + "Select p such that Uses(p, \"j\")";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 6 */

	query = declaration + "Select v1 such that Uses(p, v1)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");	
	result.push_back("z");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 7 */

	query = declaration + "Select v1 such that Uses(5, v1)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 8 */

	query = declaration + "Select v1 such that Uses(q, v1) and Uses(p, v1)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("k");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 9 */

	query = declaration + "Select v1 such that Uses(p, v1) with v1.varName=\"x\"";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 10 */

	query = declaration + "Select v1 such that Uses(p, v1) with v1.varName=\"xx\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 11 */

	query = declaration + "Select s1 pattern s1(_, _) such that Uses(p, v1) and Uses(s1, v1)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 12 */

	query = declaration + "Select s1 pattern s1(\"x\", _) such that Uses(p, v1) and Uses(s1, v1)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 13 */

	query = declaration + "Select BOOLEAN such that Uses(p, v1) with v1.varName=\"x\"";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 13" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 14 */

	query = declaration + "Select BOOLEAN such that Uses(p, v1) and Uses(s1, v1) pattern s1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 14" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 15 */

	query = declaration + "Select BOOLEAN such that Uses(p, \"j\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 15" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 16 */

	query = declaration + "Select BOOLEAN such that Uses(p, \"zz\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 16" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 17 */

	query = declaration + "Select BOOLEAN such that Uses(20, \"x\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 17" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 18 */

	query = declaration + "Select BOOLEAN such that Uses(20, \"j\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 18" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 19 */

	query = declaration + "Select BOOLEAN such that Uses(28, \"z\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 19" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 20 */

	query = declaration + "Select BOOLEAN such that Uses(5, _)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 20" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();



	cout << " SUCCESS! testUses." << endl;
}

void TestQueryEvaluator::testBoolPattern() {
	try {
		PKBParser::parse("testcases/pattern_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testBoolPattern = ";
	/* Test BOOL 1 */

	query = declaration + "Select BOOLEAN pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 2 */

	query = declaration + "Select BOOLEAN pattern a1(\"i\",_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test BOOL 3 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 4 */

	query = declaration + "Select BOOLEAN pattern a1(_,_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test BOOL 5 */

	query = declaration + "Select BOOLEAN pattern a1(\"x\",_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test BOOL 6 */

	query = declaration + "Select BOOLEAN pattern a1(_,_\"p\"_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test BOOL 7 */

	query = declaration + "Select BOOLEAN pattern a2(_,_\"p\"_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test BOOL 8 */

	query = declaration + "Select BOOLEAN pattern a2(_,_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();



	cout << "SUCCESS ! testPattern :D" << endl;
}

void TestQueryEvaluator::testPattern() {
	try {
		PKBParser::parse("testcases/pattern_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testPattern = ";
	/* Test 1*/

	query = declaration + "Select a1 pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 2*/

	query = declaration + "Select a1 pattern a1(\"i\",_)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("7");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 3*/

	query = declaration + "Select a1 pattern a1(\"x\",_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 4*/

	query = declaration + "Select a1 pattern a1(_,_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("8");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 5*/

	query = declaration + "Select a1 pattern a1(\"x\",_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 6*/

	query = declaration + "Select a1 pattern a1(_,_\"p\"_)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 7*/

	query = declaration + "Select a1 pattern a2(_,_\"p\"_)";
	PQLParser::parse(query);


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 8*/

	query = declaration + "Select a1 pattern a2(_,_\"x\"_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");


	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	cout << "SUCCESS! testPattern :j" <<endl;
}

void TestQueryEvaluator::testBoolAnd() {
	try {
		PKBParser::parse("testcases/and_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testBoolAnd = ";
	/* Test 1 */

	query = declaration + "Select BOOLEAN such that Uses(a1,\"x\") and Modifies(a1,\"z\") and Uses(a1,\"z\") and Follows*(7,a1) pattern a1(\"z\",_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 2 */

	query = declaration + "Select BOOLEAN such that Uses(w1,\"x\") and Uses(w1,\"i\") and Parent(w1,w2)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 3 */

	query = declaration + "Select BOOLEAN such that Uses(w1,\"x\") and Uses(w1,\"i\") and Parent(w1,w2) and Modifies(w1,\"j\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 4 */

	query = declaration + "Select BOOLEAN such that Uses(w1,\"x\") and Modifies(w1,\"x\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 5 */

	query = declaration + "Select BOOLEAN such that Uses(w1,\"x\") and Modifies(w1,\"x\") and Uses(w1,\"i\") and Modifies(w1,\"i\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 6 */

	query = declaration + "Select BOOLEAN such that Modifies(a1,\"y\") and Uses(a1,\"x\") pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 7 */

	query = declaration + "Select BOOLEAN such that Parent(32,33) and Uses(23,\"varA\") and Modifies(28,\"varD\") pattern a1(_,_\"varA\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 8 */

	query = declaration + "Select BOOLEAN such that Parent*(w1,43) and Modifies(w1,\"varLoop10\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 9 */

	query = declaration + "Select BOOLEAN such that Parent*(w1,43) and Modifies(w1,\"varLoop10\") and Follows*(w1,46) pattern a2(_,_\"varLoop1\"_) pattern a1(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 10 */

	query = declaration + "Select BOOLEAN such that Parent*(w1,43) pattern a1(_,_) such that Modifies(w1,\"varLoop10\") and Follows*(w1,57) pattern a2(_,_\"varLoop1\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 11 */

	query = declaration + "Select BOOLEAN such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 12 */
	query = declaration + "Select BOOLEAN such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();



	cout << "SUCCESS ! testBoolAnd :D" << endl;
}

void TestQueryEvaluator::testAnd(){
	try {
		PKBParser::parse("testcases/and_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	cout << "testAnd = ";
	/* Test 1 */

	query = declaration + "Select a1 such that Uses(a1,\"x\") and Modifies(a1,\"z\") and Uses(a1,\"z\") and Follows*(7,a1) pattern a1(\"z\",_)";
	PQLParser::parse(query);
	result.push_back("8");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 2 */

	query = declaration + "Select w1 such that Uses(w1,\"x\") and Uses(w1,\"i\") and Parent(w1,w2)";
	PQLParser::parse(query);
	result.push_back("1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 3 */

	query = declaration + "Select w1 such that Uses(w1,\"x\") and Uses(w1,\"i\") and Parent(w1,w2) and Modifies(w1,\"j\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 4 */

	query = declaration + "Select w1 such that Uses(w1,\"x\") and Modifies(w1,\"x\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 5 */

	query = declaration + "Select w1 such that Uses(w1,\"x\") and Modifies(w1,\"x\") and Uses(w1,\"i\") and Modifies(w1,\"i\")";
	PQLParser::parse(query);
	result.push_back("1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 6 */

	query = declaration + "Select a1 such that Modifies(a1,\"y\") and Uses(a1,\"x\") pattern a1(_,_\"z\"_)";
	PQLParser::parse(query);
	result.push_back("18");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 7 */

	query = declaration + "Select n1 such that Parent(32,33) and Uses(23,\"varA\") and Modifies(28,\"varD\") pattern a1(_,_\"varA\"_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");
	result.push_back("32");
	result.push_back("33");
	result.push_back("34");
	result.push_back("35");
	result.push_back("36");
	result.push_back("37");
	result.push_back("38");
	result.push_back("39");
	result.push_back("40");
	result.push_back("41");
	result.push_back("42");
	result.push_back("43");
	result.push_back("44");
	result.push_back("45");
	result.push_back("46");
	result.push_back("47");
	result.push_back("48");
	result.push_back("49");
	result.push_back("50");
	result.push_back("51");
	result.push_back("52");
	result.push_back("53");
	result.push_back("54");
	result.push_back("55");
	result.push_back("56");
	result.push_back("57");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 8 */

	query = declaration + "Select w1 such that Parent*(w1,43) and Modifies(w1,\"varLoop10\")";
	PQLParser::parse(query);
	result.push_back("32");
	result.push_back("33");
	result.push_back("34");
	result.push_back("35");
	result.push_back("36");
	result.push_back("38");
	result.push_back("39");
	result.push_back("40");
	result.push_back("41");
	result.push_back("42");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 9 */

	query = declaration + "Select w1 such that Parent*(w1,43) and Modifies(w1,\"varLoop10\") and Follows*(w1,35) pattern a2(_,_\"varLoop1\"_) pattern a1(_,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 10 */

	query = declaration + "Select c1 such that Parent*(w1,43) pattern a1(_,_) such that Modifies(w1,\"varLoop10\") and Follows*(w1,57) pattern a2(_,_\"varLoop1\"_)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12345");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 11 */

	query = declaration + "Select v1 such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1)";
	PQLParser::parse(query);
	result.push_back("varLoop5");
	result.push_back("varLoop10");
	result.push_back("varLoop9");
	result.push_back("varLoop8");
	result.push_back("varLoop7");
	result.push_back("varLoop6");
	result.push_back("varLoop4");
	result.push_back("varLoop2");
	result.push_back("varLoop1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 12 */

	query = declaration + "Select v1 such that Parent*(w1,51) and Modifies(w1,v1) and Uses(w1,v1) pattern a1(_,_) and pattern a2(_,_\"varLoop1\"_)";
	PQLParser::parse(query);
	result.push_back("varLoop5");
	result.push_back("varLoop10");
	result.push_back("varLoop9");
	result.push_back("varLoop8");
	result.push_back("varLoop7");
	result.push_back("varLoop6");
	result.push_back("varLoop4");
	result.push_back("varLoop2");
	result.push_back("varLoop1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	cout << "SUCCESS! testAnd :p" <<endl;
}

void TestQueryEvaluator::testBoolWith() {
	try {
		PKBParser::parse("testcases/with_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}
	cout<< "testBoolWith = ";
	/* Test BOOL 1 */

	query = declaration + "Select BOOLEAN with v1.varName=\"x\"";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 2 */

	query = declaration + "Select BOOLEAN with v1.varName=\"x\"";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 3 */

	query = declaration + "Select BOOLEAN with v1.varName=\"x\" and s1.stmt#=10";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 4 */

	query = declaration + "Select BOOLEAN with v1.varName=\"x\" and s1.stmt#=10";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 5 */

	query = declaration + "Select BOOLEAN with v1.varName=v2.varName and v2.varName=\"k\"";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 6 */

	query = declaration + "Select BOOLEAN with v1.varName=v2.varName and v2.varName=\"z\"";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 7 */

	query = declaration + "Select BOOLEAN with v1.varName=v2.varName and v2.varName=v3.varName";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test BOOL 8 */

	query = declaration + "Select BOOLEAN with v1.varName=v2.varName and v2.varName=v3.varName and v4.varName=\"y\"";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();



	cout<< "SUCCESS ! testBoolWith :D" << endl;
}

void TestQueryEvaluator::testWith(){
	try {
		PKBParser::parse("testcases/with_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}
	cout<< "testWith = ";

	/* Test 1 */
	query = declaration + "Select a1 with v1.varName=\"x\"";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 2 */

	query = declaration + "Select s1 with v1.varName=\"x\"";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 3 */

	query = declaration + "Select a1 with v1.varName=\"x\" and s1.stmt#=10";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 4 */

	query = declaration + "Select s1 with v1.varName=\"x\" and s1.stmt#=10";
	PQLParser::parse(query);
	result.push_back("10");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 5 */

	query = declaration + "Select a1 with v1.varName=v2.varName and v2.varName=\"k\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 6 */

	query = declaration + "Select a1 with v1.varName=v2.varName and v2.varName=\"z\"";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 7 */

	query = declaration + "Select a1 with v1.varName=v2.varName and v2.varName=v3.varName";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 8 */

	query = declaration + "Select a1 with v1.varName=v2.varName and v2.varName=v3.varName and v4.varName=\"y\"";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 9 */
	query = declaration + "Select s1 with s1.stmt#=s2.stmt# and s2.stmt#=1";
	PQLParser::parse(query);
	result.push_back("1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 10 */
	query = declaration + "Select s1 with s1.stmt#=s2.stmt# and s2.stmt#=9999";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 11 */
	query = declaration + "Select s1 with s1.stmt#=s2.stmt# and s2.stmt#=c1.value";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 12 */
	query = declaration + "Select s1 with s1.stmt#=s2.stmt# and s2.stmt#=c1.value and c1.value=c2.value and c2.value=2";
	PQLParser::parse(query);
	result.push_back("2");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 13 */
	query = declaration + "Select s1 with s1.stmt#=s2.stmt# and s2.stmt#=c1.value and c1.value=c2.value and c2.value=10000";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 13 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 14 */
	query = declaration + "Select c1 with c1.value=0";
	PQLParser::parse(query);
	result.push_back("0");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 14 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 15 */
	query = declaration + "Select c1 with c1.value=99999";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 15 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 16 */
	query = declaration + "Select c1 with c1.value=c2.value and c2.value=2";
	PQLParser::parse(query);
	result.push_back("2");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 16 " << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	PKBParser::cleanUp();
	try {
		PKBParser::parse("testcases/with2_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}
	/* Test 17 */

	query = declaration + "Select s1 with s1.stmt#=1";
	PQLParser::parse(query);
	result.push_back("1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 17" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 18 */

	query = declaration + "Select s1 with s1.stmt#=1312312311";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 18" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 19 */

	query = declaration + "Select s1 with s1.stmt#=999999";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 19" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 20 */

	query = declaration + "Select c1 with c1.value=2";
	PQLParser::parse(query);
	result.push_back("2");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 20" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 21 */

	query = declaration + "Select c1 with c1.value=1";
	PQLParser::parse(query);
	result.push_back("1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 21" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 22 */

	query = declaration + "Select c1 with c1.value=12312";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 22" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 23 */

	query = declaration + "Select c1 with c1.value=123019230192";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 23" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 24 */

	query = declaration + "Select c1 with c1.value=1";
	PQLParser::parse(query);
	result.push_back("1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 24" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 25 */

	query = declaration + "Select v1 with v1.varName=\"j\"";
	PQLParser::parse(query);
	result.push_back("j");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 25" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 26 */

	query = declaration + "Select v1 with v1.varName=\"varLoop5\"";
	PQLParser::parse(query);
	result.push_back("varLoop5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 26" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 27 */

	query = declaration + "Select v1 with v1.varName=\"vasdasdasd\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 27" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 28 */

	query = declaration + "Select p1 with p1.procName=\"Second\"";
	PQLParser::parse(query);
	result.push_back("Second");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 28" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 29 */

	query = declaration + "Select p1 with p1.procName=\"InsaneWhile\"";
	PQLParser::parse(query);
	result.push_back("InsaneWhile");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 29" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 30 */

	query = declaration + "Select p1 with p1.procName=\"Wrong\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 30" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 31 */

	query = declaration + "Select s1 with s1.stmt#=s1.stmt#";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");
	result.push_back("32");
	result.push_back("33");
	result.push_back("34");
	result.push_back("35");
	result.push_back("36");
	result.push_back("37");
	result.push_back("38");
	result.push_back("39");
	result.push_back("40");
	result.push_back("41");
	result.push_back("42");
	result.push_back("43");
	result.push_back("44");
	result.push_back("45");
	result.push_back("46");
	result.push_back("47");
	result.push_back("48");
	result.push_back("49");
	result.push_back("50");
	result.push_back("51");
	result.push_back("52");
	result.push_back("53");
	result.push_back("54");
	result.push_back("55");
	result.push_back("56");
	result.push_back("57");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 31" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 32 */

	query = declaration + "Select s1 with s1.stmt#=s2.stmt#";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");
	result.push_back("32");
	result.push_back("33");
	result.push_back("34");
	result.push_back("35");
	result.push_back("36");
	result.push_back("37");
	result.push_back("38");
	result.push_back("39");
	result.push_back("40");
	result.push_back("41");
	result.push_back("42");
	result.push_back("43");
	result.push_back("44");
	result.push_back("45");
	result.push_back("46");
	result.push_back("47");
	result.push_back("48");
	result.push_back("49");
	result.push_back("50");
	result.push_back("51");
	result.push_back("52");
	result.push_back("53");
	result.push_back("54");
	result.push_back("55");
	result.push_back("56");
	result.push_back("57");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 32" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 33 */

	query = declaration + "Select s1 with s1.stmt#=s2.stmt# and s2.stmt#=30";
	PQLParser::parse(query);
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 33" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 34 */

	query = declaration + "Select s1 with s1.stmt#=s2.stmt# and s2.stmt#=30 and s3.stmt#=s2.stmt#";
	PQLParser::parse(query);
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 34" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 35 */

	query = declaration + "Select s1 with s1.stmt#=s2.stmt# and s2.stmt#=12312";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 35" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 36 */

	query = declaration + "Select s1 with s1.stmt#=s2.stmt# and s3.stmt#=12312";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 36" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 37 */

	query = declaration + "Select s1 with s1.stmt#=c1.value";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 37" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 38 */

	query = declaration + "Select c1 with s1.stmt#=c1.value";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 38" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 39 */

	query = declaration + "Select s1 with s1.stmt#=s2.stmt# and c1.value=s2.stmt#";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 39" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 40 */

	query = declaration + "Select c1 with s1.stmt#=s2.stmt# and c1.value=s2.stmt#";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 40" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 41 */

	query = declaration + "Select c1 with s1.stmt#=s2.stmt# and c1.value=s2.stmt# and c1.value=c2.value and c2.value = 0";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 41" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 42 */

	query = declaration + "Select s1 with s1.stmt#=s2.stmt# and c1.value=s2.stmt# and c1.value=c2.value and c2.value = 0";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 42" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 43 */

	query = declaration + "Select c1 with s1.stmt#=s2.stmt# and c1.value=s2.stmt# and c1.value=c2.value and c2.value = 1";
	PQLParser::parse(query);
	result.push_back("1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 43" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 44 */

	query = declaration + "Select s1 with s1.stmt#=s2.stmt# and c1.value=s2.stmt# and c1.value=c2.value and c2.value = 1";
	PQLParser::parse(query);
	result.push_back("1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 44" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 45 */

	query = declaration + "Select c1 with c1.value=c1.value";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12345");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 45" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 46 */

	query = declaration + "Select c2 with c1.value=c2.value";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12345");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 46" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 47 */

	query = declaration + "Select c1 with c1.value=c2.value and c2.value=0";
	PQLParser::parse(query);
	result.push_back("0");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 47" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 48 */

	query = declaration + "Select c1 with c1.value=c2.value and c2.value=0 and c3.value=c2.value";
	PQLParser::parse(query);
	result.push_back("0");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 48" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 49 */

	query = declaration + "Select c1 with c1.value=c2.value and c2.value=312931923";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 49" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 50 */

	query = declaration + "Select c1 with c1.value=c2.value and c3.value=312931923";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 50" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 51 */

	query = declaration + "Select v1 with v1.varName=v1.varName";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");
	result.push_back("e");
	result.push_back("f");
	result.push_back("varA");
	result.push_back("varB");
	result.push_back("varC");
	result.push_back("varD");
	result.push_back("g");
	result.push_back("varE");
	result.push_back("varF");
	result.push_back("varG");
	result.push_back("loop1");
	result.push_back("loop2");
	result.push_back("loop3");
	result.push_back("loop4");
	result.push_back("loop5");
	result.push_back("varLoop5");
	result.push_back("loop6");
	result.push_back("loop7");
	result.push_back("loop8");
	result.push_back("loop9");
	result.push_back("loop10");
	result.push_back("lastLoop");
	result.push_back("varLastLoop");
	result.push_back("varLoop10");
	result.push_back("varLoop9");
	result.push_back("varLoop8");
	result.push_back("varLoop7");
	result.push_back("varLoop6");
	result.push_back("loop4Inside");
	result.push_back("varLoop4");
	result.push_back("varLoop3");
	result.push_back("varLoop2");
	result.push_back("varLoop1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 51" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 52 */

	query = declaration + "Select v1 with v1.varName=v2.varName";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");
	result.push_back("e");
	result.push_back("f");
	result.push_back("varA");
	result.push_back("varB");
	result.push_back("varC");
	result.push_back("varD");
	result.push_back("g");
	result.push_back("varE");
	result.push_back("varF");
	result.push_back("varG");
	result.push_back("loop1");
	result.push_back("loop2");
	result.push_back("loop3");
	result.push_back("loop4");
	result.push_back("loop5");
	result.push_back("varLoop5");
	result.push_back("loop6");
	result.push_back("loop7");
	result.push_back("loop8");
	result.push_back("loop9");
	result.push_back("loop10");
	result.push_back("lastLoop");
	result.push_back("varLastLoop");
	result.push_back("varLoop10");
	result.push_back("varLoop9");
	result.push_back("varLoop8");
	result.push_back("varLoop7");
	result.push_back("varLoop6");
	result.push_back("loop4Inside");
	result.push_back("varLoop4");
	result.push_back("varLoop3");
	result.push_back("varLoop2");
	result.push_back("varLoop1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 52" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 53 */

	query = declaration + "Select v1 with v1.varName=v2.varName and v2.varName=\"varLoop1\"";
	PQLParser::parse(query);
	result.push_back("varLoop1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 53" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 54 */

	query = declaration + "Select v1 with v1.varName=v2.varName and v2.varName=\"varLoop1\" and v3.varName=v2.varName";
	PQLParser::parse(query);
	result.push_back("varLoop1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 54" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 55 */

	query = declaration + "Select v1 with v1.varName=v2.varName and v2.varName=\"asdas\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 55" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 56 */

	query = declaration + "Select v1 with v1.varName=v2.varName and v3.varName=\"gakada\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 56" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 57 */

	query = declaration + "Select p1 with p1.procName=p1.procName";
	PQLParser::parse(query);
	result.push_back("Second");
	result.push_back("InsaneWhile");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 57" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 58 */

	query = declaration + "Select p1 with p1.procName=p2.procName";
	PQLParser::parse(query);
	result.push_back("Second");
	result.push_back("InsaneWhile");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 58" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 59 */

	query = declaration + "Select p1 with p1.procName=p2.procName and p2.procName=\"Second\"";
	PQLParser::parse(query);
	result.push_back("Second");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 59" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 60 */

	query = declaration + "Select p1 with p1.procName=p2.procName and p2.procName=\"InsaneWhile\" and p3.procName=p1.procName";
	PQLParser::parse(query);
	result.push_back("InsaneWhile");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 60" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 61 */

	query = declaration + "Select p1 with p1.procName=p2.procName and p2.procName=\"NoProcedure\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 61" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 62 */

	query = declaration + "Select p1 with p1.procName=p2.procName and p3.procName=\"NoProcedure\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 62" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 63 */

	query = declaration + "Select p1 with p1.procName=v1.varName";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 63" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 64 */

	query = declaration + "Select v1 with p1.procName=v1.varName";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 64" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 65 */

	query = declaration + "Select p1 with p1.procName=p2.procName and v1.varName=v2.varName";
	PQLParser::parse(query);
	result.push_back("Second");
	result.push_back("InsaneWhile");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 65" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 66 */

	query = declaration + "Select v1 with p1.procName=p2.procName and v1.varName=v2.varName";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");
	result.push_back("e");
	result.push_back("f");
	result.push_back("varA");
	result.push_back("varB");
	result.push_back("varC");
	result.push_back("varD");
	result.push_back("g");
	result.push_back("varE");
	result.push_back("varF");
	result.push_back("varG");
	result.push_back("loop1");
	result.push_back("loop2");
	result.push_back("loop3");
	result.push_back("loop4");
	result.push_back("loop5");
	result.push_back("varLoop5");
	result.push_back("loop6");
	result.push_back("loop7");
	result.push_back("loop8");
	result.push_back("loop9");
	result.push_back("loop10");
	result.push_back("lastLoop");
	result.push_back("varLastLoop");
	result.push_back("varLoop10");
	result.push_back("varLoop9");
	result.push_back("varLoop8");
	result.push_back("varLoop7");
	result.push_back("varLoop6");
	result.push_back("loop4Inside");
	result.push_back("varLoop4");
	result.push_back("varLoop3");
	result.push_back("varLoop2");
	result.push_back("varLoop1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 66" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 67 */

	query = declaration + "Select v1 with p1.procName=p2.procName and v1.varName=p2.procName and v1.varName=v2.varName and v2.varName =\"varLoop3\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 67" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 68 */

	query = declaration + "Select p1 with p1.procName=p2.procName and v1.varName=p2.procName and v1.varName=v2.varName and v2.varName =\"varLoop3\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 68" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 69 */

	query = declaration + "Select v1 with p1.procName=p2.procName and v1.varName=p2.procName and v1.varName=v2.varName and v2.varName =\"Second\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 69" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 70 */

	query = declaration + "Select v1 with p1.procName=p2.procName and v1.varName=p2.procName and v1.varName=v2.varName and v2.varName =\"InsaneWhile\"";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 70" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	cout << "SUCCESS! testWith :p" <<endl;
}

void TestQueryEvaluator::testCalls(){
	try {
		PKBParser::parse("testcases/calls_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}
	cout<< "testCalls = ";
	/* Test 1 */

	query = declaration + "Select n1 such that Calls(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 2 */

	query = declaration + "Select n1 such that Calls(p1,p2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 3 */

	query = declaration + "Select n1 such that Calls(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 4 */

	query = declaration + "Select n1 such that Calls(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 5 */

	query = declaration + "Select n1 such that Calls(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 6 */

	query = declaration + "Select n1 such that Calls(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 7 */

	query = declaration + "Select n1 such that Calls(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 8 */

	query = declaration + "Select n1 such that Calls(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 9 */

	query = declaration + "Select n1 such that Calls(_,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 10 */

	query = declaration + "Select n1 such that Calls(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 11 */

	query = declaration + "Select n1 such that Calls(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 12 */

	query = declaration + "Select s1 such that Calls(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 13 */

	query = declaration + "Select s1 such that Calls(p1,p2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 13" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 14 */

	query = declaration + "Select s1 such that Calls(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 14" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 15 */

	query = declaration + "Select s1 such that Calls(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 15" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 16 */

	query = declaration + "Select s1 such that Calls(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 16" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 17 */

	query = declaration + "Select s1 such that Calls(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 17" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 18 */

	query = declaration + "Select s1 such that Calls(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 18" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 19 */

	query = declaration + "Select s1 such that Calls(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 19" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 20 */

	query = declaration + "Select s1 such that Calls(_,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 20" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 21 */

	query = declaration + "Select s1 such that Calls(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 21" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 22 */

	query = declaration + "Select s1 such that Calls(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 22" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 23 */

	query = declaration + "Select a1 such that Calls(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 23" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 24 */

	query = declaration + "Select a1 such that Calls(p1,p2)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 24" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 25 */

	query = declaration + "Select a1 such that Calls(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 25" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 26 */

	query = declaration + "Select a1 such that Calls(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 26" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 27 */

	query = declaration + "Select a1 such that Calls(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 27" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 28 */

	query = declaration + "Select a1 such that Calls(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 28" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 29 */

	query = declaration + "Select a1 such that Calls(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 29" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 30 */

	query = declaration + "Select a1 such that Calls(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 30" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 31 */

	query = declaration + "Select a1 such that Calls(_,_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 31" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 32 */

	query = declaration + "Select a1 such that Calls(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 32" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 33 */

	query = declaration + "Select a1 such that Calls(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 33" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 34 */

	query = declaration + "Select c1 such that Calls(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 34" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 35 */

	query = declaration + "Select c1 such that Calls(p1,p2)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 35" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 36 */

	query = declaration + "Select c1 such that Calls(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 36" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 37 */

	query = declaration + "Select c1 such that Calls(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 37" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 38 */

	query = declaration + "Select c1 such that Calls(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 38" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 39 */

	query = declaration + "Select c1 such that Calls(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 39" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 40 */

	query = declaration + "Select c1 such that Calls(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 40" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 41 */

	query = declaration + "Select c1 such that Calls(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 41" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 42 */

	query = declaration + "Select c1 such that Calls(_,_)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 42" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 43 */

	query = declaration + "Select c1 such that Calls(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 43" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 44 */

	query = declaration + "Select c1 such that Calls(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 44" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 45 */

	query = declaration + "Select i1 such that Calls(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 45" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 46 */

	query = declaration + "Select i1 such that Calls(p1,p2)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 46" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 47 */

	query = declaration + "Select i1 such that Calls(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 47" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 48 */

	query = declaration + "Select i1 such that Calls(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 48" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 49 */

	query = declaration + "Select i1 such that Calls(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 49" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 50 */

	query = declaration + "Select i1 such that Calls(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 50" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 51 */

	query = declaration + "Select i1 such that Calls(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 51" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 52 */

	query = declaration + "Select i1 such that Calls(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 52" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 53 */

	query = declaration + "Select i1 such that Calls(_,_)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 53" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 54 */

	query = declaration + "Select i1 such that Calls(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 54" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 55 */

	query = declaration + "Select i1 such that Calls(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 55" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 56 */

	query = declaration + "Select w1 such that Calls(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 56" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 57 */

	query = declaration + "Select w1 such that Calls(p1,p2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 57" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 58 */

	query = declaration + "Select w1 such that Calls(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 58" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 59 */

	query = declaration + "Select w1 such that Calls(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 59" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 60 */

	query = declaration + "Select w1 such that Calls(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 60" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 61 */

	query = declaration + "Select w1 such that Calls(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 61" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 62 */

	query = declaration + "Select w1 such that Calls(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 62" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 63 */

	query = declaration + "Select w1 such that Calls(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 63" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 64 */

	query = declaration + "Select w1 such that Calls(_,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 64" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 65 */

	query = declaration + "Select w1 such that Calls(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 65" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 66 */

	query = declaration + "Select w1 such that Calls(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 66" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 67 */

	query = declaration + "Select ca1 such that Calls(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 67" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 68 */

	query = declaration + "Select ca1 such that Calls(p1,p2)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 68" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 69 */

	query = declaration + "Select ca1 such that Calls(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 69" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 70 */

	query = declaration + "Select ca1 such that Calls(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 70" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 71 */

	query = declaration + "Select ca1 such that Calls(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 71" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 72 */

	query = declaration + "Select ca1 such that Calls(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 72" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 73 */

	query = declaration + "Select ca1 such that Calls(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 73" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 74 */

	query = declaration + "Select ca1 such that Calls(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 74" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 75 */

	query = declaration + "Select ca1 such that Calls(_,_)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 75" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 76 */

	query = declaration + "Select ca1 such that Calls(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 76" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 77 */

	query = declaration + "Select ca1 such that Calls(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 77" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 78 */

	query = declaration + "Select v1 such that Calls(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 78" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 79 */

	query = declaration + "Select v1 such that Calls(p1,p2)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 79" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 80 */

	query = declaration + "Select v1 such that Calls(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 80" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 81 */

	query = declaration + "Select v1 such that Calls(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 81" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 82 */

	query = declaration + "Select v1 such that Calls(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 82" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 83 */

	query = declaration + "Select v1 such that Calls(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 83" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 84 */

	query = declaration + "Select v1 such that Calls(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 84" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 85 */

	query = declaration + "Select v1 such that Calls(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 85" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 86 */

	query = declaration + "Select v1 such that Calls(_,_)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 86" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 87 */

	query = declaration + "Select v1 such that Calls(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 87" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 88 */

	query = declaration + "Select v1 such that Calls(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 88" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 89 */

	query = declaration + "Select p1 such that Calls(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 89" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 90 */

	query = declaration + "Select p1 such that Calls(p1,p2)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 90" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 91 */

	query = declaration + "Select p1 such that Calls(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 91" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 92 */

	query = declaration + "Select p2 such that Calls(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("Beta");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 92" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 93 */

	query = declaration + "Select p1 such that Calls(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 93" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 94 */

	query = declaration + "Select p1 such that Calls(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 94" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 95 */

	query = declaration + "Select p1 such that Calls(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 95" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 96 */

	query = declaration + "Select p1 such that Calls(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 96" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 97 */

	query = declaration + "Select p1 such that Calls(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 97" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 98 */

	query = declaration + "Select p1 such that Calls(_,_)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 98" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 99 */

	query = declaration + "Select p1 such that Calls(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 99" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 100 */

	query = declaration + "Select p1 such that Calls(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 100" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 101 */

	query = declaration + "Select BOOLEAN such that Calls(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 101" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 102 */

	query = declaration + "Select BOOLEAN such that Calls(p1,p2)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 102" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 103 */

	query = declaration + "Select BOOLEAN such that Calls(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 103" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 104 */

	query = declaration + "Select BOOLEAN such that Calls(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 104" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 105 */

	query = declaration + "Select BOOLEAN such that Calls(p1,\"Caller\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 105" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 106 */

	query = declaration + "Select BOOLEAN such that Calls(\"Gamma\",p2)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 106" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 107 */

	query = declaration + "Select BOOLEAN such that Calls(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 107" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 108 */

	query = declaration + "Select BOOLEAN such that Calls(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 108" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 109 */

	query = declaration + "Select BOOLEAN such that Calls(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 109" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 110 */

	query = declaration + "Select BOOLEAN such that Calls(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 110" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 111 */

	query = declaration + "Select BOOLEAN such that Calls(\"Gamma\",_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 111" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	cout << "SUCCESS! testCalls :p" <<endl;
}

void TestQueryEvaluator::testCallsT(){
	try {
		PKBParser::parse("testcases/calls_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}
	cout<< "testCallsT = ";
	/* Test 1 */

	query = declaration + "Select n1 such that Calls*(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 2 */

	query = declaration + "Select n1 such that Calls*(p1,p2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 3 */

	query = declaration + "Select n1 such that Calls*(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 4 */

	query = declaration + "Select n1 such that Calls*(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 5 */

	query = declaration + "Select n1 such that Calls*(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 6 */

	query = declaration + "Select n1 such that Calls*(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 7 */

	query = declaration + "Select n1 such that Calls*(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 8 */

	query = declaration + "Select n1 such that Calls*(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 9 */

	query = declaration + "Select n1 such that Calls*(_,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 10 */

	query = declaration + "Select n1 such that Calls*(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 11 */

	query = declaration + "Select n1 such that Calls*(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 12 */

	query = declaration + "Select s1 such that Calls*(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 13 */

	query = declaration + "Select s1 such that Calls*(p1,p2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 13" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 14 */

	query = declaration + "Select s1 such that Calls*(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 14" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 15 */

	query = declaration + "Select s1 such that Calls*(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 15" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 16 */

	query = declaration + "Select s1 such that Calls*(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 16" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 17 */

	query = declaration + "Select s1 such that Calls*(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 17" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 18 */

	query = declaration + "Select s1 such that Calls*(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 18" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 19 */

	query = declaration + "Select s1 such that Calls*(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 19" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 20 */

	query = declaration + "Select s1 such that Calls*(_,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 20" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 21 */

	query = declaration + "Select s1 such that Calls*(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 21" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 22 */

	query = declaration + "Select s1 such that Calls*(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 22" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 23 */

	query = declaration + "Select a1 such that Calls*(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 23" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 24 */

	query = declaration + "Select a1 such that Calls*(p1,p2)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 24" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 25 */

	query = declaration + "Select a1 such that Calls*(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 25" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 26 */

	query = declaration + "Select a1 such that Calls*(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 26" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 27 */

	query = declaration + "Select a1 such that Calls*(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 27" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 28 */

	query = declaration + "Select a1 such that Calls*(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 28" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 29 */

	query = declaration + "Select a1 such that Calls*(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 29" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 30 */

	query = declaration + "Select a1 such that Calls*(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 30" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 31 */

	query = declaration + "Select a1 such that Calls*(_,_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 31" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 32 */

	query = declaration + "Select a1 such that Calls*(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 32" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 33 */

	query = declaration + "Select a1 such that Calls*(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 33" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 34 */

	query = declaration + "Select c1 such that Calls*(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 34" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 35 */

	query = declaration + "Select c1 such that Calls*(p1,p2)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 35" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 36 */

	query = declaration + "Select c1 such that Calls*(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 36" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 37 */

	query = declaration + "Select c1 such that Calls*(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 37" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 38 */

	query = declaration + "Select c1 such that Calls*(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 38" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 39 */

	query = declaration + "Select c1 such that Calls*(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 39" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 40 */

	query = declaration + "Select c1 such that Calls*(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 40" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 41 */

	query = declaration + "Select c1 such that Calls*(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 41" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 42 */

	query = declaration + "Select c1 such that Calls*(_,_)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 42" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 43 */

	query = declaration + "Select c1 such that Calls*(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 43" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 44 */

	query = declaration + "Select c1 such that Calls*(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 44" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 45 */

	query = declaration + "Select i1 such that Calls*(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 45" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 46 */

	query = declaration + "Select i1 such that Calls*(p1,p2)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 46" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 47 */

	query = declaration + "Select i1 such that Calls*(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 47" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 48 */

	query = declaration + "Select i1 such that Calls*(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 48" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 49 */

	query = declaration + "Select i1 such that Calls*(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 49" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 50 */

	query = declaration + "Select i1 such that Calls*(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 50" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 51 */

	query = declaration + "Select i1 such that Calls*(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 51" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 52 */

	query = declaration + "Select i1 such that Calls*(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 52" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 53 */

	query = declaration + "Select i1 such that Calls*(_,_)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 53" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 54 */

	query = declaration + "Select i1 such that Calls*(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 54" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 55 */

	query = declaration + "Select i1 such that Calls*(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 55" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 56 */

	query = declaration + "Select w1 such that Calls*(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 56" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 57 */

	query = declaration + "Select w1 such that Calls*(p1,p2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 57" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 58 */

	query = declaration + "Select w1 such that Calls*(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 58" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 59 */

	query = declaration + "Select w1 such that Calls*(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 59" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 60 */

	query = declaration + "Select w1 such that Calls*(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 60" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 61 */

	query = declaration + "Select w1 such that Calls*(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 61" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 62 */

	query = declaration + "Select w1 such that Calls*(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 62" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 63 */

	query = declaration + "Select w1 such that Calls*(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 63" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 64 */

	query = declaration + "Select w1 such that Calls*(_,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 64" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 65 */

	query = declaration + "Select w1 such that Calls*(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 65" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 66 */

	query = declaration + "Select w1 such that Calls*(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 66" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 67 */

	query = declaration + "Select ca1 such that Calls*(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 67" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 68 */

	query = declaration + "Select ca1 such that Calls*(p1,p2)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 68" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 69 */

	query = declaration + "Select ca1 such that Calls*(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 69" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 70 */

	query = declaration + "Select ca1 such that Calls*(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 70" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 71 */

	query = declaration + "Select ca1 such that Calls*(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 71" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 72 */

	query = declaration + "Select ca1 such that Calls*(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 72" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 73 */

	query = declaration + "Select ca1 such that Calls*(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 73" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 74 */

	query = declaration + "Select ca1 such that Calls*(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 74" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 75 */

	query = declaration + "Select ca1 such that Calls*(_,_)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 75" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 76 */

	query = declaration + "Select ca1 such that Calls*(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 76" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 77 */

	query = declaration + "Select ca1 such that Calls*(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 77" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 78 */

	query = declaration + "Select v1 such that Calls*(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 78" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 79 */

	query = declaration + "Select v1 such that Calls*(p1,p2)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 79" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 80 */

	query = declaration + "Select v1 such that Calls*(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 80" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 81 */

	query = declaration + "Select v1 such that Calls*(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 81" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 82 */

	query = declaration + "Select v1 such that Calls*(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 82" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 83 */

	query = declaration + "Select v1 such that Calls*(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 83" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 84 */

	query = declaration + "Select v1 such that Calls*(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 84" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 85 */

	query = declaration + "Select v1 such that Calls*(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 85" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 86 */

	query = declaration + "Select v1 such that Calls*(_,_)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 86" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 87 */

	query = declaration + "Select v1 such that Calls*(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 87" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 88 */

	query = declaration + "Select v1 such that Calls*(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 88" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 89 */

	query = declaration + "Select p1 such that Calls*(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 89" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 90 */

	query = declaration + "Select p1 such that Calls*(p1,p2)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 90" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 91 */

	query = declaration + "Select p1 such that Calls*(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 91" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 92 */

	query = declaration + "Select p2 such that Calls*(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("Beta");
	result.push_back("Gamma");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 92" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 93 */

	query = declaration + "Select p1 such that Calls*(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 93" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 94 */

	query = declaration + "Select p1 such that Calls*(p1,\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 94" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 95 */

	query = declaration + "Select p1 such that Calls*(\"Gamma\",p2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 95" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 96 */

	query = declaration + "Select p1 such that Calls*(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 96" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 97 */

	query = declaration + "Select p1 such that Calls*(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 97" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 98 */

	query = declaration + "Select p1 such that Calls*(_,_)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 98" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 99 */

	query = declaration + "Select p1 such that Calls*(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 99" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 100 */

	query = declaration + "Select p1 such that Calls*(\"Gamma\",_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 100" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 101 */

	query = declaration + "Select BOOLEAN such that Calls*(\"Alpha\",\"Beta\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 101" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 102 */

	query = declaration + "Select BOOLEAN such that Calls*(p1,p2)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 102" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 103 */

	query = declaration + "Select BOOLEAN such that Calls*(\"Alpha\",p2)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 103" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 104 */

	query = declaration + "Select BOOLEAN such that Calls*(p1,\"Beta\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 104" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 105 */

	query = declaration + "Select BOOLEAN such that Calls*(p1,\"Caller\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 105" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 106 */

	query = declaration + "Select BOOLEAN such that Calls*(\"Gamma\",p2)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 106" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 107 */

	query = declaration + "Select BOOLEAN such that Calls*(\"Gamma\",\"Caller\")";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 107" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 108 */

	query = declaration + "Select BOOLEAN such that Calls*(\"Alpha\",\"Gamma\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 108" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 109 */

	query = declaration + "Select BOOLEAN such that Calls*(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 109" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 110 */

	query = declaration + "Select BOOLEAN such that Calls*(_,\"Alpha\")";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 110" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 111 */

	query = declaration + "Select BOOLEAN such that Calls*(\"Gamma\",_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 111" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();



	cout<< "SUCCESS! testCallsTransitive!! :D" <<endl;
}

void TestQueryEvaluator::testNext(){
	try {
		PKBParser::parse("testcases/calls_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}
	cout<< "testNext = ";
	/* Test 1 */

	query = declaration + "Select n1 such that Next(2,n1)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 2 */

	query = declaration + "Select n1 such that Next(n1,2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("3");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 3 */

	query = declaration + "Select n1 such that Next(3,n1)";
	PQLParser::parse(query);
	result.push_back("2");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}
	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 4 */

	query = declaration + "Select n1 such that Next(6,7)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 5 */

	query = declaration + "Select n1 such that Next(6,n1)";
	PQLParser::parse(query);
	result.push_back("1");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 6 */

	query = declaration + "Select n1 such that Next(10,n1)";
	PQLParser::parse(query);
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 7 */

	query = declaration + "Select n1 such that Next(12,n1)";
	PQLParser::parse(query);
	result.push_back("11");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 8 */

	query = declaration + "Select n1 such that Next(12,11)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 9 */

	query = declaration + "Select n1 such that Next(6,2);";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 10 */

	query = declaration + "Select n1 such that Next(2,2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 11 */

	query = declaration + "Select n1 such that Next(n1,21)";
	PQLParser::parse(query);
	result.push_back("17");
	result.push_back("20");
	result.push_back("23");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 12 */

	query = declaration + "Select n1 such that Next(23,21)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 13 */

	query = declaration + "Select n1 such that Next(23,22)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 13" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 14 */

	query = declaration + "Select n1 such that Next(15,n1)";
	PQLParser::parse(query);
	result.push_back("16");
	result.push_back("18");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 14" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 15 */

	query = declaration + "Select n1 such that Next(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 15" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 16 */

	query = declaration + "Select n1 such that Next(29,30)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 16" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 17 */

	query = declaration + "Select n1 such that Next(30,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 17" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 18 */

	query = declaration + "Select n1 such that Next(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 18" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 19 */

	query = declaration + "Select n1 such that Next(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 19" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 20 */

	query = declaration + "Select n1 such that Next(_,1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 20" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 21 */

	query = declaration + "Select n1 such that Next(_,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 21" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 22 */

	query = declaration + "Select s1 such that Next(2,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 22" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 23 */

	query = declaration + "Select s1 such that Next(n1,2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 23" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 24 */

	query = declaration + "Select s1 such that Next(3,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 24" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 25 */

	query = declaration + "Select s1 such that Next(6,7)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 25" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 26 */

	query = declaration + "Select s1 such that Next(6,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 26" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 27 */

	query = declaration + "Select s1 such that Next(10,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 27" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 28 */

	query = declaration + "Select s1 such that Next(12,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 28" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 29 */

	query = declaration + "Select s1 such that Next(12,11)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 29" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 30 */

	query = declaration + "Select s1 such that Next(6,2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 30" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 31 */

	query = declaration + "Select s1 such that Next(2,2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 31" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 32 */

	query = declaration + "Select s1 such that Next(n1,21)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 32" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 33 */

	query = declaration + "Select s1 such that Next(23,21)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 33" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 34 */

	query = declaration + "Select s1 such that Next(23,22)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 34" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 35 */

	query = declaration + "Select s1 such that Next(15,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 35" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 36 */

	query = declaration + "Select s1 such that Next(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 36" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 37 */

	query = declaration + "Select s1 such that Next(29,30)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 37" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 38 */

	query = declaration + "Select s1 such that Next(30,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 38" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 39 */

	query = declaration + "Select s1 such that Next(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 39" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 40 */

	query = declaration + "Select s1 such that Next(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 40" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 41 */

	query = declaration + "Select s1 such that Next(_,1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 41" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 42 */

	query = declaration + "Select s1 such that Next(_,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 42" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 43 */

	query = declaration + "Select a1 such that Next(12,n1)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 43" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 44 */

	query = declaration + "Select a1 such that Next(2,2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 44" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 45 */

	query = declaration + "Select a1 such that Next(n1,21)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 45" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 46 */

	query = declaration + "Select a1 such that Next(23,21)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 46" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 47 */

	query = declaration + "Select a1 such that Next(23,22)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 47" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 48 */

	query = declaration + "Select a1 such that Next(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 48" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 49 */

	query = declaration + "Select a1 such that Next(30,_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 49" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 50 */

	query = declaration + "Select a1 such that Next(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 50" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 51 */

	query = declaration + "Select a1 such that Next(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 51" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 52 */

	query = declaration + "Select a1 such that Next(_,1)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 52" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 53 */

	query = declaration + "Select a1 such that Next(_,_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 53" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 54 */

	query = declaration + "Select c1 such that Next(12,n1)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 54" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 55 */

	query = declaration + "Select c1 such that Next(2,2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 55" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 56 */

	query = declaration + "Select c1 such that Next(n1,21)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 56" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 57 */

	query = declaration + "Select c1 such that Next(23,21)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 57" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 58 */

	query = declaration + "Select c1 such that Next(23,22)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 58" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 59 */

	query = declaration + "Select c1 such that Next(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 59" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 60 */

	query = declaration + "Select c1 such that Next(30,_)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 60" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 61 */

	query = declaration + "Select c1 such that Next(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 61" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 62 */

	query = declaration + "Select c1 such that Next(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 62" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 63 */

	query = declaration + "Select c1 such that Next(_,1)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 63" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 64 */

	query = declaration + "Select c1 such that Next(_,_)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 64" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 65 */

	query = declaration + "Select i1 such that Next(12,n1)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 65" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 66 */

	query = declaration + "Select i1 such that Next(2,2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 66" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 67 */

	query = declaration + "Select i1 such that Next(n1,21)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 67" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 68 */

	query = declaration + "Select i1 such that Next(23,21)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 68" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 69 */

	query = declaration + "Select i1 such that Next(23,22)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 69" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 70 */

	query = declaration + "Select i1 such that Next(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 70" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 71 */

	query = declaration + "Select i1 such that Next(30,_)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 71" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 72 */

	query = declaration + "Select i1 such that Next(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 72" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 73 */

	query = declaration + "Select i1 such that Next(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 73" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 74 */

	query = declaration + "Select i1 such that Next(_,1)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 74" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 75 */

	query = declaration + "Select i1 such that Next(_,_)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 75" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 76 */

	query = declaration + "Select w1 such that Next(12,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 76" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 77 */

	query = declaration + "Select w1 such that Next(2,2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 77" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 78 */

	query = declaration + "Select w1 such that Next(n1,21)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 78" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 79 */

	query = declaration + "Select w1 such that Next(23,21)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 79" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 80 */

	query = declaration + "Select w1 such that Next(23,22)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 80" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 81 */

	query = declaration + "Select w1 such that Next(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 81" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 82 */

	query = declaration + "Select w1 such that Next(30,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 82" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 83 */

	query = declaration + "Select w1 such that Next(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 83" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 84 */

	query = declaration + "Select w1 such that Next(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 84" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 85 */

	query = declaration + "Select w1 such that Next(_,1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 85" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 86 */

	query = declaration + "Select w1 such that Next(_,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 86" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 87 */

	query = declaration + "Select ca1 such that Next(12,n1)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 87" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 88 */

	query = declaration + "Select ca1 such that Next(2,2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 88" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 89 */

	query = declaration + "Select ca1 such that Next(n1,21)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 89" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 90 */

	query = declaration + "Select ca1 such that Next(23,21)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 90" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 91 */

	query = declaration + "Select ca1 such that Next(23,22)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 91" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 92 */

	query = declaration + "Select ca1 such that Next(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 92" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 93 */

	query = declaration + "Select ca1 such that Next(30,_)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 93" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 94 */

	query = declaration + "Select ca1 such that Next(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 94" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 95 */

	query = declaration + "Select ca1 such that Next(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 95" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 96 */

	query = declaration + "Select ca1 such that Next(_,1)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 96" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 97 */

	query = declaration + "Select ca1 such that Next(_,_)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 97" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 98 */

	query = declaration + "Select v1 such that Next(12,n1)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 98" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 99 */

	query = declaration + "Select v1 such that Next(2,2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 99" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 100 */

	query = declaration + "Select v1 such that Next(n1,21)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 100" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 101 */

	query = declaration + "Select v1 such that Next(23,21)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 101" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 102 */

	query = declaration + "Select v1 such that Next(23,22)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 102" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 103 */

	query = declaration + "Select v1 such that Next(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 103" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 104 */

	query = declaration + "Select v1 such that Next(30,_)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 104" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 105 */

	query = declaration + "Select v1 such that Next(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 105" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 106 */

	query = declaration + "Select v1 such that Next(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 106" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 107 */

	query = declaration + "Select v1 such that Next(_,1)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 107" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 108 */

	query = declaration + "Select v1 such that Next(_,_)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 108" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 109 */

	query = declaration + "Select p1 such that Next(12,n1)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 109" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 110 */

	query = declaration + "Select p1 such that Next(2,2)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 110" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 111 */

	query = declaration + "Select p1 such that Next(n1,21)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 111" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 112 */

	query = declaration + "Select p1 such that Next(23,21)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 112" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 113 */

	query = declaration + "Select p1 such that Next(23,22)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 113" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();	


	/* Test 114 */

	query = declaration + "Select p1 such that Next(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 114" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();	


	/* Test 115 */

	query = declaration + "Select p1 such that Next(30,_)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 115" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();	


	/* Test 116 */

	query = declaration + "Select p1 such that Next(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 116" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();	


	/* Test 117 */

	query = declaration + "Select p1 such that Next(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 117" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();	


	/* Test 118 */

	query = declaration + "Select p1 such that Next(_,1)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 118" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();	


	/* Test 119 */

	query = declaration + "Select p1 such that Next(_,_)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 119" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 120 */

	query = declaration + "Select BOOLEAN such that Next(3,n1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 120" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 121 */

	query = declaration + "Select BOOLEAN such that Next(6,1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 121" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 122 */

	query = declaration + "Select BOOLEAN such that Next(10,n1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 122" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 123 */

	query = declaration + "Select BOOLEAN such that Next(12,n1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 123" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 124 */

	query = declaration + "Select BOOLEAN such that Next(6,2)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 124" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 125 */

	query = declaration + "Select BOOLEAN such that Next(2,2)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 125" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 126 */

	query = declaration + "Select BOOLEAN such that Next(n1,21)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 126" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 127 */

	query = declaration + "Select BOOLEAN such that Next(17,18)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 127" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 128 */

	query = declaration + "Select BOOLEAN such that Next(30,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 128" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 129 */

	query = declaration + "Select BOOLEAN such that Next(31,_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 129" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 130 */

	query = declaration + "Select BOOLEAN such that Next(_,28)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 130" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 131 */

	query = declaration + "Select BOOLEAN such that Next(_,1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 131" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 132 */

	query = declaration + "Select BOOLEAN such that Next(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 132" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	cout<< "SUCCESS! testNext!! :D" <<endl;
}

void TestQueryEvaluator::testNextT(){
	try {
		PKBParser::parse("testcases/calls_source.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}
	cout<< "testNextT = ";
	/* Test 1 */

	query = declaration + "Select n1 such that Next*(2,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 1" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 2 */

	query = declaration + "Select n1 such that Next*(n1,2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 2" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 3 */

	query = declaration + "Select n1 such that Next*(3,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 3" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 4 */

	query = declaration + "Select n1 such that Next*(5,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 4" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 5 */

	query = declaration + "Select n1 such that Next*(6,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 5" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 6 */

	query = declaration + "Select n1 such that Next*(10,n1)";
	PQLParser::parse(query);
	result.push_back("11");
	result.push_back("12");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 6" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 7 */

	query = declaration + "Select n1 such that Next*(12,n1)";
	PQLParser::parse(query);
	result.push_back("11");
	result.push_back("12");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 7" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 8 */

	query = declaration + "Select n1 such that Next*(12,11)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 8" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 9 */

	query = declaration + "Select n1 such that Next*(6,2);";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 9" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 10 */

	query = declaration + "Select n1 such that Next*(2,2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 10" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 11 */

	query = declaration + "Select n1 such that Next*(n1,21)";
	PQLParser::parse(query);
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 11" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 12 */

	query = declaration + "Select n1 such that Next*(23,21)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 12" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 13 */

	query = declaration + "Select n1 such that Next*(23,22)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 13" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 14 */

	query = declaration + "Select n1 such that Next*(15,n1)";
	PQLParser::parse(query);
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 14" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 15 */

	query = declaration + "Select n1 such that Next*(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 15" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 16 */

	query = declaration + "Select n1 such that Next*(29,30)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 16" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 17 */

	query = declaration + "Select n1 such that Next*(30,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 17" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 18 */

	query = declaration + "Select n1 such that Next*(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 18" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 19 */

	query = declaration + "Select n1 such that Next*(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 19" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 20 */

	query = declaration + "Select n1 such that Next*(_,1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 20" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 21 */

	query = declaration + "Select n1 such that Next*(_,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 21" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 22 */

	query = declaration + "Select s1 such that Next*(2,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 22" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 23 */

	query = declaration + "Select s1 such that Next*(n1,2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 23" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 24 */

	query = declaration + "Select s1 such that Next*(3,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 24" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 25 */

	query = declaration + "Select s1 such that Next*(5,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 25" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 26 */

	query = declaration + "Select s1 such that Next*(6,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 26" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 27 */

	query = declaration + "Select s1 such that Next*(10,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 27" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 28 */

	query = declaration + "Select s1 such that Next*(12,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 28" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 29 */

	query = declaration + "Select s1 such that Next*(12,11)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 29" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 30 */

	query = declaration + "Select s1 such that Next*(6,2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 30" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 31 */

	query = declaration + "Select s1 such that Next*(2,2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 31" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 32 */

	query = declaration + "Select s1 such that Next*(n1,21)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 32" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 33 */

	query = declaration + "Select s1 such that Next*(23,21)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 33" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 34 */

	query = declaration + "Select s1 such that Next*(23,22)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 34" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 35 */

	query = declaration + "Select s1 such that Next*(15,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 35" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 36 */

	query = declaration + "Select s1 such that Next*(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 36" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 37 */

	query = declaration + "Select s1 such that Next*(29,30)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 37" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 38 */

	query = declaration + "Select s1 such that Next*(30,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 38" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 39 */

	query = declaration + "Select s1 such that Next*(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 39" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 40 */

	query = declaration + "Select s1 such that Next*(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 40" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 41 */

	query = declaration + "Select s1 such that Next*(_,1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 41" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 42 */

	query = declaration + "Select s1 such that Next*(_,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 42" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 43 */

	query = declaration + "Select a1 such that Next*(12,n1)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 43" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 44 */

	query = declaration + "Select a1 such that Next*(2,2)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 44" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 45 */

	query = declaration + "Select a1 such that Next*(n1,21)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 45" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 46 */

	query = declaration + "Select a1 such that Next*(23,21)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 46" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 47 */

	query = declaration + "Select a1 such that Next*(23,22)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 47" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 48 */

	query = declaration + "Select a1 such that Next*(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 48" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 49 */

	query = declaration + "Select a1 such that Next*(30,_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 49" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 50 */

	query = declaration + "Select a1 such that Next*(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 50" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 51 */

	query = declaration + "Select a1 such that Next*(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 51" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 52 */

	query = declaration + "Select a1 such that Next*(_,1)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 52" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 53 */

	query = declaration + "Select a1 such that Next*(_,_)";
	PQLParser::parse(query);
	result.push_back("3");
	result.push_back("4");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 53" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 54 */

	query = declaration + "Select c1 such that Next*(12,n1)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 54" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 55 */

	query = declaration + "Select c1 such that Next*(2,2)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 55" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 56 */

	query = declaration + "Select c1 such that Next*(n1,21)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 56" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 57 */

	query = declaration + "Select c1 such that Next*(23,21)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 57" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 58 */

	query = declaration + "Select c1 such that Next*(23,22)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 58" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 59 */

	query = declaration + "Select c1 such that Next*(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 59" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 60 */

	query = declaration + "Select c1 such that Next*(30,_)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 60" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 61 */

	query = declaration + "Select c1 such that Next*(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 61" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 62 */

	query = declaration + "Select c1 such that Next*(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 62" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 63 */

	query = declaration + "Select c1 such that Next*(_,1)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 63" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 64 */

	query = declaration + "Select c1 such that Next*(_,_)";
	PQLParser::parse(query);
	result.push_back("0");
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 64" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 65 */

	query = declaration + "Select i1 such that Next*(12,n1)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 65" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 66 */

	query = declaration + "Select i1 such that Next*(2,2)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 66" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 67 */

	query = declaration + "Select i1 such that Next*(n1,21)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 67" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 68 */

	query = declaration + "Select i1 such that Next*(23,21)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 68" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 69 */

	query = declaration + "Select i1 such that Next*(23,22)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 69" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 70 */

	query = declaration + "Select i1 such that Next*(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 70" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 71 */

	query = declaration + "Select i1 such that Next*(30,_)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 71" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 72 */

	query = declaration + "Select i1 such that Next*(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 72" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 73 */

	query = declaration + "Select i1 such that Next*(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 73" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 74 */

	query = declaration + "Select i1 such that Next*(_,1)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 74" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 75 */

	query = declaration + "Select i1 such that Next*(_,_)";
	PQLParser::parse(query);
	result.push_back("15");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 75" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 76 */

	query = declaration + "Select w1 such that Next*(12,n1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 76" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 77 */

	query = declaration + "Select w1 such that Next*(2,2)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 77" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 78 */

	query = declaration + "Select w1 such that Next*(n1,21)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 78" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 79 */

	query = declaration + "Select w1 such that Next*(23,21)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 79" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 80 */

	query = declaration + "Select w1 such that Next*(23,22)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 80" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 81 */

	query = declaration + "Select w1 such that Next*(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 81" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 82 */

	query = declaration + "Select w1 such that Next*(30,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 82" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 83 */

	query = declaration + "Select w1 such that Next*(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 83" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 84 */

	query = declaration + "Select w1 such that Next*(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 84" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 85 */

	query = declaration + "Select w1 such that Next*(_,1)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 85" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 86 */

	query = declaration + "Select w1 such that Next*(_,_)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("11");
	result.push_back("21");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 86" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 87 */

	query = declaration + "Select ca1 such that Next*(12,n1)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 87" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 88 */

	query = declaration + "Select ca1 such that Next*(2,2)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 88" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 89 */

	query = declaration + "Select ca1 such that Next*(n1,21)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 89" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 90 */

	query = declaration + "Select ca1 such that Next*(23,21)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 90" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 91 */

	query = declaration + "Select ca1 such that Next*(23,22)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 91" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 92 */

	query = declaration + "Select ca1 such that Next*(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 92" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 93 */

	query = declaration + "Select ca1 such that Next*(30,_)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 93" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 94 */

	query = declaration + "Select ca1 such that Next*(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 94" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 95 */

	query = declaration + "Select ca1 such that Next*(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 95" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 96 */

	query = declaration + "Select ca1 such that Next*(_,1)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 96" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 97 */

	query = declaration + "Select ca1 such that Next*(_,_)";
	PQLParser::parse(query);
	result.push_back("5");
	result.push_back("20");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 97" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 98 */

	query = declaration + "Select v1 such that Next*(12,n1)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 98" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 99 */

	query = declaration + "Select v1 such that Next*(2,2)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 99" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 100 */

	query = declaration + "Select v1 such that Next*(n1,21)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 100" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 101 */

	query = declaration + "Select v1 such that Next*(23,21)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 101" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 102 */

	query = declaration + "Select v1 such that Next*(23,22)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 102" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 103 */

	query = declaration + "Select v1 such that Next*(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 103" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 104 */

	query = declaration + "Select v1 such that Next*(30,_)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 104" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 105 */

	query = declaration + "Select v1 such that Next*(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 105" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 106 */

	query = declaration + "Select v1 such that Next*(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 106" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 107 */

	query = declaration + "Select v1 such that Next*(_,1)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 107" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 108 */

	query = declaration + "Select v1 such that Next*(_,_)";
	PQLParser::parse(query);
	result.push_back("i");
	result.push_back("j");
	result.push_back("x");
	result.push_back("z");
	result.push_back("y");
	result.push_back("k");
	result.push_back("l");
	result.push_back("a");
	result.push_back("b");
	result.push_back("c");
	result.push_back("d");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 108" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 109 */

	query = declaration + "Select p1 such that Next*(12,n1)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 109" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 110 */

	query = declaration + "Select p1 such that Next*(2,2)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 110" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 111 */

	query = declaration + "Select p1 such that Next*(n1,21)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 111" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 112 */

	query = declaration + "Select p1 such that Next*(23,21)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 112" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 113 */

	query = declaration + "Select p1 such that Next*(23,22)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 113" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();	


	/* Test 114 */

	query = declaration + "Select p1 such that Next*(17,18)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 114" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();	


	/* Test 115 */

	query = declaration + "Select p1 such that Next*(30,_)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 115" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();	


	/* Test 116 */

	query = declaration + "Select p1 such that Next*(31,_)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 116" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();	


	/* Test 117 */

	query = declaration + "Select p1 such that Next*(_,28)";
	PQLParser::parse(query);

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 117" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();	


	/* Test 118 */

	query = declaration + "Select p1 such that Next*(_,1)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 118" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();	


	/* Test 119 */

	query = declaration + "Select p1 such that Next*(_,_)";
	PQLParser::parse(query);
	result.push_back("Alpha");
	result.push_back("Beta");
	result.push_back("Gamma");
	result.push_back("Caller");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 119" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 120 */

	query = declaration + "Select BOOLEAN such that Next*(3,n1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 120" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 121 */

	query = declaration + "Select BOOLEAN such that Next*(6,1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 121" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 122 */

	query = declaration + "Select BOOLEAN such that Next*(10,n1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 122" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 123 */

	query = declaration + "Select BOOLEAN such that Next*(12,n1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 123" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 124 */

	query = declaration + "Select BOOLEAN such that Next*(6,2)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 124" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 125 */

	query = declaration + "Select BOOLEAN such that Next*(2,2)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 125" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 126 */

	query = declaration + "Select BOOLEAN such that Next*(n1,21)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 126" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 127 */

	query = declaration + "Select BOOLEAN such that Next*(17,18)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 127" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 128 */

	query = declaration + "Select BOOLEAN such that Next*(30,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 128" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 129 */

	query = declaration + "Select BOOLEAN such that Next*(31,_)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 129" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 130 */

	query = declaration + "Select BOOLEAN such that Next*(_,28)";
	PQLParser::parse(query);
	result.push_back("false");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 130" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 131 */

	query = declaration + "Select BOOLEAN such that Next*(_,1)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 131" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 132 */

	query = declaration + "Select BOOLEAN such that Next*(_,_)";
	PQLParser::parse(query);
	result.push_back("true");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 132" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 133 */

	query = declaration + "Select n1 such that Next*(7,n1)";
	PQLParser::parse(query);
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 133" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();


	/* Test 134 */

	query = declaration + "Select n1 such that Next*(12,12)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");
	result.push_back("10");
	result.push_back("11");
	result.push_back("12");
	result.push_back("13");
	result.push_back("14");
	result.push_back("15");
	result.push_back("16");
	result.push_back("17");
	result.push_back("18");
	result.push_back("19");
	result.push_back("20");
	result.push_back("21");
	result.push_back("22");
	result.push_back("23");
	result.push_back("24");
	result.push_back("25");
	result.push_back("26");
	result.push_back("27");
	result.push_back("28");
	result.push_back("29");
	result.push_back("30");
	result.push_back("31");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 134" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();

	/* Test 135 */

	query = declaration + "Select s1 such that Next*(s1,10)";
	PQLParser::parse(query);
	result.push_back("1");
	result.push_back("2");
	result.push_back("3");
	result.push_back("4");
	result.push_back("5");
	result.push_back("6");
	result.push_back("7");
	result.push_back("8");
	result.push_back("9");

	try {
		ans = QueryEvaluator::evaluate();
	} catch (exception&e) {
		cout << e.what() << endl;
		cout << "Test 135" << endl;
	}

	CPPUNIT_ASSERT(ans == result);
	result.clear();



	cout<< "SUCCESS! testNextTransitive!! :D" <<endl;
}