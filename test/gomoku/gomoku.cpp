#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
��Ʒ��� �������� �����ϼ���.
���и�: �����������б�
��  ��: �츮��
��  ��: ȫ�浿(��ǻ�Ͱ��а� 4�г�),...
������: 2017.5.10

���ۼ� �� ���ǻ���
- C++�⺻ ������ ���Ͽ� �ۼ�
- �ܺ� ���̺귯�� ��� ���� (dll, STL��)
- for�� �ε��� ������ �ܺο� �̸� ������ �� (�Ʒ��� ���� ���� �� ��)
for (int i = 0; i < 10...
- ���� ���� global����, �Լ�, class�� ���� ����, �� �ٸ� ���� �ߺ����� �ʵ��� ���
- ����� �� ������ �Լ� f201701001()�� �ش� ����ȣ�� �����ϰ� "����ȣ.cpp"�� �����Ͽ� ����
*/

// ��� ����
#define MAXXY 16
#define BLACK 1
#define WHITE 0
#define EMPTY -1
#define OUTBD -2

#define WEIGHT 2

// B�Լ��� �������� �ش� ��ġ�� ��Ȳ�� ����� �� ��, ����ϴ� �Լ��� ������ BLACK, WHITE, EMPTY, OUTBD�� �� ���� ������
// B(-3,6)�� ������ �ٱ��� �����ϹǷ� OUTBD(-2)�� ���ϰ����� ����
// B(-3,6,BLACK)�� ������ ���� �����ϳ�, ���ϰ��� def������ �Ѱ��� BLACK�� ���ϰ����� ����
//extern int B(int x, int y, int def = OUTBD);

int ary[16][16] = { -1 };

int B(int x, int y)
{
	return ary[y][x];
}


// AI �ۼ���, B(int x,int y,int)�Լ��� ���� �Ǽ��� �м��ϰ� ���� �� ��ġ ���� ���� *NewX, *NewY�� ���� ȣ�� �Լ��� �ǵ�����.
// ������ ���� ���� ���η� ���� 2�� �ְ� �� �������� ����ִ� ���� ã�� ���� �δ� AI�� ���̴�.
//
// NewX,NewY : AI�� ���� ���� �ΰ��� �ϴ� ���� ���� ���� ������ ����
// mc : AI�� �� ���� �� (BLACK �Ǵ� WHITE)
// CurTurn : ���� ����� ��
// 4�� ���������� ���� ������ ����, COmDevDlg::IsGameOver() �Լ��� ���� ����

static int MC;
static int EC;

int getScore(int value, int color)
{
	int weight = 1;
	if (color == EC)
		weight = -WEIGHT;
	switch (value) {
	case 1:
		return 10 * weight;
	case 2:
		return 40 * weight;
	case 3:
		return 160 * weight;
	case 4:
		return 640 * weight;
	case 5:
		return 10000 * weight;
	default:
		return value * weight;
	}
}

int getBoundedScore(int value, int color)
{
	int weight = 1;
	if (color == EC)
		weight = -WEIGHT;
	switch (value) {
	case 1:
		return 0 * weight;
	case 2:
		return 1 * weight;
	case 3:
		return 2 * weight;
	case 4:
		return 5 * weight;
	case 5:
		return 100000 * weight;
	default:
		return value * weight;
	}
}

static class Board {
private:
	int board[MAXXY][MAXXY];
	int new_x;
	int new_y;
	int eval;

public:
	Board()
	{
		eval = 0;
	}
	void initBoard()
	{
		int i, j;
		for (i = 0; i < MAXXY; i++) {
			for (j = 0; j < MAXXY; j++) {
				board[j][i] = B(i, j);
			}
		}
	}
	;void getBoard()
	{
		int i, j;
		cout << "print" << endl;
		for (i = 0; i < MAXXY; i++) {
			for (j = 0; j < MAXXY; j++) {
				cout << board[j][i];
			}
			cout << endl;
		}
	}
	int boardValue(int x, int y)
	{
		// ��ǥ�� �ִ� ���� ��ȯ(BLACK, WHITE, EMPTY)
		return board[y][x];
	}
	void setEval(int _eval)
	{
		eval = _eval;
	}
	int getEval()
	{
		return eval;
	}
	void addXY(int x, int y, int color)
	{
		// �� ���� ���� newX, newY�� ������Ʈ�Ѵ�.
		board[y][x] = color;
		new_x = x;
		new_y = y;
	}
	void setXY(int x, int y)
	{
		new_x = x;
		new_y = y;
	}
	void getXY(int &x, int &y)
	{
		x = new_x;
		y = new_y;
	}
	void evaluation()
	{
		// evaluation function
		int x, y, i;
		int tempEval = 0;
		// �ٵ��ǿ� ��ġ�� ��� ���� ���� �˻��Ѵ�.
		for (y = 0; y < MAXXY; y++) {
			for (x = 0; x < MAXXY; x++) {
				int currentColor = board[y][x]; // ���� ��ġ�� ����
				if (currentColor == WHITE && currentColor == BLACK) { // �� ������ �ƴ� ���
					int enemyColor = (currentColor == WHITE) ? BLACK : WHITE;

					int tempValue = 1;
					for (i = 1; i <= 4; i++) { // up
						if (y - i < 0) { // �ٵ��� �ٱ����� �Ѿ��
										 //tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y - i][x] != currentColor) {
							//tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y - i][x] == currentColor) // �� ���̸� �ӽ����� + 1
							tempValue++;
						//if (i == 4)
						//tempEval += getScore(tempValue, currentColor);
					}
					tempEval += getScore(tempValue, currentColor);

					tempValue = 1;
					for (i = 1; i <= 4; i++) { // up-right
						if (y - i < 0 || x + i >= MAXXY) { // �ٵ��� �ٱ����� �Ѿ��
														   //tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y - i][x + i] != currentColor) {
							//tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y - i][x + i] == currentColor) // �� ���̸� �ӽ����� + 1
							tempValue++;
						//if (i == 4)
						//tempEval += getScore(tempValue, currentColor);
					}
					tempEval += getScore(tempValue, currentColor);

					tempValue = 1;
					for (i = 1; i <= 4; i++) { // right
						if (x + i >= MAXXY) { // �ٵ��� �ٱ����� �Ѿ��
											  //tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y][x + i] != currentColor) {
							//tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y][x + i] == currentColor) // �� ���̸� �ӽ����� + 1
							tempValue++;
						//if (i == 4)
						//tempEval += getScore(tempValue, currentColor);
					}
					tempEval += getScore(tempValue, currentColor);

					tempValue = 1;
					for (i = 1; i <= 4; i++) { // right-down
						if (x + i >= MAXXY || y + i >= MAXXY) { // �ٵ��� �ٱ����� �Ѿ��
																//tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y + i][x + i] != currentColor) {
							//tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y + i][x + i] == currentColor) // �� ���̸� �ӽ����� + 1
							tempValue++;
						//if (i == 4)
						//tempEval += getScore(tempValue, currentColor);
					}
					tempEval += getScore(tempValue, currentColor);

					tempValue = 1;
					for (i = 1; i <= 4; i++) { // down
						if (y + i >= MAXXY) { // �ٵ��� �ٱ����� �Ѿ��
											  //tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y + i][x] != currentColor) {
							//tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y + i][x] == currentColor) // �� ���̸� �ӽ����� + 1
							tempValue++;
						//if (i == 4)
						//tempEval += getScore(tempValue, currentColor);
					}
					tempEval += getScore(tempValue, currentColor);

					tempValue = 1;
					for (i = 1; i <= 4; i++) { // down-left
						if (y + i >= MAXXY || x - i < 0) { // �ٵ��� �ٱ����� �Ѿ��
														   //tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y + i][x - i] != currentColor) {
							//tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y + i][x - i] == currentColor) // �� ���̸� �ӽ����� + 1
							tempValue++;
						//if (i == 4)
						//tempEval += getScore(tempValue, currentColor);
					}
					tempEval += getScore(tempValue, currentColor);

					tempValue = 1;
					for (i = 1; i <= 4; i++) { // left
						if (x - i < 0) { // �ٵ��� �ٱ����� �Ѿ��
										 //tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y][x - i] != currentColor) {
							//tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y][x - i] == currentColor) // �� ���̸� �ӽ����� + 1
							tempValue++;
						//if (i == 4)
						//tempEval += getScore(tempValue, currentColor);
					}
					tempEval += getScore(tempValue, currentColor);

					tempValue = 1;
					for (i = 1; i <= 4; i++) { // left - up
						if (x - i < 0 || y - i < 0) { // �ٵ��� �ٱ����� �Ѿ��
													  //tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y - i][x - i] != currentColor) {
							//tempEval += getBoundedScore(tempValue, currentColor);
							break;
						}
						if (board[y - i][x - i] == currentColor) // �� ���̸� �ӽ����� + 1
							tempValue++;
						//if (i == 4)
						//tempEval += getScore(tempValue, currentColor);
					}
					tempEval += getScore(tempValue, currentColor);

				}
			}
		}
		eval = tempEval;
	}
};

int maxNode(int a, int b)
{
	if (a < b)
		return b;
	else
		return a;
}

int minNode(int a, int b)
{
	if (a > b)
		return b;
	else
		return a;
}

Board minimax(Board node, int depth, int alpha, int beta, bool maximizingPlayer)
{
	cout << "11" << endl;
	if (depth == 0) {
		node.evaluation();
		int temp = node.getEval();
		cout << temp << endl;
		node.getBoard();
		return node;
	}

	int i, j;

	// ��ȯ�� ���� �޾ƾ� �� - �������� ��ȯ�� ���ؼ�
	// ��ȯ���� ��带 ���� ��忡 ���� ������ �ʿ�� ���� - �ʿ��Ѱ� eval��
	// xy���� ��ȯ���� ����� ���� ����ϸ� �� �ǰ� �� �Լ��� ij�� ����ؾ���
	cout << "11" << endl;
	if (maximizingPlayer) { // (�ִ밪�� ����) �� ���� ���
		int bestValue = -99999;
		int bestX = 0, bestY = 0;
		for (i = 0; i < MAXXY; i++) {
			for (j = 0; j < MAXXY; j++) {
				// �ش� ĭ�� ��ĭ�� ��쿡�� Ʈ���� ����
				if (node.boardValue(i, j) == EMPTY) {
					Board nextNode = node; // minmax �Լ��� �� �ӽ� ���
					nextNode.addXY(i, j, MC); // xy ����� �� ����

											  // ��ȯ���� ����� eval���� ����ϰ� �������� ����(������ x, y���� ù �Լ��� ���� ��ȯ�ؾ��ϱ⶧����)
					int v = minimax(nextNode, depth - 1, alpha, beta, false).getEval();

					bestValue = maxNode(bestValue, v);
					if (bestValue == v) {
						bestX = i;
						bestY = j;
					}
					/*
					// alpha-beta pruning
					alpha = maxNode(alpha, bestValue);
					if (beta <= alpha) {
					node.setEval(bestValue);
					node.setXY(bestX, bestY);
					return node;
					}
					*/
				}
			}
		}
		// node ������ eval, new_x, new_y ���� ����
		node.setEval(bestValue);
		node.setXY(bestX, bestY);
		return node;
	}
	else { // minimizingPlayer
		int bestValue = 99999;
		int bestX = 0, bestY = 0;
		for (i = 0; i < MAXXY; i++) {
			for (j = 0; j < MAXXY; j++) {
				// �ش� ĭ�� ��ĭ�� ��쿡�� Ʈ���� ����
				if (node.boardValue(i, j) == EMPTY) {
					Board nextNode = node; // minmax �Լ��� �� �ӽ� ���
					nextNode.addXY(i, j, EC); // �ӽ� ����� xy ��ǥ�� ���� ����

					int v = minimax(nextNode, depth - 1, alpha, beta, true).getEval();

					bestValue = minNode(bestValue, v);
					if (bestValue == v) {
						bestX = i;
						bestY = j;
					}
					/*
					// alpha-beta pruning
					beta = minNode(beta, bestValue);
					if (beta <= alpha) {
					node.setEval(bestValue);
					node.setXY(bestX, bestY);
					return node;
					}
					*/
				}
			}
		}
		node.setEval(bestValue);
		node.setXY(bestX, bestY);
		return node;
	}
}

void f201701001(int *NewX, int *NewY, int mc, int CurTurn)
{
	int ec = (mc == WHITE) ? BLACK : WHITE;	//	���� �� Ȯ��
	MC = mc;
	EC = ec;

	Board current_board;
	current_board.initBoard(); // ���� ������ �ʱ�ȭ

	int alpha = -99999, beta = 99999;
	Board new_board = minimax(current_board, 1, alpha, beta, true);

	new_board.getXY(*NewX, *NewY);

	if (CurTurn == 0) {
		*NewX = rand() % MAXXY;
		*NewY = rand() % MAXXY;
	}
	while (1) {
		if (B(*NewX, *NewY) == EMPTY) {
			break;
		}
		*NewX = rand() % MAXXY;
		*NewY = rand() % MAXXY;
	}
}

int main()
{
	int x, y;
	scanf("%d %d", &x, &y);
	ary[y][x] = BLACK;
	f201701001(&x, &y, WHITE, 1);
	ary[y][x] = WHITE;
	scanf("%d %d", &x, &y);
	ary[y][x] = BLACK;
	f201701001(&x, &y, WHITE, 1);
	ary[y][x] = WHITE;
	scanf("%d %d", &x, &y);
	ary[y][x] = BLACK;
	f201701001(&x, &y, WHITE, 1);
	ary[y][x] = WHITE;
}
