/*
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
/*
    m.populateRandom();
    b.populateRandom();

    cout << "answer with gaussJordan:" << gaussJordan(m,b) << endl;
    cout << "answer with gaussianElimination: " << gaussianElimination(m,b) << endl;   

    return 0;
}
*/



/*
#include <iostream>
using namespace std;
#include "Matrix.h"
#include "MatrixFunctions.h"
#include <boost/progress.hpp>
int main(int argc, char * argv[])
{
    boost::progress_timer t;
    // time gaussJordan: 7.75 s
    // time gaussianElimination: 4.10 s
	for (int i=1;i<100;i++)
    {
        Matrix *a = new Matrix(i,i);
        a->populateRandom();
        
        ColumnVector *b = new ColumnVector(i);
        b->populateRandom();
        
        gaussianElimination(*a,*b);
        cout << i << endl;
    }
    
	return 0;
}
*/

#include <iostream>
using namespace std;
#include "Matrix.h"
#include "MatrixFunctions.h"
#include <boost/progress.hpp>
int main(int argc, char * argv[])
{
    Matrix m(3,3);
    m.populateIdentity();
    m(1,0) = 2;
    cout << m << endl;
    cout << m.inverse() << endl;
    cout << m*m.inverse() << endl;
    return 0;
}