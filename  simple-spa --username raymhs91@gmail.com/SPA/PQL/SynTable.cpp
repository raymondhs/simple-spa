#include "SynTable.h"

using namespace std;

SynTable::SynTable() { }

SynTable* SynTable::getSynTable(){
	static SynTable synTable;
	return &synTable;
}

void SynTable::clearTable(){
	idxMapper.clear();
	nameMapper.clear();
}

int SynTable::getSize() {
	return idxMapper.size();
}

int SynTable::insertSyn(std::string syn, int type) {
	int idx = getSynIdx(syn);
	if(idx == -1) {
		idx = nameMapper.size();
		nameMapper.insert(pair<string,int>(syn,idx));
		idxMapper.push_back(pair<string,int>(syn,type));
		return idx;
	} else {
		return -1;
	}
}

int SynTable::getSynIdx(std::string name) {
	if(nameMapper.count(name) != 0)
		return nameMapper[name];
	return -1;
}

std::pair<std::string,int> SynTable::getSyn(int idx) {
	return idxMapper[idx];
}