#include <iostream>
using namespace std;
#include "Matrix.h"

int main(int argc, char * argv[])
{

    int b[2][2] = { {1,0},
                    {0,1} };
    Matrix a(2,2);
    a.populateRandom();
    int c[] = {50,50};
    a.appendCol(c,2);
    
    RowVector x(2);
    x.populateRandom();
    cout << x << endl;
    
    cout << a << endl;
    cout << a.transpose() << endl;
	return 0;
}