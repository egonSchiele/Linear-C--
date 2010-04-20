#include <iostream>
using namespace std;
#include "Matrix.h"
#include "MatrixFunctions.h"
#include "boost/tuple/tuple.hpp"
#include <vector>
int main(int argc, char * argv[])
{
    double v[] = {1,0,0,1};
    Matrix A(v,2,2);
    cout << A << endl;
}