#include <stdio.h>

int Comb(int n, int k) {
	if (n == k || k == 0)
		return 1;
	return (Comb(n - 1, k - 1) + Comb(n - 1, k));

}

int main() {
	printf("%d\n", Comb(10, 2));
}