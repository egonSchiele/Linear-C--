#include "Matrix.h"
#include "MatrixFunctions.h"
#include <iostream>
using namespace std;
#include <algorithm>
#include <numeric>

int main(int argc, char * argv[])
{
    Matrix A(3,3);
    A.populateSymmetric();
    ColumnVector b(3);
    b.populateRandom();
    cout << "A: " << A << endl;
    cout << "b: " << b << endl;
    
    Matrix x = conjugateGradient(A,b);
    cout << "answer:" << x << endl;
    
    cout << "answer with gaussian elimination:" << gaussianElimination(A,b) << endl;
    
    return 0;
}
