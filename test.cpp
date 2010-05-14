#include "Matrix.h"
#include "MatrixFunctions.h"
#include <iostream>
using namespace std;
#include <algorithm>
#include <numeric>

int main(int argc, char * argv[])
{
    double v[] = {2, -1, 0, -1, 2, -1, 0, -1, 2};
    Matrix A(v,3,3);
//    A.populateSymmetric();
    double v2[] = {1, 2, 3};
    ColumnVector b(v2,3);
//    b.populateRandom();
    cout << "A: " << A << endl;
    cout << "b: " << b << endl;
    
    Matrix x = steepestDescent(A,b);
    cout << "answer:" << x << endl;
    
    cout << "answer with gaussian elimination:" << gaussianElimination(A,b) << endl;
    
    return 0;
}
