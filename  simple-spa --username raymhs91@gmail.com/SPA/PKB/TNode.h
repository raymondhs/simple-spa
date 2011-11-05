/*
 * @author: Raymond Hendy Susanto
 */

#pragma once

#include <vector>
#include "../Constants.h"

class TNode {

private:
	NodeType type;
	int attrib;
	TNode* firstChild;
	TNode* leftSibling;
	TNode* rightSibling;
	TNode* upLink;
	TNode* parent;
	std::vector<TNode*> parented;
	TNode* follower;
	TNode* followed;
	void setParented(TNode* node);
	void init();
	void setFollower(TNode* node);
	void setFollowed(TNode* node);

public:
	/**
	 * Default class constructor
	 */
	TNode();

	/**
	 * Class constructor specifying the type
	 *
	 * @param type Type of the node
	 */	
	TNode(NodeType type);
	
	/**
	 * Class constructor specifying the type and its attribute
	 *
	 * @param type Type of the node
	 * @param attrib Attribute of the node
	 */
	TNode(NodeType type, int attrib);

	/**
	 * Class destructor
	 */
	~TNode();

	/**
	 * Sets the type of the node
	 *
	 * @param type Type of the node
	 */
	void setType(NodeType type);

	/**
	 * Sets the attribute of the node
	 *
	 * @param attrib Attribute of the node
	 */	
	void setAttrib(int attrib);

	/**
	 * Sets the first child of the node
	 *
	 * @param firstChild First child of the node
	 */
	void setFirstChild(TNode* firstChild);
	
	
	/**
	 * Sets the right sibling of the node
	 *
	 * @param rightSibling Right sibling of the node
	 */
	void setRightSibling(TNode* rightSibling);
	

	/**
	 * Sets the direct parent of the node (Parent relationship)
	 *
	 * @param parent Parent of the node
	 */
	void setParent(TNode* parent);
	
	/**
	 * Gets the type of the node
	 *
	 * @return Type of the node
	 */
	NodeType getType();

	/**
	 * Gets the attribute of the node
	 *
	 * @return Attribute of the node
	 */
	int getAttrib();

	/**
	 * Gets the first child of the node
	 *
	 * @return First child of the node
	 */
	TNode* getFirstChild();
	
	/**
	 * Gets the left sibling of the node
	 *
	 * @return Left sibling of the node
	 */
	TNode* getLeftSibling();

	/**
	 * Gets the right sibling of the node
	 *
	 * @return Right sibling of the node
	 */
	TNode* getRightSibling();
	
	/**
	 * Gets the up link of the node
	 *
	 * @return Up link of the node
	 */
	TNode* getUpLink();
	
	/**
	 * Gets the direct parent of the node (Parent relationship)
	 *
	 * @return Direct parent of the node
	 */
	TNode* getParent();

	/**
	 * Gets the children of the node (Parent relationship)
	 *
	 * @return Vector of children of the node
	 */
	std::vector<TNode*> getParentedBy();

	/**
	 * Returns true if and only if the relationship Parent(this,child) holds
	 *
	 * @param child The child node
	 * @return true if and only if the relationship Parent(this,child) holds
	 */
	bool isParent(TNode* child);

	/**
	 * Gets transitive parents of the node (Parent* relationship)
	 *
	 * @return Vector of transitive parents of the node
	 */
	std::vector<TNode*> getParentTransitive();
	
	/**
	 * Gets transitive children of the node (Parent* relationship)
	 *
	 * @return Vector of transitive children of the node
	 */
	std::vector<TNode*> getParentedByTransitive();

	/**
	 * Returns true if and only if the relationship Parent*(this,child) holds
	 *
	 * @param child The child node
	 * @return true if and only if the relationship Parent*(this,child) holds
	 */ 
	bool isParentTransitive(TNode* child);

	/**
	 * Gets the following node
	 *
	 * @return Reference to the node which is following node
	 */
	TNode* getFollows();

	/**
	 * Gets the node which the node follows 
	 *
	 * @return Reference to the node which node follows
	 */
	TNode* getFollowedBy();

	/**
	 * Returns true if and only if the relationship Follows(this,successor) holds
	 *
	 * @param successor The successor node
	 * @return true if and only if the relationship Follows(this,successor) holds
	 */
	bool isFollows(TNode* successor);

	/**
	 * Gets the nodes which follow (transitively) this node (Follows* relationship)
	 *
	 * @return Vector of nodes which follow (transitively) this node
	 */
	std::vector<TNode*> getFollowsTransitive();
	
	/**
	 * Gets the nodes which are followed by (transitively) this node (Follows* relationship)
	 *
	 * @return Vector of nodes which are followed by (transitively) this node
	 */
	std::vector<TNode*> getFollowedByTransitive();

	/**
	 * Returns true if and only if the relationship Follows*(this,successor) holds
	 *
	 * @param successor The successor node
	 * @return true if and only if the relationship Follows*(this,successor) holds
	 */
	bool isFollowsTransitive(TNode* successor);


	/**
	 * Overriding object equality function
	 */
	bool operator == (const TNode& t);

	// to be implemented:
	// call, if, minus, times nodes
};