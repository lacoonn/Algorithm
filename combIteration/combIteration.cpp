#include <stdio.h>

int Comb(int n, int k) {
	int combArr[100][100], i, j;
	
	for (i = 0; i < 100; i++) {
		combArr[i][0] = 1;
	}
	for (i = 0; i < 100; i++) {
		for (j = 0; j < 100; j++) {
			if(j == j)
				combArr[i][j] = 1;
		}
	}
	
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= k; j++) {
			if (j == 0)
				combArr[i][j] = 1;
			else if (i == j)
				combArr[i][j] = 1;
			else
				combArr[i][j] = combArr[i - 1][j - 1] + combArr[i - 1][j];
		}
		
	}
	return combArr[n][k];
}

int main() {
	printf("%d\n", Comb(10, 2));
}