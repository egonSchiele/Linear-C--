#include <iostream>
using namespace std;
#include "Matrix.h"

int main(int argc, char * argv[])
{
	RowVector r(10);
	r.populateRandom();
	ColumnVector c(10);
	c.populateRandom();
	cout << r*c << endl;
	cout << c*r << endl;
	return 0;
}