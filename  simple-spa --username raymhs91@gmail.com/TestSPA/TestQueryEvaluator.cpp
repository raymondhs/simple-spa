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
	declaration = "while w1,w2,w3,w4; assign a,a1,a2,a3,a4; stmt s,s#,s1,s2,s3,s4; variable v1,v2,v3,v4; prog_line n1, n2, n3,n4; constant c1, c2, c3,c4; ";
}

void TestQueryEvaluator::tearDown() {
	PKBParser::cleanUp();
}

CPPUNIT_TEST_SUITE_REGISTRATION( TestQueryEvaluator );

void TestQueryEvaluator::testFollows() {
	try {
		PKBParser::parse("testcases/testQuery.txt");
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

void TestQueryEvaluator::testFollowsT() {
	try {
		PKBParser::parse("testcases/testQuery.txt");
	} catch (exception& e) {
		cout << "PKBParser: " << e.what() << endl;
	}

	/* Test 1*/
	cout << "testFollows* = ";
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

void TestQueryEvaluator::testParent() {
	try {
		PKBParser::parse("testcases/testQuery.txt");
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

void TestQueryEvaluator::testParentT() {
	try {
		PKBParser::parse("testcases/testQuery.txt");
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

void TestQueryEvaluator::testModifies() {
	try {
		PKBParser::parse("testcases/testQuery.txt");
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

void TestQueryEvaluator::testUses() {
	try {
		PKBParser::parse("testcases/testQuery.txt");
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

void TestQueryEvaluator::testPattern() {
	try {
		PKBParser::parse("testcases/testQuery.txt");
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

void TestQueryEvaluator::testAnd(){
	try {
		PKBParser::parse("testcases/testQuery2.txt");
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

void TestQueryEvaluator::testWith(){
	try {
		PKBParser::parse("testcases/testQuery.txt");
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

	cout << "SUCCESS! testWith :p" <<endl;
}