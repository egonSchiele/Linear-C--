#include <iostream>
using namespace std;
#include "Matrix.h"
#include "MatrixFunctions.h"
int main(int argc, char * argv[])
{
    
    Matrix m(2,2);
    m(0,0) = 1;
    m(0,1) = 2;
    m(1,0) = 2;
    m(1,1) = 5;
    
    cout << "A:" << m << endl;
    
    double arr[] = {2,5};
    ColumnVector b(arr,2);
    cout << "b:" << b << endl;
/*
    Matrix b(2,1);
    b.populateRandom();
*/
    
    cout << gaussJordan(m,b) << endl;   

    return 0;
}