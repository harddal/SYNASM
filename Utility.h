//--------------------------------------------------------------------------------------
// File: Utility.h
//
// Provides functions to convert hex numbers and characters to binary
// as well as a function to split strings by whitespace and specified delimiters.
// 
//--------------------------------------------------------------------------------------

#ifndef _UTILITY_H
#define _UTILITY_H

#include <string>
#include <vector>

#include "LookupTable.h"

// Converts a hex string to a binary string
std::string hex_to_bin(std::string in);

// For DCO, converts strings in the *.asm file to seperate DCO commands
std::string process_string(std::string in, std::vector<std::string> &vec);

// Splits a string by whitespace and delimiters
void split(const std::string& str, const std::string& delimiters, std::vector<std::string>& tokens);

#endif