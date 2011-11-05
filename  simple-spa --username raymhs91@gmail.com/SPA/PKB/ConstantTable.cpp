/*
 * @author: Jessinca
 */
#include "ConstantTable.h"
#include <queue>

ConstantTable::ConstantTable() {}

ConstantTable* ConstantTable::getConstantTable(){
	static ConstantTable consTable;
	return &consTable;
}

void ConstantTable::clearTable() {
	constantsList.clear();
}

void ConstantTable::addConstant(TNode* constant) {
	constantsList.insert(constant->getAttrib());
}

std::vector<int> ConstantTable::getAllConstant() {
	return std::vector<int> (constantsList.begin(),constantsList.end());
}