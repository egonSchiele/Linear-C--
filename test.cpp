#include <iostream>
using namespace std;
#include "Matrix.h"
#include "MatrixFunctions.h"
#include "boost/tuple/tuple.hpp"
#include <vector>
int main(int argc, char * argv[])
{
    vector<vector<double> > a;
    a.resize(3);
    a[0].resize(3);
    a[1].resize(3);
    a[2].resize(3);
    
    a[0][0] = 0;
    a[0][1] = 0;
    a[0][2] = 1;
    a[1][0] = 2;
    a[1][1] = 4;
    a[1][2] = 6;
    a[2][0] = 1;
    a[2][1] = 2;
    a[2][2] = 3;

    Matrix m(a);
    ColumnVector c(3);
    c.populateRandom();
    cout << gaussJordan(m,c) << endl;
/*
    m.populateRandom();
    boost::tuple<Matrix, Matrix> t = LUDecompose(m);
    
    Matrix L = t.get<0>();
    Matrix U = t.get<1>();
    
    cout << "m is:" << m << endl;
    cout << "L*U:" << L*U << endl;
    cout << L << endl;
    cout << U << endl;
*/
}

/*
    0 0 1
    2 4 6
    1 2 3


*/