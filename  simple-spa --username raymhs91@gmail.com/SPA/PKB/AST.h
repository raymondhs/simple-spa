/*
 * @author Raymond Hendy Susanto
 */

#pragma once

#include <vector>
#include <string>
#include "../PKB/TNode.h"
#include "../PQL/QNode.h"
#include "../Constants.h"

using namespace std;

class AST {
private:
	TNode *root;
	AST();
	AST(const AST &);
	AST& operator=(const AST &);

public:
	/**
	 * Gets the AST
	 *
	 * @return Reference to AST
	 */
	static AST* getAST();

	/**
	 * Sets the root of AST
	 *
	 * @param root The root of AST to be set
	 */
	void setRoot(TNode* root);

	/**
	 * Gets the root of AST
	 *
	 * @return The root of AST
	 */
	TNode* getRoot();

	/**
	 * Deletes this AST
	 */
	void destroy();

	/**
	 * returns true if node 1 contains node 2
	 *
	 * @return boolean
	 */
	bool contains(QNodeType t1, int v1, QNodeType t2, int v2);
};