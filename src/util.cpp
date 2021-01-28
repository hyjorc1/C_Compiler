#include "../include/util.h"

vector<string> load_modes()
{
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

	options.add_options()("o", "write to outfile instead of standard output", value<string>()->default_value("std.out"), "outfile");
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

string current_version()
{
	string res = "My bare-bones C compiler (for COM 440/540)\n";
	res += "\tWritten by Yijia Huang (hyj@iastate.edu)\n";
	res += "\tVersion 0.1\n";
	res += "\t30 January, 2021\n";
	return res;
}

bool is_number(const string &s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it))
		++it;
	return !s.empty() && it == s.end();
}

string handle_mode(string &mode, vector<string> &modes)
{
	if (mode.length() <= 1 || mode.at(0) != '-' || !is_number(mode.substr(1)))
		throw OptionException("err");

	int x;
	sscanf(mode.substr(1).c_str(), "%d", &x);
	int size = static_cast<int>(modes.size());
	if (x < 0 || x >= size)
		throw OptionException("err");

	if (x == 0)
		return current_version();
	return modes.at(x);
}