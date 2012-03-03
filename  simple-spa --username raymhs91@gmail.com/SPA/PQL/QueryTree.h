#pragma once 

#include <map>
#include "QNode.h"

using namespace std;

class QueryTree
{
private:
	QNode *result;
	QNode *suchThat;
	QNode *with;
	QNode *pattern;
	bool isBooleanAnswer;
	vector<QNode*> tuple;
	vector<QNode*> booleanQueries;
	vector< vector<QNode*> > dependencyGraph;
	QueryTree();
	QueryTree(const QueryTree &);
	QueryTree& operator=(const QueryTree &);
public:
	/**
	 * Gets the reference to the query tree
	 *
	 * @return Reference to the query tree
	 */
	static QueryTree* getQueryTree();

	void addClause(QNode* clause);

	vector<QNode*> nextClauses();

	vector<QNode*> getTuple();

	bool isBoolean();

	/**
	 * Clears the query tree
	 */
	void clearTree();

	/**
	 * Destroys the query tree
	 */
	void destroy();
};