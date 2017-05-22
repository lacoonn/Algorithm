#include <iostream>
using namespace std;

class testThing
{
private:
	int ary[3][3];
public :
	testThing()
	{

	}
	void initThing()
	{
		int i, j;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				ary[i][j] = 3;
			}
		}
	}
	void setThing()
	{
		int i, j;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				ary[i][j] = 5;
			}
		}
	}
	void printThing()
	{
		int i, j;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				cout << ary[i][j];
			}
			cout << endl;
		}
	}
};

int main()
{
	testThing a;
	a.initThing();
	testThing b = a;
	a.setThing();
	a.printThing();
	b.printThing();

	return 0;
}