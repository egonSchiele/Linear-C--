#include <iostream>
using namespace std;
#include "Matrix.h"
#include "MatrixFunctions.h"
#include "boost/tuple/tuple.hpp"

int main(int argc, char * argv[])
{
    Matrix A(3,3);
    A.populateRandom();
/*
[ 0  2  9 ]
[ 7  5  0 ]
[ 3  9  6 ]
*/
/*

    A(0,0) = 0;
    A(0,1) = 2;
    A(0,2) = 9;
    A(1,0) = 7;
    A(1,1) = 5;
    A(1,2) = 0;
    A(2,0) = 3;
    A(2,1) = 9;
    A(2,2) = 6;
        
*/
    boost::tuple<Matrix,Matrix> t = LUDecompose(A);
    
    Matrix L = t.get<0>();
    Matrix U = t.get<1>();
    
    cout << "A:" << A << endl;
    cout << "L:" << L << endl;
    cout << "U:" << U << endl;
    cout << "A again?:" << L*U << endl;
}