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
public:
	int a;
	int b;
	Node(int _a)
	{
		a = _a;
		// b = _b;
	}
	bool operator > (const Node &rhs) const { return a > rhs.a; }

};

priority_queue<Node, vector<Node>, greater<Node>> PQ;

int main()
{
	Node a(1);
	PQ.push(a);
	Node b(2);
	PQ.push(b);
	Node c(3);
	PQ.push(c);
	a.a = 4;
	b.a = 5;
	c.a = 6;
	Node d = PQ.top();
	cout << d.a << endl;

	return 0;
}