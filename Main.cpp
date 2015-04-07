//--------------------------------------------------------------------------------------
// File: Main.cpp
//
// Main file.
//
//--------------------------------------------------------------------------------------

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "LookupTable.h"
#include "Utility.h"

using namespace std;

int main()
{
	// User input and ifsteam input strings
	string in, str;

	// Vector to hold binary instructions and assembly tokens
	vector<string> bin_stack, tokens;

	// Display text and get user input
	cout << "--- SYNASM Assembler ---";
	cout << "\n\nEnter file to assemble: ";
	cin >> in;

	// Open assembly file
	ifstream fin(in);
	if (!fin)
		cout << "Error opening file, check if directory and filename are correct.";

	// Split lines into tokens for assembling
	while (getline(fin, str))
	{
		// Remove comments
		int pos = str.find(";");
		if (pos != -1)
			str.erase(str.begin() + pos, str.end());

		stringstream ss("");

		// Split commands and arguments by whitespace, strings by quotes
		for (size_t i = 0; i < str.length(); i++)
		{
			char c = str[i];
			if (c == ' ')
			{
				ss << ":";
			}
			else if (c == '\"')
			{
				i++;
				while (str[i] != '\"')
				{
					ss << str[i];
					i++;
				}
			}
			else
			{
				ss << c;
			}
		}
		split(ss.str(), ":", tokens);

		str = "";
	}

	// Remove commas from the second argument
	for (int i = 0; i < tokens.size(); i++)
	{
		int pos = tokens[i].find(",");

		if (pos != -1)
			tokens[i].erase(pos);
	}

	bool flag = false;

	// Assemble file to binary code
	for (int i = 0; i < tokens.size(); i++)
	{
		flag = false;

		// Convert instructions
		for (int j = 0; j < INSTRUCTION_LOOKUP_TABLE.size(); j++)
		{
			if (tokens[i] == "DCO") // Don't write DCO bits, process_string() does that
			{
				flag = true;
				break;
			}
			if (tokens[i] == INSTRUCTION_LOOKUP_TABLE[j])
			{
				bin_stack.push_back(INSTRUCTION_VALUE_LOOKUP_TABLE[j]);

				flag = true;
				break;
			}
		}
		if (flag) 
			continue;

		// Convert arguments
		if (tokens[i] == "NUL")
			bin_stack.push_back("000000000000");
		else if (tokens[i] == "EAX")
			bin_stack.push_back("000000000001");
		else if (tokens[i] == "EBX")
			bin_stack.push_back("000000000010");
		else if (tokens[i][0] == '@')
			process_string(tokens[i], bin_stack);
		else if (tokens[i][1] = 'x')
			bin_stack.push_back(hex_to_bin(tokens[i]));
		
	}

	bool error = false;

	if ((bin_stack.size() / 3) > 889)
	{
		error = true;
		cout << "\n\nERROR: Program size exceeded 889 instructions, program was not assembled.";
		std::cin >> in;
		return 1;
	}

	// Get file name to write from previous user input
	in.erase(in.end() - 3, in.end());
	in += "sc";

	// Create the output file (*.sc)
	ofstream fout;
	fout.open(in);

	// Write the instruction, argument a, argument b
	for (int i = 0; i < bin_stack.size(); i+=3)
	{
		fout << bin_stack[i] << bin_stack[i + 1] << bin_stack[i + 2] << "\n";
	}
	fout.close();

	// Display some statistics and tell user file was assembled
	cout << "\nBinary Instructions: " << bin_stack.size() / 3 << "\nProgram Size: " << (bin_stack.size() / 3) * 29 << " bits";
	cout << "\n\nProgram successfully assembled to file " + in;

	std::cin >> in;

	return 0;
}
