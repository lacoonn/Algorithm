#include <stdio.h>

int S1(int);

int main()
{
	printf("%d\n", S1(5));
}

int S1(int n)
{
	if (n <= 0)
		return 0;
	return (S1(n - 1) + n);
}