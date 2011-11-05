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
	QueryTree();
	QueryTree(const QueryTree &);
	QueryTree& operator=(const QueryTree &);
public:
	static QueryTree* getQueryTree();
	void addSuchThat(QNode* suchThat);
	void addPattern(QNode* pattern);
	void setResult(QNode* result);
	void setSuchThat(QNode* suchThat);
	void setWith(QNode* with);
	void setPattern(QNode* pattern);
	QNode* getResult();
	QNode* getSuchThat();
	QNode* getWith();
	QNode* getPattern();
	void clearTree();
	void destroy();
};