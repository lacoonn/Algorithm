#include <stdio.h>

#define NUM 6 //개수
#define START 5 //시작위치

int W[NUM + 1] = { 0, 2, 10, 18, 19, 15, 19 }; //시간당 소비전력
int D[NUM + 1] = { 0, 3, 11, 12, 13, 15, 17 }; //위치
int EE[NUM + 1][NUM + 1][3]; //소모전력
int DD[NUM + 1][NUM + 1][3]; //이동거리
int PP[NUM + 1][NUM + 1][3]; //이전위치

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