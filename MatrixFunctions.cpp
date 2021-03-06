#include <memory>
#include "MatrixFunctions.h"
#include "Matrix.h"
#include <boost/tuple/tuple.hpp>
#include <boost/shared_ptr.hpp>
#include <algorithm>
#include <limits>

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
    
    /* STEP 1: Start with a guess. Our guess is all ones. */
    ColumnVector x(A.cols());
    fill(x.begin(),x.end(),1);
    
    /* This is NOT an infinite loop. There's a break statement inside. */
    while(true)
    {
        /* STEP 2: Calculate the residual r_0 = b - Ax_0 */
        ColumnVector r =  static_cast<ColumnVector> (b - A*x);

        if (r.length() < .01) break;
        
        /* STEP 3: Calculate alpha */
        double alpha = (r.transpose() * r)(0,0) / (r.transpose() * A * r)(0,0);
                
        /* STEP 4: Calculate new X_1 where X_1 = X_0 + alpha*r_0 */
        x = x + alpha * r;
    }
    
    shared_ptr<Matrix> final_x(new Matrix(static_cast<Matrix>(x)));
    
    return *final_x;
}

/* Solve Ax = b using the conjugate gradient method. */
Matrix conjugateGradient(Matrix& A, Matrix& b)
{
    double error_tol = .5;      // error tolerance
    int max_iter = 200;          // max # of iterations
    ColumnVector x(A.rows());   // the solution we will iteratively arrive at
    
    int i = 0;
    ColumnVector r = static_cast<ColumnVector>(b - A*x);
    ColumnVector d = r;
    double sigma_old = 0; // will be used later on, in the loop
    double sigma_new = (r.transpose() * r)(0,0);
    double sigma_0 = sigma_new;
    
    while (i < max_iter && sigma_new > error_tol * error_tol * sigma_0)
    {
        ColumnVector q = A * d;
        double alpha = sigma_new / (d.transpose() * q)(0,0);
        x = x + alpha * d;
        
        if (i % 50 == 0)
        {
            r = static_cast<ColumnVector>(b - A*x);
        }else{
            r = r - alpha * q;
        }
        sigma_old = sigma_new;
        sigma_new = (r.transpose() * r)(0,0);
        double beta = sigma_new / sigma_old;
        d = r + beta * d;
        i++;
    }
    
    shared_ptr<Matrix> final_x(new Matrix(static_cast<Matrix>(x)));    
    return *final_x;
}

/* Solve Ax = b using the Jacobi Method. */
Matrix jacobi(Matrix& A, Matrix& b)
{
    ColumnVector x0(A.rows()); // our initial guess
    ColumnVector x1(A.rows()); // our next guess
    
    // STEP 1: Choose an initial guess
    fill(x0.begin(),x0.end(),1);
    
    // STEP 2: While convergence is not reached, iterate.
    ColumnVector r = static_cast<ColumnVector>(A*x0 - b);
    while (r.length() > 1)
    {
        for (int i=0;i<A.cols();i++)
        {
            double sum = 0;
            for (int j=0;j<A.cols();j++)
            {
                if (j==i) continue;
                sum = sum + A(i,j) * x0(j,0);
                
            }            
            x1(i,0) = (b(i,0) - sum) / A(i,i);
        }
        x0 = x1;
        r = static_cast<ColumnVector>(A*x0 - b);
    }
    
    shared_ptr<Matrix> final_x(new Matrix(static_cast<Matrix>(x0)));
    return *final_x;
}

/*  Solve a linear programming problem using the simplex method.
    Good resource: http://www.slideshare.net/sbishop2/simplex-algorithm
 */
int simplex(Matrix &A, Matrix &b)
{
    /*  we assume that we're given this in a tableau form.
        Matrix A contains all the variables, and
        Matrib b contains all the values.
        
        We also assume that the first row of the Matrices
        contains the values for the objective function.
    */
    
    while(true) // there's a break statement inside.
    {
        /*  STEP 1: Look at the negative values in the first row of A
            to determine the pivot column. We want the largest negative
            value (i.e. the smallest value), because removing that bit
            will increase the objective function the most. For example,
            if we have z -10x -20y = 0, the y is lowering the value more.
        */
        MatrixIterator min_e = min_element(A.begin(),A.begin() + A.cols());
        int pivotCol = min_e - A.begin();
        
        /*  if the minimum value is non-negative, we have found
            the optimal solution.
        */
        if (*min_e >= 0)
        {
            /*  FINAL STEP: Find the values of the variables.
                any variable that is still in the objective function
                has to have a value of 0, so we can zero those columns
                out.
            */
            for (int i=0;i<A.cols();i++)
            {
                if (A(0,i) > 0)
                {
                    for (int j=0;j<A.rows();j++)
                    {
                        A(j,i) = 0;
                    }
                    
                }
            }
            
            return b(0,0);
        }
            
        /*  STEP 2: (Temporarily) Divide all the values in Matrix b by
            the corresponding value in that row that is part of the pivot column
        */
        Matrix c = b;
        for (int i=0;i<b.rows();i++)
        {
            c(i,0) = c(i,0) / A(i,pivotCol);
        }
        
        /*  STEP 3: The least value in b tells us the pivot row.
            The smallest value is the constraining value; it's the
            reason that our result can't be bigger. It's constrained
            by this smallest value.
        */
        MatrixIterator min_val = min_element(c.begin()+1,c.end());
        int pivotRow = min_val - c.begin();
        
        /*  STEP 4: Divide pivot row by pivot value so pivot becomes 1
        */
        double divisor = A(pivotRow,pivotCol);
        for (int i=0;i<A.cols();i++)
        {
            A(pivotRow,i) = A(pivotRow,i) / divisor;
        }
        b(pivotRow,0) = b(pivotRow,0) / divisor;
        
        /*  STEP 5: Zero out the pivot column:
        */
        
        for (int i=0;i<A.rows();i++)
        {
            if (i==pivotRow) continue; // no point doing it for the same row.
            double ratio = A(i,pivotCol) / A(pivotRow, pivotCol);
            for (int j=0;j<A.cols();j++)
            {
                A(i,j) -= ratio * A(pivotRow,j);
            }
            b(i,0) -= ratio * b(pivotRow,0);
        }
    }    
    
    return -10;
}

Matrix convolve(Matrix& A, Matrix &kernel) {
	// have to be odd, otherwise how would we center
	// the kernel on a particular element?
	assert(kernel.rows() % 2 == 1);
	assert(kernel.cols() % 2 == 1);

	int k_w = kernel.cols();
	int k_h = kernel.rows();
	
	shared_ptr<Matrix> ret(new Matrix(A.rows(), A.cols()));

	for (int x = 0; x < A.cols(); x++) {
		for (int y = 0; y < A.rows(); y++) {
			// for each element, apply the filter
			int sum = 0;
			for (int i = 0; i < k_w; i++) {
				for (int j = 0; j < k_h; j++) {
					int x_index = x - (k_w - 1)/2 + i;
					int y_index = y - (k_h - 1)/2 + j;
					if (x_index < 0 || y_index < 0) continue;
					if (x_index >= A.cols() || y_index >= A.rows()) continue;
					sum += A(x_index,y_index) * kernel(i,j);
				}
			}
			(*ret)(x,y) = sum;
		}
	}
	return *ret;
}
