#include <memory>
#include "MatrixFunctions.h"
#include "Matrix.h"
#include <boost/tuple/tuple.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;
using boost::shared_ptr;
// returns the # of first row of this matrix that
// has a non-zero value in the given column
int findNonZero(Matrix &m, int col)
{
    // initial row to look at has to be the current row:
    // we can NOT look above! That would be a disaster.
    for (int i=col;i<m.rows();i++)
    {
        if(m(i,col)!=0)
        {
            return i;
        }
    }
    return -1;
}

// Given two matrices A and b, solves the linear system of equations
// assuming the form Ax = b. Uses Gauss-Jordan.
Matrix gaussJordan(Matrix& A, Matrix& b)
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
            shared_ptr<ColumnVector> n(new ColumnVector(0));
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
    
    // at this point, the augmented part of Aug contains our solution.
    // Let's return it.
    
    shared_ptr<Matrix> res(new Matrix(b.rows(), b.cols()));
    for (int x=0;x<A.rows();x++)
    {
        for (int y=A.cols();y<A.cols() + b.cols();y++)
        {

            (*res)(x,y-A.cols()) = Aug(x,y);
        }
    }
        
    return *res;
}


// Given two matrices A and b, solves the linear system of equations
// assuming the form Ax = b. Uses Gaussian Elimination with backsubstitution.
Matrix gaussianElimination(Matrix& A, Matrix& b)
{
    // First let's get it in row-echelon form.
    // This code is actually very similar to the code for
    // gaussJordan(). The big difference is we set j=i
    // as the starting condition in a for loop so we only
    // work on the lower triangle.
    
    Matrix Aug = A;
    Aug.appendCol(b); // make the augmented matrix
    int i;
    for (i=0;i<A.cols();i++)
    {
        int goodRow = findNonZero(Aug, i);
        
        // either we don't have enough equations, or there's
        // a logical error, like -1 = 0. Either way, no solution.
        if (goodRow < 0)
        {
            shared_ptr<ColumnVector> n(new ColumnVector(0));
            return *n;
        }
        
        // swap the good row with the row we want a 1 in.
        // we want 1's on the diagonal, so the row we want 
        // a 2 in is the same # as the column that we're on.
        Aug.swapRows(i, goodRow);

        // Now we want to zero out this column for all other rows.
        // In this row (in the diagonal position) we want a 1.
        for (int j=i;j<A.rows();j++)
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
    
    // At this point, our Matrix is in row echelon form.
    // Now we do backsubstitution.
    
    // start from the last row, work our way up.
    for (int x=Aug.rows()-2;x>=0;x--)
    {
        for (int y=A.cols()-1;y>x;y--)
        {
            // set the augmented columns values to the answer.
            for (int z=A.cols();z<A.cols() + b.cols();z++)
            {
                Aug(x,z) = Aug(x,z) - (Aug(x,y) * Aug(y,z));
            }
            // set the substituted column to zero since we moved it
            // to the other side of the = sign.
            Aug(x,y) = 0;
        }
    }
    
    // at this point, the augmented part of Aug contains our solution.
    // Let's return it.
    
    shared_ptr<Matrix> res(new Matrix(b.rows(), b.cols()));
    for (int x=0;x<A.rows();x++)
    {
        for (int y=A.cols();y<A.cols() + b.cols();y++)
        {

            (*res)(x,y-A.cols()) = Aug(x,y);
        }
    }
        
    return *res;
}

boost::tuple<Matrix, Matrix, Matrix> LUPDecompose(Matrix A)
{
    /* although not required ofr general LU decomposition, we require
       matrices to be square. */
    assert(A.rows()==A.cols());
    Matrix L(A.rows(),A.cols());
    shared_ptr<Matrix> P(new Matrix(A.rows(),A.cols())); // permutation matrix    
    L.populateIdentity();
    P->populateIdentity();
    Matrix Lfinal(L);
    /* gaussian Elimination to get us in upper triangular form. */
    for (int c=0;c<A.cols();c++)
    {    
        int goodRow = findNonZero(A, c);
        
        // either we don't have enough equations, or there's
        // a logical error, like -1 = 0. Either way, no solution.
        if (goodRow < 0)
        {
            shared_ptr<Matrix> l(new Matrix(0,0));
            shared_ptr<Matrix> u(new Matrix(0,0));
            shared_ptr<Matrix> p(new Matrix(0,0));
            return boost::make_tuple(*l,*u,*p);
        }
        
        // swap the good row with the row we want a 1 in.
        // we want 1's on the diagonal, so the row we want 
        // a 2 in is the same # as the column that we're on.
        A.swapRows(c, goodRow);
        
        // adjust L-inverse if we did have to swap a row
        // (i.e. the good row wasn't the current diagonal)
        if (goodRow != c)
        {
            (*P)(c,c) = 0;
            (*P)(c,goodRow) = 1;
            (*P)(goodRow,c) = 1;
            (*P)(goodRow,goodRow) = 0;
        }
        
        for (int r=c+1;r<A.rows();r++)
        {
            if (r==c) {
                // we want a 1 here.
                double scalar = A(c,c);
                /* set L-inverse to reflect this. */
                L(c,c) = 1.0/scalar;
                for (int k=0;k<A.cols();k++)
                {
                    /* multiply through by 1/x to make the current cell = 1. */
                    A(r,k) = A(r,k) * (1.0/scalar);
                }                
            }else{
                // we want a 0 here
                if (A(r,c) == 0) continue;
                double multiplier = A(r,c) / A(c,c);
                /* set L-inverse to reflect this. */
                L(r,c) = multiplier;
                for (int k=0;k<A.cols();k++)
                {
                    A(r,k) = A(r,k) - (A(c,k) * multiplier);
                }                                                
            }
            
/*
            Lfinal = L*Lfinal;
            L.populateIdentity();
*/
        }

    }
    Matrix *L2 = &(L);
    Matrix *U = &A;
    return boost::make_tuple(*L2, *U, *P);
    
}

/* checks if a matrix is symmetric. */
bool isSymmetric(Matrix &A)
{
    // not square, so definitely not symmetric.
    if (A.rows() != A.cols()) return false;
    
    if (A.transpose() == A) return true;
    
    return false;
}


/* solve Ax=b using the Method of Steepest Descent. */
Matrix steepestDescent(Matrix& A, Matrix& b)
{
    // the Method of Steepest Descent *requires* a symmetric matrix.
    if (isSymmetric(A)==false)
    {
        shared_ptr<Matrix> nullMat(new Matrix(0,0));
        return *nullMat;
    }
    
    
}