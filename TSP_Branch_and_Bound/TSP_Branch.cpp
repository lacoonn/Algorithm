// TSP Problem with Branch-and-Bound

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <queue>
#include <functional>

using namespace std;

// Macro
#define MAX_ARY 100
#define U_LIMIT 9000

// Global Variable
ifstream fsin;
ofstream fsout;
int W[MAX_ARY][MAX_ARY];
int n, minlength;
int opttour[MAX_ARY];

// Class Declaration
class Node {
public :
	int level;
	int path[MAX_ARY];
	int bound;

	Node()
	{

	}

	Node(int _level, int _path[], int _bound)
	{
		level = _level;
		//path = _path;
		bound = _bound;
	}

	void LastTwo()
	{
		//inPath(i, v.path, 0, v.level)
		for (int k = 1; k <= n; k++) {
			
			bool inPath = false;
			for (int i = 0; i < level; i++) {
				if (k == path[i]) {
					inPath = true;
					break;
				}
			}
			if (inPath == false) {
				path[level] = k;
				break;
			}
			
			/*
			if (!inPath(k, path, 0, level - 1)) {
				path[level] = k;
			}
			*/
		}
		path[level + 1] = 1;
		level = n;
	}

	bool operator > (const Node &rhs) const { return bound > rhs.bound; }

};

// Function Prototype
void TSP();
int bound(Node &);
int length(Node &);
void setTour(int[], int[]);
bool inPath(int, int[], int, int);
int getMin(int[], int);

priority_queue<Node, vector<Node>, greater<Node>> PQ;

int main()
{
	cout << "Input File Name? ";
	string InputFileName;
	cin >> InputFileName;

	fsin.open(InputFileName, ifstream::in);
	fsout.open("output.txt", ofstream::out);


	fsin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int temp;
			fsin >> temp;
			if (temp == 0)
				W[i][j] = U_LIMIT;
			else
				W[i][j] = temp;
		}
	}

	TSP();

	fsout << minlength << endl;
	for (int i = 0; i <= n; i++) {
		fsout << opttour[i] << endl;
	}

	return 0;
}

void TSP()
{
	// initialize(PQ);
	Node v;
	v.level = 0;
	v.path[0] = 1;
	v.bound = bound(v);
	minlength = U_LIMIT;
	PQ.push(v);
	while (!PQ.empty()) {
		v = PQ.top();
		PQ.pop();
		cout << "bound: " << v.bound << endl;
		if (v.bound < minlength) {
			Node u;
			u.level = v.level + 1;
			if (u.level == n - 1) {
				setTour(u.path, v.path); // 여기가 문제
				u.LastTwo(); // add(나머지 1개) & 1 to u.path -> level + 1, level + 2 해결
				if (length(u) < minlength) {
					minlength = length(u);
					setTour(opttour, u.path);
					return;
				}
			}
			else {
				for (int i = 2; i <= n; i++) // && i ∈ v.path do 해결
				{
					if (!inPath(i, v.path, 0, v.level)) {
						setTour(u.path, v.path);
						u.path[u.level] = i; // add i to u path 해결
						u.bound = bound(u);
						// 오류 확인
						cout << '\t' << u.bound << endl;
						for (int j = 0; j <= n; j++) {
							cout << '\t' << u.path[j] << '\t';
						}
						cout << endl;
						// 오류 확인
						if (u.bound < minlength)
							PQ.push(u);
					}
				}
			}
		}
	}
}
/*
int bound(Node &v)
{
	int bound = 0;
	bound += length(v); // 바운드에 현재까지 이동한 노드까지의 edge를 더함
	for (int i = 1; i <= n; i++) { // 모든 노드에 대해서
		if (!inPath(i, v.path, 0, v.level - 1)) { // 지금까지 출발한 노드중에 없으면
			bound += getMin(W[i], n); // 그 노드에서 출발하는 edge 중 가장 작은 값을 바운드에 더함
		}
	}
	return bound;
}
*/


int bound(Node &v)
{
	int bound = 0;
	bound += length(v); // 바운드에 현재까지 이동한 노드까지의 edge를 더함
	cout << bound << '+' << endl;

	int ary[MAX_ARY][MAX_ARY] = { U_LIMIT, };
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			//if (ary[i][j] != U_LIMIT)
				//cout << "U_LIMIT" << endl;
			ary[i][j] = W[i][j];
		}
	}
	for (int i = 0, j = 1; j <= v.level; i++, j++) {
		int a = v.path[i];
		int b = v.path[j];
		ary[b][a] = U_LIMIT; // 다시 돌아오는 경우
		for (int j = 1; j <= n; j++) {
			ary[a][j] = U_LIMIT;
		} // 가로
		for (int j = 1; j <= n; j++) {
			ary[j][b] = U_LIMIT;
		} // 가로
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << ary[i][j] << '\t';
		}
		cout << endl;
	}
	for (int i = 1; i <= n; i++) { // 모든 노드에 대해서
		if (!inPath(i, v.path, 0, v.level - 1)) { // 지금까지 출발한 노드중에 없으면
			bound += getMin(ary[i], n); // 그 노드에서 출발하는 edge 중 가장 작은 값을 바운드에 더함
			cout << getMin(W[i], n) << '+';
		}
	}
	cout << endl;

	return bound;
}

int length(Node &v)
{
	int length = 0;
	for (int i = 0, j = 1; j <= v.level; i++, j++) {
		length += W[v.path[i]][v.path[j]];
	}
	return length;
}

void setTour(int to[], int from[])
{
	for (int i = 0; i <= n; i++) {
		to[i] = from[i];
	}
}

bool inPath(int value, int path[], int start, int end)
{
	for (int i = start; i <= end; i++)
	{
		if (value == path[i])
			return true;
	}
	return false;
}

int getMin(int ary[], int size)
{
	int min = ary[1];
	for (int i = 1; i <= size; i++) {
		if (ary[i] < min)
			min = ary[i];
	}

	return min;
}