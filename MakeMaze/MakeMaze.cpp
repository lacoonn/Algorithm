#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

typedef struct coordinate {
	int x;
	int y;
} cdn;

#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define UP 4

ofstream outStream("output.txt");

cdn getMin(int n, int **M, int **T, int **L);
void makePath(int n, int **M, int **T, int **L);
void getPath(int n, int **T, cdn near);

int main()
{
	int n, **M, **T, **L;
	string inputFile;
	cout << "input file name? ";
	cin >> inputFile;
	ifstream inStream(inputFile);


	inStream >> n;

	// dynamic allocation and get maze
	M = new int*[n];
	T = new int*[n];
	L = new int*[n];
	for (int i = 0; i < n; i++) {
		M[i] = new int[n];
		T[i] = new int[n];
		L[i] = new int[n];
	}
	char temp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			inStream >> temp;
			if (temp == '0')
				M[i][j] = 1;
			else if (temp == '1')
				M[i][j] = 0;
			else
				cout << "Maze Error : There is number not 0 or 1" << endl;
		}
	}

	// init Length
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			L[i][j] = 9999;
	L[0][0] = 0;

	T[0][0] = 0;

	makePath(n, M, T, L);
	outStream << L[n - 1][n - 1] << endl;

	
	//print Touch
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (T[i][j] == 0)
				outStream << 'H';
			else if (T[i][j] == 1)
				outStream << 'R';
			else if (T[i][j] == 2)
				outStream << 'D';
			else if (T[i][j] == 3)
				outStream << 'L';
			else if (T[i][j] == 4)
				outStream << 'U';
			else
				outStream << 'E';
		}
		outStream << endl;
	}
	
	cdn temp_cdn = { n - 1, n - 1 };
	getPath(n, T, temp_cdn);

	// delete array
	for (int i = 0; i < n; i++) {
		delete[] M[i];
		delete[] T[i];
		delete[] L[i];
	}
	delete[] M;
	delete[] T;
	delete[] L;

	return 0;
}

void makePath(int n, int **M, int **T, int **L)
{
	cdn near = { 0, 0 };
	cdn right, down, left, up;
	int temp;

	while (near.x != n - 1 || near.y != n - 1) {
		// change T, L in 4 direction
		right = { near.x + 1, near.y };
		down = { near.x, near.y + 1 };
		left = { near.x - 1, near.y };
		up = { near.x, near.y - 1 };
		if (right.x < n && L[right.y][right.x] >= 0) { // RIGHT
			temp = L[near.y][near.x] + M[right.y][right.x];
			if (temp < L[right.y][right.x]) {
				L[right.y][right.x] = temp;
				T[right.y][right.x] = LEFT;
			}
		}
		if (down.y < n && L[down.y][down.x] >= 0) { // DOWN
			temp = L[near.y][near.x] + M[down.y][down.x];
			if (temp < L[down.y][down.x]) {
				L[down.y][down.x] = temp;
				T[down.y][down.x] = UP;
			}
		}
		if (left.x >= 0 && L[left.y][left.x] >= 0) { // LEFT
			temp = L[near.y][near.x] + M[left.y][left.x];
			if (temp < L[left.y][left.x]) {
				L[left.y][left.x] = temp;
				T[left.y][left.x] = RIGHT;
			}
		}
		if (up.y >= 0 && L[up.y][up.x] >= 0) { // UP
			temp = L[near.y][near.x] + M[up.y][up.x];
			if (temp < L[up.y][up.x]) {
				L[up.y][up.x] = temp;
				T[up.y][up.x] = DOWN;
			}
		}

		// Error Test
		//cout << "Now Processing : " << near.x << ' ' << near.y << endl;

		// move near to smallest coordinate
		L[near.y][near.x] = -1;
		near = getMin(n, M, T, L);

	}
}

cdn getMin(int n, int **M, int **T, int **L)
{
	cdn min = { -1, -1 };
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (L[j][i] >= 0 && min.x < 0)
				min = { i, j };
			if (L[j][i] >= 0 && L[j][i] < L[min.y][min.x])
				min = { i, j };
		}
	}
	return min;
}

void getPath(int n, int **T, cdn near)
{
	cdn temp;
	if (T[near.y][near.x] == 0) {
		outStream << near.x + 1 << ' ' << near.y + 1 << endl;
		return;
	}
	else if (T[near.y][near.x] == RIGHT)
		getPath(n, T, temp = { near.x + 1, near.y });
	else if (T[near.y][near.x] == DOWN)
		getPath(n, T, temp = { near.x, near.y + 1 });
	else if (T[near.y][near.x] == LEFT)
		getPath(n, T, temp = { near.x - 1, near.y });
	else if (T[near.y][near.x] == UP)
		getPath(n, T, temp = { near.x, near.y - 1 });
	else {
		cout << "Error : getPath()" << endl;
		exit(1);
	}
	outStream << near.x + 1 << ' ' << near.y + 1 << endl;
}

/*
8
11100110
11010010
10011010
11101100
01000111
00110001
11011000
11000111
*/