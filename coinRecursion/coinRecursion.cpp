#include <stdio.h>

int min(int a, int b, int c, int d) {
	int temp = a;
	if (temp > b)
		temp = b;
	if (temp > c)
		temp = c;
	if (temp > d)
		temp = d;
	return temp;
}

int coin(int n) {
	if (n == 0)
		return 0;
	if (n < 0)
		return 9999;
	printf("%d\n", n);
	return(min(coin(n - 1), coin(n - 2), coin(n - 4), coin(n - 8)) + 1);
}

int main() {
	printf("%d\n", coin(30));
}