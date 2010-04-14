#include "MatrixFunctions.h"
#include "Matrix.h"
using namespace std;

// returns the # of first row of this matrix that
// has a non-zero value in the given column
int findNonZero(Matrix &m, int col)
{
    for (int i=col;i<m.rows();i++)
    {
        if(m(i,col)!=0)
        {
            return i;
        }
    }
    return -1;
}

ColumnVector& gaussJordan(Matrix& A, Matrix& b)
{
    Matrix Aug = A;
    Aug.appendCol(b); // make the augmented matrix
    for (int i=0;i<A.cols();i++)
    {
        int goodRow = findNonZero(Aug, i);
        
        // either we don't have enough equations, or there's
        // a logical error, like -1 = 0. Either way, no solution.
        if (goodRow < 0)
        {
            cout << "no solution possible." << endl;
            ColumnVector *n = new ColumnVector(0);
            return *n;
        }
        
        // swap the good row with the row we want a 1 in.
        // we want 1's on the diagonal, so the row we want 
        // a 2 in is the same # as the column that we're on.
        Aug.swapRows(i, goodRow);

        // Now we want to zero out this column for all other rows.
        // In this row (in the diagonal position) we want a 1.
        for (int j=0;j<A.rows();j++)
        {
            if (j==i) {
                // we want a 1 here.
                double scalar = Aug(i,i);
                for (int k=0;k<Aug.cols();k++)
                {
                    Aug(i,k) = Aug(i,k) * (1.0/scalar);
                }                
            }else{
                // we want a 0 here
                double multiplier = Aug(j,i) / Aug(i,i);
                for (int k=0;k<Aug.cols();k++)
                {
                    Aug(j,k) = Aug(j,k) - (Aug(i,k) * multiplier);
                }                                                
            }
        }
    }
    
    // at this point, the last column of Aug contains our solution.
    // Let's return it.
    
    ColumnVector *res = new ColumnVector(A.rows());
    for (int x=0;x<A.rows();x++)
    {
        (*res)(x,0) = Aug(x,Aug.cols()-1);
    }
        
    return *res;
}

