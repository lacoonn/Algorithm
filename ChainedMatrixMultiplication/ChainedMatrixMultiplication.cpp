#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void minMult(int n, int *d, int **M, int **P);
void getMin(int left, int right, int *d, int **M, int **P);
void printOrder(int i, int j, int ** P);
ofstream outStream("output.txt");

int main()
{
	int n, *d, **M, **P;
	string inputFile;
	cout << "input file name? ";
	cin >> inputFile;
	ifstream inStream(inputFile);
	

	inStream >> n;
	d = new int[n];
	M = new int *[n];
	P = new int *[n];
	for (int i = 0; i < n; i++) {
		M[i] = new int[n];
		P[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		inStream >> d[i];
		cout << d[i] << ' ';
	}

	minMult(n, d, M, P);
	printOrder(1, n - 1, P);

	// delete array
	for (int i = 0; i < n; i++) {
		delete[] M[i];
		delete[] P[i];
	}
	delete[] d;
	delete[] M;
	delete[] P;

	return 0;
}

void minMult(int n, int *d, int **M, int **P)
{
	for (int i = 1; i < n; i++)
		M[i][i] = 0;
	for (int diagonal = 1; diagonal < n - 1; diagonal++) {
		for (int i = 1; i < n - diagonal; i++) {
			int j = i + diagonal;
			getMin(i, j, d, M, P);
		}
	}
}

void getMin(int left, int right, int *d, int **M, int **P) {
	/*
	1~5
	11 25
	12 35 => M[1][2] + M[3][5] + d[0] * d[2] * d[5]
	13 45
	14 55
	*/
	int k = left, temp, min = 0;

	for (int i = left; i < right; i++) {
		temp = M[left][i] + M[i + 1][right] + d[left - 1] * d[i] * d[right];
		if (min == 0)
			min = temp;
		if (temp < min) {
			min = temp;
			k = i;
		}
	}
	M[left][right] = min;
	P[left][right] = k;
}

void printOrder(int i, int j, int ** P)
{
	if (i == j)
		outStream  << i << ' ';
	else {
		int k = P[i][j];
		outStream << "( ";
		printOrder(i, k, P);
		printOrder(k + 1, j, P);
		outStream << " )";
	}
}