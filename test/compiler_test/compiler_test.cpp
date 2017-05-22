#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream input("scan.txt");
	int lineNum;
	string _token, _tokentype;

	while (1) {
		input >> lineNum >> _tokentype >> _token;
		if (input.eof())
			break;
		cout << lineNum << ' ' << _tokentype << ' ' << _token << endl;
	}


	return 0;
}