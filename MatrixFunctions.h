#ifndef MATRIXFUNCTIONS_H
#define MATRIXFUNCTIONS_H

#include <iostream>
#include <vector>
#include "Matrix.h"
#include "boost/tuple/tuple.hpp"

/*! \file MatrixFunctions.h
    
    This file contains the declarations of the basic Linear Algebra classes
    and some methods that operate on them.
*/

/** \fn int findNonZero(Matrix &m, int col);
    
    Given a Matrix and a column number, this functions
    returns the index of the first row which has a non-zero
    value in that column. If all rows have zeroes, it returns -1.
    This function is used by both gaussJordan and gaussianElimination.
*/
int findNonZero(Matrix &m, int col);

/** \fn Matrix& gaussJordan(Matrix& A, Matrix& b);
    
    Given two matrices A and b, solves the linear system of equations
    assuming the form Ax = b. Uses Gauss-Jordan. Returns a Matrix
    object containing the solution.
*/
Matrix& gaussJordan(Matrix& A, Matrix& b);

/** \fn Matrix& gaussianElimination(Matrix& A, Matrix& b);
    
    Given two matrices A and b, solves the linear system of equations
    assuming the form Ax = b. Uses Gaussian Elimination with backsubstitution.
    Returns a Matrix object containing the solution.
*/
Matrix& gaussianElimination(Matrix& A, Matrix& b);

/** \fn boost::tuple<Matrix, Matrix, Matrix> LUPDecompose(Matrix A);
    
    Given a matrix, returns it's LUP decomposition. Three matrices L, U and P
    are returned as a boost tuple. Example usage:
    \code
    #include "boost/tuple/tuple.hpp"

    // create a new matrix
    Matrix A(3,3);
    A.populateRandom();
  
    // get its decomposition
    boost::tuple<Matrix,Matrix,Matrix> lu = LUPDecompose(A);
    Matrix L = lu.get<0>();
    Matrix U = lu.get<1>();
    Matrix P = lu.get<2>();
    
    // print out matrices
    cout << L << endl;
    cout << U << endl;
    cout << P << endl;
    \endcode
*/
boost::tuple<Matrix, Matrix, Matrix> LUPDecompose(Matrix A);
#endif