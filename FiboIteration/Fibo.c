#include <stdio.h>

int F2(int n) {
	int F[100], i;

	F[0] = 0;
	F[1] = 1;
	for (i = 2; i <= n; i++) {
		F[i] = F[i - 1] + F[i - 2];
	}
	return (F[n]);
}

int main() {
	printf("%d\n", F2(10));
}