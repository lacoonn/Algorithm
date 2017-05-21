// N Queen Problem with Monte Carlo Algorithm

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>

#define MAX_ARY 2000

void NQueen(int[], int, int);
bool isPromising(int[], int);

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

	srand(time(NULL));
	bool promising = true;
	while (!isFinish) {
		for (int i = 1; i < size - 4; i++) {
			for (int j = 1; j <= size; j++) {
				col[i] = rand() % size + 1;
				promising = isPromising(col, i);
				if (promising)
					break;
			}
			if (!promising)
				break;
		}
		// size - 5 까지 promising 할 경우에만 NQueen 함수 실행
		if (promising) {
			cout << "Random Complete" << endl;
			NQueen(col, size, size - 5);
		}
	}

	return 0;
}

void NQueen(int col[], int size, int index)
{

	if (isPromising(col, index) && !isFinish) {
		if (index == size) {
			// col[1] ~ col[n] 출력
			for (int i = 1; i <= size; i++) {
				fsout << col[i] << endl;
				cout << col[i] << endl;
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

bool isPromising(int col[], int index)
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
