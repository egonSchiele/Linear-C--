#include <iostream>
using namespace std;
#include "Matrix.h"
#include "MatrixFunctions.h"
#include "boost/tuple/tuple.hpp"
#include <vector>
int main(int argc, char * argv[])
{
    double ar[] = {1,2,3,3,4,5,7,2,5};
    Matrix *m = new Matrix(ar,3,3);
    Matrix *I = new Matrix(3,3);
    I->populateIdentity();
    Matrix *n = &(m->inverse());
    Matrix *sol = &(gaussJordan(*m,*I));
    cout << *sol << endl;
}