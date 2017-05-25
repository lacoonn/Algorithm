#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <vector>
#include <list>

using namespace std;

#define TRUE	1
#define FALSE	0
#define MAX_FILENAME 260
#define INFI 9000

typedef struct _node
{
	int level;
	int bound;
	list<int> path;

	bool operator <  (const _node& rhs) const
	{
		return bound  < rhs.bound;
	}

} node;

priority_queue<node, vector<node>, less<node>> PQ;

int n;
int **matrix;
int **boundmatrix;
int minlength;
list<int> opttour;

void error_handling(char *message);
void travel();
int bound(node nod);
int length(node nod);
void init_boundmatrix(void);

void print_file();

int main(void)
{
	srand(time(NULL));

	string input_file;
	cout << "input file name? ";
	cin >> input_file;

	ifstream in(input_file);

	if (in.is_open())
	{
		in >> n;
	}
	else
	{
		error_handling("IFSTREAM ERROR");
	}

	matrix = new int*[n + 1];
	boundmatrix = new int*[n + 1];

	int i;

	for (i = 0; i < n + 1; i++)
	{
		matrix[i] = new int[n + 1];
		boundmatrix[i] = new int[n + 1];
	}

	int j;

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			in >> matrix[i][j];
		}
	}

	travel();
	print_file();


	for (i = 0; i < n + 1; i++)
	{
		delete[] matrix[i];
		delete[] boundmatrix[i];
	}
	delete[] matrix;
	delete[] boundmatrix;

	in.close();
	return 0;
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void travel()
{
	node u, v;
	int i, j;

	v.level = 0;
	v.path.push_back(1);
	v.bound = bound(v);
	minlength = INFI;
	PQ.push(v);

	while (!PQ.empty())
	{
		v = PQ.top();
		PQ.pop();

		if (v.bound < minlength)
		{
			u.level = v.level + 1;
			for (i = 2; i <= n; i++)
			{
				if (v.path.end() == find(v.path.begin(), v.path.end(), i))
				{
					u.path = v.path;
					u.path.push_back(i);

					if (u.level == n - 2)
					{
						for (j = 1; j <= n; j++)
						{
							if (u.path.end() == find(u.path.begin(), u.path.end(), j))
							{
								u.path.push_back(j);
								u.path.push_back(1);
								break;
							}
						}
						/*

						list<int> temp = u.path;
						temp.sort();
						int k;
						int misnum;

						for (k = 1; k <= n-1; k++)
						{
						if (k == n - 1)
						{
						misnum = k + 1;
						}

						if (k == temp.front())
						{
						temp.pop_front();
						continue;

						}
						else
						{
						misnum = k;
						break;
						}
						}
						*/

						if (length(u) < minlength)
						{
							minlength = length(u);
							opttour = u.path;
						}
					}
					else
					{
						u.bound = bound(u);
						if (u.bound < minlength)
							PQ.push(u);

					}

				}
			}



		}
	}
}
int bound(node nod)
{
	init_boundmatrix();

	list<int> remove_cow;
	list<int> remove_row;

	remove_cow = nod.path;
	remove_cow.pop_front();

	remove_row = nod.path;
	remove_row.pop_back();

	int totalbound = 0;

	int i, j;
	int flag = 0;
	list<int>::iterator iter;

	for (iter = remove_row.begin(); iter != remove_row.end(); iter++)
	{
		for (i = 1; i <= n; i++)
		{
			boundmatrix[*iter][i] = INFI;
		}
	}

	for (iter = remove_cow.begin(); iter != remove_cow.end(); iter++)
	{
		for (i = 1; i <= n; i++)
		{
			boundmatrix[i][*iter] = INFI;
		}
	}

	int last = remove_cow.back();

	boundmatrix[last][1] = INFI;

	totalbound += length(nod);

	int minnum = 9000;

	for (i = 1; i <= n; i++)
	{
		flag = 0;
		for (j = 1; j <= n; j++)
		{
			if (minnum > boundmatrix[i][j])
			{
				minnum = boundmatrix[i][j];
			}
		}

		for (iter = remove_row.begin(); iter != remove_row.end(); iter++)
		{
			if (i == *iter)
			{
				minnum = 9000;
				flag = 1;
				break;
			}
		}

		if (flag == 0)
		{
			totalbound += minnum;
			minnum = 9000;
		}
	}

	/*
	int totalbound = 0;
	list<int> check_col;
	list<int> check_row;
	int minnum = INFI;
	int vertex;

	vertex = nod.path.back();
	check_col.push_back(nod.path.back());
	check_row.push_back(nod.path.front());

	int i;
	for (i = 1; i <= n; i++)
	{
	if (nod.path.end() == find(nod.path.begin(), nod.path.end(), i))
	{
	check_col.push_back(i);
	check_row.push_back(i);
	}
	}

	totalbound += length(nod);

	list<int>::iterator iter;
	list<int>::iterator iter1;

	for (iter = check_col.begin(); iter != check_col.end(); iter++)
	{
	for (iter1 = check_row.begin(); iter1 != check_row.end(); iter1++)
	{
	if (*iter == *iter1)
	{
	continue;
	}

	if (*iter == vertex)
	{
	if (*iter1 == 1)
	continue;
	}

	if (matrix[*iter][*iter1] < minnum)
	{
	minnum = matrix[*iter][*iter1];
	}
	}
	totalbound += minnum;
	minnum = INFI;
	}
	*/
	return totalbound;

}
int length(node nod)
{
	int a1, a2;
	int i;
	list<int> temppath;
	int length = 0;
	int tempsize;

	temppath = nod.path;
	tempsize = temppath.size();
	for (i = 0; i < tempsize - 1; i++)
	{
		a1 = temppath.front();
		temppath.pop_front();
		a2 = temppath.front();
		length += matrix[a1][a2];
	}

	return length;
}
void print_file()
{
	ofstream out("output.txt");

	if (out.is_open())
	{
		out << minlength << "\n";

		while (!opttour.empty())
		{
			out << opttour.front();
			opttour.pop_front();

			if (!opttour.empty())
			{
				out << "\n";
			}
		}
	}
	else
	{
		error_handling("OFSTREAM ERROR");
	}

	out.close();
}
void init_boundmatrix(void)
{
	int i, j;

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (i == j)
			{
				boundmatrix[i][j] = INFI;
			}
			else
			{
				boundmatrix[i][j] = matrix[i][j];
			}
		}
	}
}