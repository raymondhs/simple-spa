/*
 * @author Raymond Hendy Susanto
 */

#pragma once

#include <vector>
#include <string>
#include "../PKB/TNode.h"
#include "../PQL/QNode.h"

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
};