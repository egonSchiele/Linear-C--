#ifndef MATRIXFUNCTIONS_H
#define MATRIXFUNCTIONS_H

#include <iostream>
#include <vector>
#include "Matrix.h"

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

/** \fn ColumnVector& gaussJordan(Matrix& A, Matrix& b);
    
    Given two matrices A and b, solves the linear system of equations
    assuming the form Ax = b. Uses Gauss-Jordan. Returns a ColumnVector
    object containing the solution.
*/
ColumnVector& gaussJordan(Matrix& A, Matrix& b);

/** \fn ColumnVector& gaussianElimination(Matrix& A, Matrix& b);
    
    Given two matrices A and b, solves the linear system of equations
    assuming the form Ax = b. Uses Gaussian Elimination with backsubstitution.
    Returns a ColumnVector object containing the solution.
*/
ColumnVector& gaussianElimination(Matrix& A, Matrix& b);

#endif