#include "Matrix.h"
#include "MatrixFunctions.h"
#include <iostream>
using namespace std;
#include <algorithm>
#include <numeric>
int main(int argc, char * argv[])
{
    double ar1[] = {2, 1, 1, 2, 2.5, -1};
    Matrix A(ar1,2,3);
    cout << A << endl;
    sort(A.begin(),A.end(),greater<double>());
    cout << "sorted: " << A << endl;
    Matrix b(10,10);
    b.populateRandom();
    cout << b << endl;

}
