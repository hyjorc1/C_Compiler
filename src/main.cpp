#include <iostream>
#include "../include/f.h"
#include <vector>

using namespace std;

int main()
{
	cout << "\nHello world!\n"
		 << endl;

	vector<int> vec{10, 20, 30};

	for (int x : vec)
		cout << x << " ";

	cout << " " << endl;

	return 0;
}
