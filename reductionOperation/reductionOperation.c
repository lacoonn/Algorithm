#include <stdio.h>
#include <math.h>

int A[30][30][31]; // 
int P[30][30][31]; // 이전에 연산한 항의 번호
int a[31] = { -1, 10, 2, 5, 2 };
int n = 4; //number of array
int V = 5; //what we want to check

int print_value(int i, int j, int v, int x);


int main()
{
	int h, i, j, v, k, u;

	// init array for reduction operation
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			for (k = 0; k <= 30; k++) {
				A[i][j][k] = -1;
				if (i == j) {
					if (k == a[i]) {
						A[i][j][k] = k;
						P[i][j][k] = i;
					}
				}
			}
		}
	}

	// get value

	for (h = 1; h <= n; h++) {
		for (i = 1; (j = i + h) <= n; i++) {
			printf("[%2d, %2d]\n", i, j);
			for (v = 0; v <= 30; v++) {
				for (k = i; k < j; k++) {
					for (u = 0; u <= 30 - v; u++) {
						/*
						if ((abs(A[i][k][u] - A[k + 1][j][u + v]) == v)
							|| (abs(A[i][k][u + v] - A[k + 1][j][u]))) {
							A[i][j][v] = u;
							P[i][j][v] = k;
						}
						*/
						/*
						if ((A[i][k][u] != -1 && A[k + 1][j][u + v] != -1)
							|| (A[i][k][u + v] != -1 && A[k + 1][j][u] != -1)) {
							A[i][j][v] = u;
							P[i][j][v] = k;
						}
						*/
						if ((abs(A[i][k][u] - A[k + 1][j][u + v]) == v)
							|| (abs(A[i][k][u + v] - A[k + 1][j][u]) == v)) {
							A[i][j][v] = u;
							P[i][j][v] = k;
						}
					}
				}
			}
		}
	}

	printf("A[1][%d][%d] = %d\n",n, V, A[1][n][V]);


	// print value
	if (A[1][n][V] == -1)
		printf("0\n");
	else
		print_value(1, n, V, 1);

	/*
	print_value(1, n, V, 1);
	if (A[1][n][V] == -1)
		printf("0\n");
	*/

	return 0;
}


int print_value(int i, int j, int v, int x)
{
	int u, k;

	if (i < j) {
		u = A[i][j][v];
		k = P[i][j][v];

		if (A[i][k][u] != -1 && A[k + 1][j][u + v] != -1) {
			print_value(i, k, u, x);
			print_value(k + 1, j, u + v, x + 1);
			printf("%d ", x);
		}
		else {
			print_value(i, k, u + v, x);
			print_value(k + 1, j, u, x + 1);
			printf("%d ", x);
		}
	}
}

/*

A[i,j,v] = u if ORi≤k<j OR0≤u≤30-v
((A[i,k,u] && A[k+1, j, u+v]) || (A[i, k, u+v] && A[k+1, j, u]));
P[i,j,v] = such k;

*/