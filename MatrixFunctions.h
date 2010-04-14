#ifndef MATRIXFUNCTIONS_H
#define MATRIXFUNCTIONS_H

#include <iostream>
#include <vector>
#include "Matrix.h"

int findNonZero(Matrix &m, int col);
Matrix& gaussJordan(Matrix& A, Matrix& b);

#endif