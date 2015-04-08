//--------------------------------------------------------------------------------------
// File: Main.cpp
//
// Main file.
//
//--------------------------------------------------------------------------------------

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#include "LookupTable.h"
#include "Utility.h"

using namespace std;

int main()
{
	// User input and ifsteam input strings
	bool error = false;
	int errorcount = 0;
	string in, filehandle, str;

	// Vector to hold binary instructions and assembly tokens
	vector<string> bin_stack, tokens;

	// Display text and get user input
	SetTextColor("grey");
	cout << "\n" << "------------------------------ SYNASM Assembler --------------------------------";
	cout << "\nEnter file to assemble (*.scm): "; 
	cin >> in;

	// Open assembly file
	ifstream fin(in);
	while (true)
	{
		if (!fin)
		{
			cout << "\nError opening file, enter file to assemble: ";
			cin >> in;
			fin.open(in);
		}
		else
			break;
	}

	filehandle = in;

	cout << DASHED_LINE;

	// Split lines into tokens for assembling
	while (getline(fin, str))
	{
		stringstream ss("");
		
		// Remove comments
		int pos = str.find(";");
		if (pos != -1)
			str.erase(str.begin() + pos, str.end());

		if (str[0] == 'J')
		{
			tokens.push_back(str);
			continue;
		}

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

	// Remove commas from the second argument, ignoring commas in strings
	for (int i = 0; i < tokens.size(); i++)
	{
		int pos = tokens[i].find(",");
		int isStr = tokens[i].find("@");

		// Don't erase the comma in jump commands, process_jump() handles that
		if (pos != -1 && isStr == -1 && tokens[i][0] != 'J')
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
			if (tokens[i][0] == 'J') // Let process_jump() handle jump commands
			{
				process_jump(tokens[i], bin_stack);
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
		else if (tokens[i][1] = 'x' || tokens.back() == "h")
			bin_stack.push_back(hex_to_bin(tokens[i]));
		
	}

	// Check if program size exceeds the amount of ROM (889)
	if ((bin_stack.size() / 3) > 889)
	{
		SetTextColor("lightred");
		cout << "[ERROR] ";
		SetTextColor("grey");
		cout << " Program size exceeded 889 instructions, program was not assembled.";
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
		try
		{
			fout << bin_stack.at(i) << bin_stack.at(i + 1) << bin_stack.at(i + 2) << "\n";
		}
		catch (const out_of_range& oor)
		{
			error = true;
			errorcount++;

			SetTextColor("lightred");
			cout << "[ERROR] ";
			SetTextColor("grey");

			cerr << oor.what() << "\n";
			cout << " - Cause: Missing or invalid instruction(s) in " << filehandle << "\n\n";
		}
	}
	fout.close();

	// Display some statistics
	SetTextColor("lightgreen");
	cout << "[INFO]";
	SetTextColor("grey");
	cout << " Binary Instructions: " << bin_stack.size() / 3 << "\n";
	SetTextColor("lightgreen");
	cout << "[INFO]";
	SetTextColor("grey");
	cout << " Program Size: " << (bin_stack.size() / 3) * 29 << " bits";

	// Display the status of the output
	if (error)
	{
		SetTextColor("lightyellow");
		cout << "\n\n[WARNING]";
		SetTextColor("grey");
		cout << " Errors were detected, the assembled file may not function properly\n";
		cout << "\nProgram assembled to file " + in << " with " << errorcount << " error(s)";
	}
	else
	{
		cout << "\n\nProgram successfully assembled to file " + in;
	}

	std::cin >> in;

	return 0;
}
