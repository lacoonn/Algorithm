#include <stdio.h>
#include <stdlib.h>

int num = 0;

void swap(char *first, char *second) {
	char temp = *first;
	*first = *second;
	*second = temp;
}

int comp(const void *a, const void *b) {
	return *(char *)a - *(char *)b;
}

void perm(char* a, int k, int n) { // a:배열 k:현재위치 n:문자열갯수
	int m = k;

	if (k >= n) {
		puts(a);
		num++;
		return;
	}
		
	qsort(a + k, n - k, sizeof(char), comp);
	perm(a, k + 1, n);
	qsort(a + k + 1, n - k - 1, sizeof(char), comp);

	while (m < n) {
		if (a[m] > a[k]) {
			
			swap(&a[m], &a[k]);
			
			perm(a, k + 1, n);
			qsort(a + k + 1, n - k - 1, sizeof(char), comp);
		}
		m++;
	}
	
}

int main() {
	char a[11] = "ccbbaa";
	perm(a, 0, 6);
	printf("%d\n", num);
}

/*
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
int g_count;

int perm(string a, int k, int n)
{
	if (k >= n)
	{
		//cout << a << " ";
		g_count++;
		return 0;
	}
	sort(a.begin() + k, a.end());
	//cout << a << "\n";
	perm(a, k + 1, n);
	//sort(a.begin() + k+1, a.end());
	


	for (int i = k; i < n; i++)
	{
		if (i > k && a[i] > a[k])
		{
			swap(a[i], a[k]);

			cout << a << "\n";
			perm(a, k + 1, n);
			//sort(a.begin() + k + 1, a.end());
		}
	}

	return 0;
}

int main()
{
	string a;

	getline(cin, a, '\n');

	cout << "\n";

	perm(a, 0, a.length());

	cout << g_count << "\n";


	return 0;
}
*/