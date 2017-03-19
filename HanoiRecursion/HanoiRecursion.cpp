#include <stdio.h>

void T_H(int A, int B, int C, int n) {
	if (n <= 0)
		return;
	T_H(A, C, B, n - 1);
	printf("Move disk %d from %d to %d\n",n, A, C);
	T_H(B, A, C, n - 1);
}

int main()
{
	T_H(1, 2, 3, 10);
}