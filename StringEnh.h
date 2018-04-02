/*
 * StringEnh.h
 *
 *  Created on: Mar 2, 2017
 *      Author: Joe
 */

#ifndef STRING_ENH_H_
#define STRING_ENH_H_

#include <string>
#include <vector>

/**
 * The StringEnh class provides enhanced string functionality not available in the Standard Library string class
 */
class StringEnh {
public:
	// Trim string of leading and trailing whitespace
	static std::string trim(const std::string &str);

	// Tokenize string (break into vector of strings based on token/delimiter)
	static std::vector<std::string> tokenize(const std::string &str, const char *tokens);
	static std::vector<std::string> tokenize(const std::string &str, const std::string &tokens);

private:
	// Default constructor (use private to prevent creation)
	StringEnh();
};

#endif /* STRING_ENH_H_ */
