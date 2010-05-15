#include "Matrix.h"
#include "MatrixFunctions.h"
#include <iostream>
using namespace std;
#include <algorithm>
#include <numeric>
#include <cmath>

int main(int argc, char * argv[])
{
    Matrix m(2,2);
    m.populateRandom();
    cout << m << endl;
}
