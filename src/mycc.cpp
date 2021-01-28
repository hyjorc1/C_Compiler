#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "../include/util.h"
#include <cxxopts.hpp>

using namespace std;
using namespace cxxopts;

int main(int argc, char *argv[])
{

	cout << "You have entered " << argc
		 << " arguments:"
		 << "\n";

	for (int i = 0; i < argc; ++i)
		cout << argv[i] << endl;
	cout << endl;

	string program_name = argv[0];
	Options options = load_options(program_name);
	vector<string> modes = load_modes();

	try
	{
		string output;
		if (argc > 1)
		{
			string mode = argv[1];
			output = handle_mode(mode, modes);

			argc--;
			argv++;

			auto result = options.parse(argc, argv);
			if (result.count("o")) {
				cout << "output file: " + result["o"].as<string>() << endl;
			} else {
				cout << output << endl;
			}
		}
		else
		{
			throw OptionException("err");
		}

		auto result = options.parse(argc, argv);
		int options_size = result.arguments().size();
		cout << "current arg size " << options_size << endl;

		cout << "Arguments remain = " << (argc - 1) << endl;

		for (int i = 1; i < argc; ++i)
			cout << argv[i] << endl;
		cout << endl;
	}
	catch (const exception &e)
	{
		string msg = help_msg(modes, options);
		if (strcmp(e.what(), "err") == 0)
		{
			cerr << msg << '\n';
		}
	}

	return 0;
}
