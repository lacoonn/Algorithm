// 0/1 Napsack Problem with Backtracking

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

// Macro
#define MAX_ARY 2000

// Function Prototype
void knapsack(int, int, int);
bool isPromising(int, int, int);


// Global Variable
ifstream fsin;
ofstream fsout;
int w[MAX_ARY];
int p[MAX_ARY];
bool include[MAX_ARY];
bool bestset[MAX_ARY];
int W;
int n;
int numbest = 0, maxprofit = 0;
//bool isFinish = false;


int main()
{
	cout << "Input File Name? ";
	string InputFileName;
	cin >> InputFileName;

	fsin.open(InputFileName, ifstream::in);
	fsout.open("output.txt", ofstream::out);


	fsin >> n >> W;
	for (int i = 1; i <= n; i++) {
		fsin >> p[i] >> w[i];
	}

	knapsack(0, 0, 0);

	fsout << "maxprofit: " << maxprofit << endl;
	for (int i = 1; i <= n; i++) {
		fsout << bestset[i] << endl;
	}

	return 0;
}

void knapsack(int i, int profit, int weight)
{
	if (i > n)
		return;
	if (weight <= W && profit > maxprofit) {
		maxprofit = profit;
		numbest = i;
		//bestset = include
		for (int j = 1; j <= n; j++) {
			bestset[j] = include[j];
		}
	}
	if (isPromising(i, profit, weight)) {
		include[i + 1] = true;
		knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		include[i + 1] = false;
		knapsack(i + 1, profit, weight);
	}
}

bool isPromising(int i, int profit, int weight)
{
	bool promising = true;
	if (weight >= W)
		promising = false;
	else {
		int j = i + 1;
		int bound = profit;
		//int totweight = weight;
		int totalweight = weight;
		//while (j <= n && totweight + w[j] <= W) {
		while (j <= n && totalweight + w[j] <= W) {
			totalweight = totalweight + w[j];
			bound = bound + p[j];
			j++;
		}
		//d
		int k = j;
		if (k <= n) {
			bound = bound + (W - totalweight) * p[k] / w[k];

			if (bound > maxprofit)
				return true;
			else
				return false;
		}
		else {
			return false;
		}
		//d
	}
	return promising;
}