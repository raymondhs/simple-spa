#pragma once
#include <vector>
#include "../Constants.h"
#include <string>

class QNode {
private:
	QNodeType type;
	int intVal; // used in QNodeType QSYN QCONST
	std::string strVal; // used in QNodeType QSTRING
	QNode* leftChild;
	QNode* rightChild;
	QNode* leftSibling;
	QNode* rightSibling;
	QNode* upLink;
public:
	/**
	 * Initializes components of QNode
	 */
	void init();

	/**
	 * Constructor for QNode
	 */
	QNode();
	
	/**
	 * Destructor for QNode
	 */
	~QNode();

	/**
	 * Constructor for QNode with type specified
	 *
	 * @param type Type of QNode
	 */
	QNode(QNodeType type);

	/**
	 * Constructor for QNode with type, integer value and string value specified
	 *
	 * @param type Type of QNode
	 * @param intVal Integer value of QNode
	 * @param strVal String value of QNode
	 */
	QNode(QNodeType type, int intVal, std::string strVal);

	/**
	 * Sets the type of QNode
	 *
	 * @param type Type of Qnode
	 */
	void setType(QNodeType type);

	/**
	 * Sets integer value of QNode
	 *
	 * @param intVal Integer value of Qnode
	 */
	void setIntVal(int intVal);

	/**
	 * Sets string value of QNode
	 *
	 * @param intVal String value of Qnode
	 */
	void setStrVal(std::string strVal);

	/**
	 * Sets left child of QNode
	 *
	 * @param leftChild Reference to the left child of Qnode
	 */
	void setLeftChild(QNode* leftChild);
	
	/**
	 * Sets right child of QNode
	 *
	 * @param rightChild Reference to the right child of Qnode
	 */
	void setRightChild(QNode* rightChild);

	/**
	 * Sets right sibling of QNode
	 *
	 * @param rightSibling Reference to the right sibling of QNode
	 */
	void setRightSibling(QNode* rightSibling);

	/**
	 * Gets the type of QNode
	 *
	 * @return Type of QNode
	 */
	QNodeType getType();

	/**
	 * Gets the integer value of Qnode
	 *
	 * @return Integer value of QNode
	 */
	int getIntVal();
	
	/**
	 * Gets the string value of Qnode
	 *
	 * @return String value of QNode
	 */
	std::string getStrVal();

	/**
	 * Gets the left child of QNode
	 *
	 * @return Reference to the left child of QNode
	 */
	QNode* getLeftChild();
	
	/**
	 * Gets the right child of QNode
	 *
	 * @return Reference to the right child of QNode
	 */
	QNode* getRightChild();
		
	/**
	 * Gets the left sibling of QNode
	 *
	 * @return Reference to the left sibling of QNode
	 */
	QNode* getLeftSibling();
	
	/**
	 * Gets the right sibling of QNode
	 *
	 * @return Reference to the right sibling of QNode
	 */
	QNode* getRightSibling();
	
	/**
	 * Gets the uplink of QNode
	 *
	 * @return Reference to the uplink of QNode
	 */
	QNode* getUpLink();

	/**
	 * Overriding object equality function
	 */
	bool operator == (const QNode& t);
};