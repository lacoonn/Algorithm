#include <stdio.h>

#define NUM 6 //����
#define START 5 //������ġ

int W[NUM + 1] = { 0, 2, 10, 18, 19, 15, 19 }; //�ð��� �Һ�����
int D[NUM + 1] = { 0, 3, 11, 12, 13, 15, 17 }; //��ġ
int EE[NUM + 1][NUM + 1][3]; //�Ҹ�����
int DD[NUM + 1][NUM + 1][3]; //�̵��Ÿ�
int PP[NUM + 1][NUM + 1][3]; //������ġ

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
}