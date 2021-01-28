#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cxxopts.hpp>

using namespace std;
using namespace cxxopts;

vector<string> load_modes();
Options load_options(string &program_name);
string help_msg(vector<string> &modes, Options &options);

string current_version();
bool is_number(const string &s);
string handle_mode(string &mode, vector<string> &modes);

#endif