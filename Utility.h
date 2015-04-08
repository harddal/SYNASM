//--------------------------------------------------------------------------------------
// File: Utility.h
//
// Provides functions to convert hex numbers and characters to binary
// as well as a function to split strings by whitespace and specified delimiters.
// 
//--------------------------------------------------------------------------------------

#ifndef _UTILITY_H
#define _UTILITY_H

#define DASHED_LINE "\n--------------------------------------------------------------------------------\n"

#define NUL "000000000000"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "LookupTable.h"

// Splits a string by whitespace and delimiters
void split(const std::string& str, const std::string& delimiters, std::vector<std::string>& tokens);

// Converts a hex string to a binary string
std::string hex_to_bin(std::string in);

// For DCO, converts strings in the *.asm file to seperate DCO commands
std::string process_string(std::string in, std::vector<std::string> &vec);

// For JNE, JE, and JMP
std::string process_jump(std::string in, std::vector<std::string> &vec);

void SetTextColor(const char* szColor);

#endif