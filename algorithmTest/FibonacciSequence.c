#include <stdio.h>

int F1(int);

int main()
{
	printf("%d\n", F1(10));
}

int F1(int n)
{
	if (n <= 1)
		return n;
	return (F1(n - 1) + F1(n - 2));

}