#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "../lib/cxxopts.hpp"

using namespace std;
using namespace cxxopts;

vector<string> load_modes();
Options load_options(string &program_name);
string help_msg(vector<string> &modes, Options &options);

string current_version();
bool is_number(const string &s);
string handle_mode(string &mode, vector<string> &modes);

string current_version()
{
	string res = "My bare-bones C compiler (for COM 440/540)\n";
	res += "\tWritten by Yijia Huang (hyj@iastate.edu)\n";
	res += "\tVersion 0.1\n";
	res += "\t30 January, 2021\n";
	return res;
}

vector<string> load_modes()
{
	// The mode is an integer from 0 to 5, and corresponds to each part of the project.
	return {
		"Version information",
		"Part 1 (not implemented yet)",
		"Part 2 (not implemented yet)",
		"Part 3 (not implemented yet)",
		"Part 4 (not implemented yet)",
		"Part 5 (not implemented yet)"};
}

Options load_options(string &program_name)
{
	Options options(program_name);
	options
		.custom_help("-mode [options] infile")
		.show_positional_help()
		.allow_unrecognised_options();

	options.add_options()("o", "write to outfile instead of standard output", value<string>(), "outfile");
	return options;
}

string help_msg(vector<string> &modes, Options &options)
{
	string output = "Usage:\n\t./mycc -mode [options] infile\n\n";

	output += "Valid modes:\n";
	int i = 0;
	for (string &desc : modes)
	{
		output += "\t-" + to_string(i++) + ": " + desc + '\n';
	}
	output += '\n';

	output += "Valid options:\n";
	for (HelpOptionDetails detail : options.group_help("").options)
	{
		output += "\t-" + detail.s;
		if (!detail.arg_help.empty())
		{
			output += ' ' + detail.arg_help;
		}
		output += ": " + detail.desc + '\n';
	}
	return output;
}

bool is_number(const string &s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it))
		++it;
	return !s.empty() && it == s.end();
}

#endif