#ifndef MATRIXFUNCTIONS_H
#define MATRIXFUNCTIONS_H

#include <iostream>
#include <vector>
#include "Matrix.h"

int findNonZero(Matrix &m, int col);

// Given two matrices A and b, solves the linear
// system of equations assuming the form Ax = b.
ColumnVector& gaussJordan(Matrix& A, Matrix& b);

#endif