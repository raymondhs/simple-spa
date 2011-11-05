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
	void init();
	QNode();
	~QNode();
	QNode(QNodeType type);
	QNode(QNodeType type, int intVal, std::string strVal);

	void setType(QNodeType type);
	void setIntVal(int intVal);
	void setStrVal(std::string strVal);
	void setLeftChild(QNode* leftChild);
	void setRightChild(QNode* rightChild);
	void setRightSibling(QNode* rightSibling);

	QNodeType getType();
	int getIntVal();
	std::string getStrVal();
	QNode* getLeftChild();
	QNode* getRightChild();
	QNode* getLeftSibling();
	QNode* getRightSibling();
	QNode* getUpLink();

	bool operator == (const QNode& t);
};