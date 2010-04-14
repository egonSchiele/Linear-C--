#include "MatrixFunctions.h"
#include "Matrix.h"
using namespace std;

// returns the # of first row of this matrix that
// has a non-zero value in the given column
int findNonZero(Matrix &m, int col)
{
    cout << "in findNonZero...col is: " << col << endl;
    for (int i=col;i<m.rows();i++)
    {
        cout << "i: " << i << endl;
        if(m(i,col)!=0)
        {
            return i;
        }
    }
    return -1;
}

Matrix& gaussJordan(Matrix& A, Matrix& b)
{
    Matrix Aug = A;
    Aug.appendCol(b); // make the augmented matrix
    cout << "original matrix" << A << endl;
    cout << "augmented matrix" << Aug << endl;
    cout << "result matrix" << b << endl;
    
    for (int i=0;i<A.cols();i++)
    {
        int goodRow = findNonZero(A, i);
        assert(goodRow >=0);
        
        // swap the good row with the row we want a 1 in.
        // we want 1's on the diagonal, so the row we want 
        // a 2 in is the same # as the column that we're on.
        
        cout << "before swap:" << Aug << endl;
        
        Aug.swapRows(i, goodRow);
        cout << "after swap:" << Aug << endl;
        cout << "col #" << i << endl;
        cout << "aug is:" << Aug << endl;
        
        // Now we want to zero out this column for all other rows.
        for (int j=0;j<A.rows();j++)
        {
            if (j==i) {
                // we want a 1 here.
                double scalar = Aug(i,i);
                cout << "scalar is: " << scalar << endl;
                cout << "1/scalar is: " << 1.0/scalar << endl;
                cout << "division yields: " << (1.0/scalar) * scalar << endl;
                for (int k=0;k<Aug.cols();k++)
                {
                    Aug(i,k) = Aug(i,k) * (1.0/scalar);
                }                
            }
        }
        cout << "after trying to set diagonal to zero, Aug is:" << Aug << endl;
                
    }
    return A;   
}

