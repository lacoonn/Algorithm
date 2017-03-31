int A[30][30][30];
int P[30][30][30];

int print_value(int i, int j, int v, int x)
{
	int u, k;

	if (i < j)
	{
		u = A[i][j][v];
		k = P[i][j][u + v];
		if (A[i][k][u] && A[k + 1][j][u + v])
		{
			print_value(i, k, u, x);
			print_value(k + 1, j, u + v, x + 1);
			printf("%d ", x);
		}
		else
		{
			print_value(i, k, u + v, x);
			print_value(k + 1, j, u, x + 1);
			printf("%d ", x);
		}
	}
}

int main()
{
	if (A[1][n][V] == -1)
		printf("0");
	else
		print_value(1, n, V, 1);

	return 0;
}