#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "../include/mycc.h"
#include "../include/test.h"

using namespace std;

int test_num = 0;

void test_main(const char *input) {
    vector<string> result;
    string s(input);
    istringstream iss(s);
    for (string s; iss >> s;)
        result.push_back(s);
    int idx = 0, size = result.size();
    char **argv = new char *[size + 1];
    for (string s: result)
        argv[idx++] = strdup(s.c_str());
    cout << "Test " << test_num++ << endl;
    cout << "Command: " << input << endl; 
    cout << "------------- Output Start -------------" << endl;
    main(size, argv);
    cout << "------------- Output End -------------\n" << endl;
}

int unit_test()
{
    cout << "Start Unit Test\n" << endl;

    cout << "################### PART 0 ###################" << endl;
    test_main("./mycc");
    test_main("./mycc -0");
    test_main("./mycc -0 -o out.txt");
    test_main("./mycc -1 input.txt");
    test_main("./mycc -1 -o out.txt input.txt");
    
    test_main("./mycc -");
    test_main("./mycc -7");
    test_main("./mycc -1");
    return 0;
}