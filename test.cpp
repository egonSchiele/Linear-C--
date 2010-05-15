#include "Matrix.h"
#include "MatrixFunctions.h"
#include <iostream>
using namespace std;
#include <algorithm>
#include <numeric>
#include <cmath>

int main(int argc, char * argv[])
{
/*
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
    
*/
    double ar[] = {3, 1, 8, 2, -5, 4, -1, 6, -2};
    Matrix *m = new Matrix(ar,3,3);
    double d = m->det();
    cout << (fabs(m->det() - 14) < .01) << endl;
    cout << (m->det()==14) << endl;
    cout << (d==14) << endl;

    return 0;
}
