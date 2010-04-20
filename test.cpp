#include <iostream>
using namespace std;
#include "Matrix.h"
#include "MatrixFunctions.h"
#include "boost/tuple/tuple.hpp"
#include <vector>
int main(int argc, char * argv[])
{
    Matrix A(3,3);
    A.populateRandom();
  
    // get its decomposition
    boost::tuple<Matrix,Matrix,Matrix> lu = LUPDecompose(A);
    Matrix L = lu.get<0>();
    Matrix U = lu.get<1>();
    Matrix P = lu.get<2>();
    cout << "A:" << A << endl;
    cout << "L:" << L << endl;
    cout << "U:" << U << endl;
    cout << "P:" << P << endl;
    cout << "LUP:" << L*U*P << endl;
}