#include <iostream>
using namespace std;
#include "Matrix.h"
#include "MatrixFunctions.h"
int main(int argc, char * argv[])
{
    Matrix m(2,2);
    m.populateRandom();
    cout << m << endl;
    Matrix b(2,1);
    b.populateRandom();
    
    cout << gaussJordan(m,b) << endl;   

    return 0;
}