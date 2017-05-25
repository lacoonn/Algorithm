// N Queen Problem with Deterministic Algorithm

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#define MAX_ARY 1000

void NQueen(int[], int, int);
bool isPromising(int[], int, int);

using namespace std;

ifstream fsin;
ofstream fsout;
bool isFinish = false;

int main()
{
	cout << "Input File Name? ";
	string InputFileName;
	cin >> InputFileName;

	fsin.open(InputFileName, ifstream::in);
	fsout.open("output.txt", ofstream::out);

	int col[MAX_ARY];
	int size;
	fsin >> size;
	NQueen(col, size, 0);


	return 0;
}

void NQueen(int col[], int size, int index)
{

	if (isPromising(col, size, index) && !isFinish) {
		if (index == size) {
			// col[1] ~ col[n] Ãâ·Â
			for (int i = 1; i <= size; i++) {
				fsout << col[i] << endl;
			}
			isFinish = true;
		}
		else {
			for (int j = 1; j <= size; j++) {
				col[index + 1] = j;
				NQueen(col, size, index + 1);
			}
		}
	}
}

bool isPromising(int col[], int size, int index)
{
	int k = 1;
	bool promising = true;
	while (k < index && promising) {
		if (col[index] == col[k] || abs(col[index] - col[k]) == abs(index - k))
			promising = false;
		k++;
	}
	return promising;
}