#include <iostream>
using namespace std;
#include "Matrix.h"
#include "MatrixFunctions.h"
#include "boost/tuple/tuple.hpp"
#include <vector>
int main(int argc, char * argv[])
{
    double ar1[] = {2, 1, 1, 2, 2.5, -1};
    Matrix A(ar1,2,3);
    cout << A << endl;
    ColumnVector b(2);
    
    cout << gaussianElimination(A,b) << endl;
}