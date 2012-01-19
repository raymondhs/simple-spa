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
	/**
	 * Gets the reference to the query tree
	 *
	 * @return Reference to the query tree
	 */
	static QueryTree* getQueryTree();

	/**
	 * Adds a new "such that" condition to query tree
	 *
	 * @param suchThat Reference to "such that" condition
	 */
	void addSuchThat(QNode* suchThat);
	
	/**
	 * Adds a new "pattern" condition to query tree
	 *
	 * @param pattern Reference to "pattern" condition
	 */
	void addPattern(QNode* pattern);

	/**
	 * Adds a new "with" condition to query tree
	 *
	 * @param with Reference to "with" condition
	 */
	void addWith(QNode* with);

	/**
	 * Sets the "Select" sub-root
	 *
	 * @param result "Select" sub-root to be set
	 */
	void setResult(QNode* result);

	/**
	 * Sets the "such that" sub-root
	 *
	 * @param suchThat "such that" sub-root to be set
	 */
	void setSuchThat(QNode* suchThat);
	
	/**
	 * Sets the "with" sub-root
	 *
	 * @param suchThat "with" sub-root to be set
	 */
	void setWith(QNode* with);
	
	/**
	 * Sets the "pattern" sub-root
	 *
	 * @param suchThat "pattern" sub-root to be set
	 */
	void setPattern(QNode* pattern);

	/**
	 * Gets the "Select" sub-root
	 *
	 * @return Reference to the "Select" sub-root
	 */
	QNode* getResult();
	
	/**
	 * Gets the "such that" sub-root
	 *
	 * @return Reference to the "such that" sub-root
	 */
	QNode* getSuchThat();

	/**
	 * Gets the "with" sub-root
	 *
	 * @return Reference to the "with" sub-root
	 */
	QNode* getWith();
	
	/**
	 * Gets the "pattern" sub-root
	 *
	 * @return Reference to the "pattern" sub-root
	 */
	QNode* getPattern();

	/**
	 * Clears the query tree
	 */
	void clearTree();

	/**
	 * Destroys the query tree
	 */
	void destroy();
};