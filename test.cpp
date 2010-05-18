#include "Matrix.h"
#include "MatrixFunctions.h"
#include <iostream>
using namespace std;
#include <algorithm>
#include <numeric>
#include <cmath>

int main(int argc, char * argv[])
{
    double var[] = {1, -2, -3, -4, 0, 0, 0, 3, 2, 1, 1, 0, 0, 2, 5, 3, 0, 1};
    double val[] = {0,10,15};
    
    Matrix m(var,3,6);
    ColumnVector b(val,3);
    cout << m << endl;
    cout << b << endl;
    cout << simplex(m,b) << endl;
    
    return 0;
}
