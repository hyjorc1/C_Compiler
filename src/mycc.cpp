#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "../include/util.h"
#include "../include/mycc.h"
#include "../include/test.h"
#include "../lib/cxxopts.hpp"

using namespace std;
using namespace cxxopts;

void write(string &content, string& path) {
	ofstream file;
	file.open(path);
	file << content + '\n';
	file.close();
}

int main(int argc, char *argv[])
{
	if (argc == 2 && strcmp(argv[1], "test") == 0) {
		unit_test();
		exit(0);
	}

	// cout << "You have entered " << argc
	// 	 << " arguments:"
	// 	 << "\n";

	// for (int i = 0; i < argc; ++i)
	// 	cout << argv[i] << endl;
	// cout << endl;


	string program_name = argv[0];
	Options options = load_options(program_name);
	vector<string> modes = load_modes();

	try
	{

		// If no arguments are given, display usage information to standard error.
		if (argc <= 1)
			throw OptionException("usage");

		// If mode argument is invalid, throw error.
		string mode_arg = argv[1];
		if (mode_arg.length() <= 1 || mode_arg.at(0) != '-' || !is_number(mode_arg.substr(1)))
			throw OptionException("usage");

		// If mode id is invalid, throw error
		int mode_id;
		sscanf(mode_arg.substr(1).c_str(), "%d", &mode_id);
		if (mode_id < 0 || mode_id >= static_cast<int>(modes.size()))
			throw OptionException("usage");

		auto result = options.parse(--argc, ++argv);

		string std_out; // standard output

		if (mode_id == 0)
		{
			std_out = current_version();
		}
		else
		{
			// For most modes, it is an error if no input files are specified.
			if (argc < 2)
				throw OptionException("For modes 1 to 5, please provide a input file.");

			for (int i = 1; i < argc; ++i) {
				std_out += "input file: " + string(argv[i]) + '\n';
			}
		}

		// If no output file is specified, then the output should be written to standard output
		if (result.count("o"))
		{
			string output_path = result["o"].as<string>();
			write(std_out, output_path);
		}
		else
		{
			cout << std_out << endl;
		}
	}
	catch (const exception &e)
	{
		if (strcmp(e.what(), "usage") == 0)
			cerr << help_msg(modes, options) << endl;
		else
			cerr << e.what() << endl;
	}

	return 0;
}