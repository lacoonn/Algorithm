#include <stdio.h>
#include <limits.h>

#define INF		INT_MAX
#define MAX		1000

void EE(int L, int R, int n);
void recursive();
void path(int L, int R, int last);

int N;
int M;
int D[MAX];
int W[MAX];

int mQueue[MAX*MAX][2];		// previous performed "EE(L, R, 0 or 1)"
int mQueueStart;
int mQueueEnd;

int mEE[MAX][MAX][3];
int mDD[MAX][MAX][3];
int mPP[MAX][MAX][3];

int main(int argc, char** argv) {
	int resultL = 0;
	int resultR = 0;
	int result_final = 0;
	int L = 0;
	int R = 0;
	int last = 0; // last position
	int i = 0, j = 0;

	// input
	scanf("%d", &N);
	scanf("%d", &M);

	for (i = 0; i<N; ++i) {
		scanf("%d %d", &D[i + 1], &W[i + 1]);
	}

	// initialize
	for (i = 0; i<MAX; ++i) {
		for (j = 0; j<MAX; ++j) {
			mEE[i][j][1] = INF;
			mEE[i][j][2] = INF;
		}
	}

	mEE[M][M][1] = 0;
	mEE[M][M][2] = 0;

	mQueue[0][0] = M;
	mQueue[0][1] = M;

	mQueueStart = 0;
	mQueueEnd = 1;

	// do DP (dynamic programming)
	recursive();

	// min { EE[1,N,1], EE[1,N,2] }
	resultL = mEE[1][N][1];
	resultR = mEE[1][N][2];

	if (resultL < resultR) {
		result_final = resultL;
		last = 1;
	}
	else {
		result_final = resultR;
		last = N;
	}

	// shop result and path
	printf("%d\n", result_final);
	//path(1, N, last);

	return 0;
}

void recursive() {
	int i = 0;
	int L = 0, R = 0;
	int newQueueEnd = 0;

	newQueueEnd = mQueueEnd;
	for (i = mQueueStart; i<mQueueEnd; ++i) {
		L = mQueue[i][0];
		R = mQueue[i][1];

		if (L - 1 >= 1) {
			EE(L - 1, R, 1);
			EE(L - 1, R, 2);

			mQueue[newQueueEnd][0] = L - 1;
			mQueue[newQueueEnd][1] = R;

			++newQueueEnd;
		}

		if (R + 1 <= N) {
			EE(L, R + 1, 1);
			EE(L, R + 1, 2);

			mQueue[newQueueEnd][0] = L;
			mQueue[newQueueEnd][1] = R + 1;

			++newQueueEnd;
		}
	}

	if (mQueueEnd == newQueueEnd) {
		return;
	}

	mQueueStart = mQueueEnd;
	mQueueEnd = newQueueEnd;

	recursive();
}

void EE(int L, int R, int n) {
	int EE_L = 0;
	int EE_R = 0;

	int distanceL = 0;
	int distanceR = 0;

	int weight = 0;

	int resultL = 0;
	int resultR = 0;

	// flag
	// 1: take left result
	// 2: take right result
	int flag = 0;

	if (n == 1) {
		EE_L = mEE[L + 1][R][1];
		EE_R = mEE[L + 1][R][2];

		distanceL = mDD[L + 1][R][1] + D[L + 1] - D[L];
		distanceR = mDD[L + 1][R][2] + D[R] - D[L];

		weight = W[L];
	}
	else { // n == 2
		EE_L = mEE[L][R - 1][1];
		EE_R = mEE[L][R - 1][2];

		distanceL = mDD[L][R - 1][1] + D[R] - D[L];
		distanceR = mDD[L][R - 1][2] + D[R] - D[R - 1];

		weight = W[R];
	}

	if (EE_L == INF && EE_R == INF) {
		return;
	}

	// which result is better?
	if (EE_L == INF) {
		resultR = EE_R + distanceR * weight;
		flag = 2;
	}
	else if (EE_R == INF) {
		resultL = EE_L + distanceL * weight;
		flag = 1;
	}
	else { // EE_L != INF && EE_R != INF
		resultL = EE_L + distanceL * weight;
		resultR = EE_R + distanceR * weight;

		if (resultL < resultR) {
			flag = 1;
		}
		else if (resultL > resultR) {
			flag = 2;
		}
		else { // resultL == resultR, choose the shorter distance
			if (distanceL < distanceR) {
				flag = 1;
			}
			else {
				flag = 2;
			}
		}
	}

	// save the result of EE(L, R, n), DD(L, R, n) and PP(L, R, n)
	if (flag == 1) {
		mEE[L][R][n] = resultL;
		mDD[L][R][n] = distanceL;
		if (n == 1) {
			mPP[L][R][n] = L + 1;
		}
		else if (n == 2) {
			mPP[L][R][n] = L;
		}
	}
	else if (flag == 2) {
		mEE[L][R][n] = resultR;
		mDD[L][R][n] = distanceR;
		if (n == 1) {
			mPP[L][R][n] = R;
		}
		else if (n == 2) {
			mPP[L][R][n] = R - 1;
		}
	}
}

void path(int L, int R, int last) {
	if (last != M) {
		if (last == L) {
			path(L + 1, R, mPP[L][R][1]);
		}
		else if (last == R) {
			path(L, R - 1, mPP[L][R][2]);
		}
	}

	printf("%d\n", last);
}