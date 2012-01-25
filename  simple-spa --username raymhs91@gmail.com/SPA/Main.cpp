#include <iostream>
#include <fstream>
#include <vector>
#include "PKB/PKBParser.h"
#include "PQL/PQLParser.h"
#include "PQL/QueryEvaluator.h"

using namespace std;

void printResult(vector<string> result);
void printExit();
void printAssign();

int main() {
	string fileName = "../TestSPA/testcases/testQuery.txt";
	cout << "################################" << endl;
	cout << "#     SPA Prototype v1.0.0     #" << endl;
	cout << "#            Team 3            #" << endl;
	cout << "################################" << endl;
	cout << endl;

	while(true) {
		cout << ">> Please input full path to SIMPLE source code: ('0' to exit)" << endl;
		getline (cin,fileName);
		if(fileName == "0") { printExit(); return 0; }
		try {
			PKBParser::parse(fileName);
			cout << "Parse OK." << endl << endl;
			break;
		} catch (exception& e)
		{	
			cout << e.what() << endl << endl;
		}
	}

	printAssign();

	string q; vector<string> result;
	cout << ">> Enter PQL queries ('0' to exit)" << endl;
	while(true){
		cout << ">> ";
		getline (cin,q);
		if(q == "0") { printExit(); return 0; }
		try {
			/*string decl = "while w1,w2; assign a1,a2; stmt s1,s2; variable v1, v2; prog_line n1, n2; constant c1, c2; ";
			string st = "Select w1 such that Uses(w1,\"x\") and Uses(w1,\"i\") and Parent(w1,w2)";
			string qq = decl + st;*/
			cout << q <<endl;
			PQLParser::parse(q);
			printResult(QueryEvaluator::evaluate());
		} catch (exception& e) {
			cout << e.what() << endl;
		}
		cout << endl;
	}
	PKBParser::cleanUp();
	printExit();
	return 0;
}

void printResult(vector<string> result) {
	if(result.size() == 0) cout << "none" << endl;
	else {
		for(unsigned i = 0; i < result.size(); i++) {
			cout << result[i] << " ";
		}
		cout << endl;
	}
}

void printExit() {
	cout << "GOOD BYE!" << endl;
}

void printAssign(){
	PKBParser::getAssign();
}