#pragma once
#include <string>

class PQLParser
{
public:
	/**
	 * Parses a PQL query
	 */
	static void parse(std::string query);

	/**
	 * Cleans up the data used for a query
	 */
	static void cleanUp();
};