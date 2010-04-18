#include <iostream>
using namespace std;
#include "Matrix.h"
#include "MatrixFunctions.h"
#include "boost/tuple/tuple.hpp"

int main(int argc, char * argv[])
{

    Matrix L(2,2);
    L(0,0) = 1;
    L(0,1) = 0;
    L(1,0) = 4;
    L(1,1) = 1;

    Matrix U(2,2);
    U(0,0) = 2;
    U(0,1) = 1;
    U(1,0) = 0;
    U(1,1) = 3;
    
    Matrix A = L*U;
    cout << A << endl;
    boost::tuple<Matrix,Matrix> lu = LUDecompose(A);
    L = lu.get<0>();
    U = lu.get<1>();
    
    cout << L << endl;
    cout << U << endl;
    cout << L*U << endl;
    return 0;
}