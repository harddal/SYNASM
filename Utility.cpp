//--------------------------------------------------------------------------------------
// File: Utility.cpp
//
// Provides functions to convert hex numbers and characters to binary
// as well as a function to split strings by whitespace and specified delimiters.
//
//--------------------------------------------------------------------------------------

#include "Utility.h"

std::string hex_to_bin(std::string in)
{
	std::string bin, temp;
	std::string hex = in;

	// Remove the x or h from the hex number
	if (hex[1] == 'x' || hex[1] == 'X')
		hex.erase(0, 2);
	else if (hex.find("h") != -1)
	{
		int pos = hex.find("h");
		hex.erase(hex.begin() + pos, hex.end());
	}

	// Convert the hex number to binary
	for (int i = 0; i != hex.length(); ++i)
	{
		temp = hex[i];

		for (int j = 0; j < HEX_LOOKUP_TABLE.size(); j++)
		{
			if (temp == HEX_LOOKUP_TABLE[j])
			{
				bin += HEX_VALUE_LOOKUP_TABLE[j];
				break;
			}
		}
	}

	// Make sure the length is always 12 bits, if not, add some zeros
	if (bin.length() == 4)
		bin = "00000000" + bin;
	else if (bin.length() == 8)
		bin = "0000" + bin;

	return bin;
}

std::string process_string(std::string in, std::vector<std::string> &vec)
{
	int iter = 0;
	std::vector<std::string> chars;
	std::string charbin = "", temp = in;
	
	// Remove the '@' delimiter used in the assembly
	temp.erase(0, 1);

	// Convert the character stream to binary
	for (int j = 0; j != temp.length(); j++)
	{
		for (int k = 0; k < CHAR_LOOKUP_TABLE.size(); k++)
		{
			if (temp[j] == CHAR_LOOKUP_TABLE[k])
			{
				charbin = CHAR_VALUE_LOOKUP_TABLE[k];
				chars.push_back(charbin);

				break;
			}
		}
	}

	// Make sure the size is a multiple of 4, if not, add some filler bytes
	while (chars.size() % 4 != 0)
	{
		chars.push_back("010011");
	}

	// Write the formatted DCO command
	for (int j = 0; j < chars.size(); j += 4)
	{
		vec.push_back("10001");
		vec.push_back(chars[j + 3] + chars[j + 2]);
		vec.push_back(chars[j + 1] + chars[j]);
	}

	return in;
}

void split(const std::string& str, const std::string& delimiters, std::vector<std::string>& tokens)
{
	// Skip delimiters at the beginning
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

	// Find first non-delimiter
	std::string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		// Found a token, so add it to the vector
		tokens.push_back(str.substr(lastPos, pos - lastPos));

		// Skip the specified delimiters
		lastPos = str.find_first_not_of(delimiters, pos);

		// Find the next non-delimiter
		pos = str.find_first_of(delimiters, lastPos);
	}
}
