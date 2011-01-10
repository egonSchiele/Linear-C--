#include "Matrix.h"
#include "MatrixFunctions.h"
#include <iostream>
using namespace std;
#include <algorithm>
#include <numeric>
#include <cmath>

int main(int argc, char * argv[])
{
    double var[] = {0,0,0,1,0,0,0,0,0};
    
    Matrix m(var,3,3);
    Matrix r(5,5);
	r.populateRandom();
	cout << r << endl;
	cout << convolve(r, m) << endl;

    return 0;
}
