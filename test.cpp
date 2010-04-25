#include <iostream>
using namespace std;
#include "Matrix.h"
#include "MatrixFunctions.h"
#include "boost/tuple/tuple.hpp"
#include <vector>
#include <algorithm>
int main(int argc, char * argv[])
{
    double ar1[] = {2, 1, 1, 2, 2.5, -1};
    Matrix A(ar1,2,3);
    cout << A << endl;
    sort(A.begin(),A.end());
    cout << "sorted: " << A << endl;
}