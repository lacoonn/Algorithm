#include <stdio.h>

int A[30][30][31];
int P[30][30][31];
int a[31] = { -1, 12, 10, 4, 3, 5 };
int V = 8;
int n = 5;

int print_value(int i, int j, int v, int x);


int main()
{
	int i, j, k, l;


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


	print_value(1, n, V, 1);
	if (A[1][n][V] == -1)
		printf("0\n");

	return 0;
}


int print_value(int i, int j, int v, int x)
{
	int u, k;

	if (i < j) {
		u = A[i][j][v];
		k = P[i][j][v];

		if (A[i][k][u] && A[k + 1][j][u + v]) {
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