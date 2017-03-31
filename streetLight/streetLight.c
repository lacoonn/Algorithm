#include <stdio.h>

#define NUM 6 //����
#define START 5 //������ġ

int W[NUM + 1] = { 0, 2, 10, 18, 19, 15, 19 }; //�ð��� �Һ�����
int D[NUM + 1] = { 0, 3, 11, 12, 13, 15, 17 }; //��ġ
int EE[NUM + 1][NUM + 1][3]; //�Ҹ�����
int DD[NUM + 1][NUM + 1][3]; //�̵��Ÿ�
int PP[NUM + 1][NUM + 1][3]; //������ġ

int min(int, int);

int main()
{
	int i, j, k;

	EE[START][START][1] = 0;
	EE[START][START][2] = 0;

	for (i = 1; i <= NUM; i++) {
		if (i != START) {
			EE[i][i][1] = 9999;
			EE[i][i][2] = 9999;
		}
		DD[i][i][1] = 0;
		DD[i][i][2] = 0;
		PP[i][i][1] = 0;
		PP[i][i][2] = 0;

	}

	for (i = 1; i <= NUM; i++) {
		for (j = i + 1; j <= NUM; j++) {
			EE[i][j][1] = min(EE[i + 1][j][1] + (DD[i + 1][j][1] + D[i + 1] - D[i]) * W[i],
												EE[i + 1][j][2] + (DD[i + 1][j][2] + D[j] - D[i]) * W[i]);
			EE[i][j][2] = min(EE[i][j - 1][2] + (DD[i][j - 1][2] + D[j] - D[j - 1]) * W[j],
												EE[i][j - 1][1] + (DD[i][j - 1][2] + D[j] - D[i]) * W[j]);
			
		}
	}
}

int min(a, b) {
	if (a <= b)
		return a;
	return b;
}
