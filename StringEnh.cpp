/*
 * StringEnh.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: Joe
 */

#include <string>
#include <vector>

#include "StringEnh.h"

static const char WHITE_SPACE[] = " \t\r\n";

/**
 * Trim string of leading and trailing whitespace
 */
std::string StringEnh::trim(const std::string &str)
{
	std::string emptyString;

	// If string not provided or is empty, just return an empty string
	if (str.empty())
		return emptyString;

	// Find first non-whitespace character, if all whitespace, just return an empty string
	std::string::size_type firstPos = str.find_first_not_of(WHITE_SPACE);
	if (firstPos == std::string::npos)
		return emptyString;

	// Find last non-whitespace character
	std::string::size_type lastPos = str.find_last_not_of(WHITE_SPACE);

	// Return trimmed string
	return str.substr(firstPos, lastPos - firstPos + 1);
}

/**
 * Tokenize string (break into vector of strings based on token/delimiter)
 */
std::vector<std::string> StringEnh::tokenize(const std::string &str, const char *tokens)
{
	std::vector<std::string> tokenizedString;

	// Trim leading/trailing whitespace from string
	std::string trimmedString = trim(str);
	if (trimmedString.empty())
		return tokenizedString;

	// Loop through string searching for a token
	std::string::size_type pos = 0, tokenPos;
	do {
		tokenPos = trimmedString.find_first_of(tokens, pos);

		// If token was not found, add remainder of string to vector
		//  otherwise, split string based on position of token and add to vector
		if (tokenPos == std::string::npos)
			tokenizedString.push_back(trimmedString.substr(pos, std::string::npos));
		else
			tokenizedString.push_back(trimmedString.substr(pos, tokenPos - pos));

		// Reposition starting position to first character following token
		pos = tokenPos + 1;
	} while (tokenPos != std::string::npos);

	// Return tokenized string (vector)
	return tokenizedString;
}

/**
 * Tokenize string (break into vector of strings based on token/delimiter)
 */
std::vector<std::string> StringEnh::tokenize(const std::string &str, const std::string &tokens)
{
	return tokenize(str, tokens.c_str());
}

/**
 * Default constructor (use private to prevent creation)
 */
StringEnh::StringEnh()
{
}
