/*
 * @author Raymond Hendy Susanto
 */

#pragma once
#include <string>

using namespace std;
class PKBParser{
public:
	/**
	* Parses the given SIMPLE source code
	*
	* @param fileName The file name of SIMPLE source code
	*/
	static void parse(string fileName);

	/**
	* Clear PKB database
	*/
	static void cleanUp();
};