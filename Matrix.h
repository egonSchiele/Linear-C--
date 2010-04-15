#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

/*! \mainpage LinearC++ Documentation
 *
 * \section intro_sec Introduction
 *
 * This is the reference documentation for LinearC++,
 * a very basic library for doing Linear Algebra using C++.
 */

/*! \file Matrix.h
    
    This file contains the declarations of the basic Linear Algebra classes
    and some methods that operate on them.
*/


/**
    The general Matrix class. Defines several methods to create and populate matrices.
    Each element in a matrix is a double.
    
    If you really want a vector instead, use RowVector or ColumnVector. This allows
    for additional operations such as length().
*/

class Matrix {
    public:


        /** Creates a zero matrix of the given size.
            Will throw an error if you try to create a matrix
            of negative dimensions.
        */
        Matrix(int r, int c);
        
        /** Returns the number of rows in the matrix. */
        int rows();
        
        /** Returns the number of columns in the matrix. */
        int cols();
        
        /** Creates a Matrix object from a 2d vector of doubles. */
        Matrix(std::vector<std::vector<double> >& a);
        
        /** Populates the matrix with random integers in the range 0-9. */
        Matrix& populateRandom();
        
        /** Makes this matrix an identity matrix. Throws an error if 
        this is not a square matrix. */
        Matrix& populateIdentity();
        
        /** Returns a Matrix object that is the transpose of the current Matrix. */
        Matrix& transpose();

        /** Returns a Matrix object that is the inverse of the current Matrix. */
        Matrix& inverse();
        /** This allows you to access the elements in the matrix using subscripts.

            Example:
                Matrix m(10,10);        // create a 10x10 Matrix
                m(0,0) = 10;            // set it's first element to 10
                cout << m(9,9) << endl; // print it's last element

            This is similar to MATLAB's notation for matrices, but our matrices
            are zero-indexed.
        */
        double& operator()(int i, int j);
        
        /** Adds a row to the current Matrix object.
            The new row must be the same length as all the other
            rows in the matrix.
        */
        virtual void appendRow(Matrix &b);
                
        /** Same as appendRow, but takes an array as the first argument
            and the length of the array as the second argument.
        */
        virtual void appendRow(double *r, int size);
        
        /** Same as appendRow, but takes a vector. */
        virtual void appendRow(std::vector<double> &r);

        
        /** Adds a column to the current Matrix object.
            The new column must be the same length as all the other
            column in the matrix.
        */
        virtual void appendCol(Matrix& b);

        /** Same as appendCol, but takes an array as the first argument
            and the length of the array as the second argument.
        */
        virtual void appendCol(double *r, int size);

        /** Same as appendCol, but takes a vector. */
        virtual void appendCol(std::vector<double> &r);
        
        /** Swaps the given rows in the Matrix. */
        void swapRows(int rowA, int rowB);

        /** Swaps the given cols in the Matrix. */
        void swapCols(int colA, int colB);

    protected:
        /** Here's where the matrix is actually stored. */
        std::vector<std::vector<double> > data;
};


/*! \fn Matrix& operator*(Matrix &a,  Matrix &b);
   
    Multiplies two matrices and returns the resulting Matrix object.
*/
Matrix& operator*(Matrix &a,  Matrix &b);


/*! \fn Matrix& operator*(double s, Matrix &a);
   
    Multiplies a Matrix object by a scalar (double) and returns the resulting Matrix object.
*/
Matrix& operator*(double s, Matrix &a);


/*! \fn Matrix& operator*(Matrix &a, double s);
   
    Multiplies a Matrix object by a scalar (double) and returns the resulting Matrix object.
*/
Matrix& operator*(Matrix &a, double s);


/*! \fn Matrix& operator+(Matrix &a, Matrix &b);
    
    Adds two Matrix objects elementwise and returns the resulting Matrix object.
*/
Matrix& operator+(Matrix &a, Matrix &b);


/*! \fn Matrix& operator-(Matrix &a, Matrix &b);
    
    Subtracts the second matrix from the first matrix returns the resulting Matrix object.
*/
Matrix& operator-(Matrix &a, Matrix &b);


/*! \fn std::ostream& operator<<(std::ostream& s,  Matrix &m);
    
    Prints out a Matrix object.
*/
std::ostream& operator<<(std::ostream& s,  Matrix &m);


/*! \fn bool operator==(Matrix &a, Matrix &b);
    
    Tests if two Matrix objects are equivalent.
*/
bool operator==(Matrix &a, Matrix &b);


/** The RowVector class, which inherits from the general Matrix class.
    If you want to do vector-specific operations like get the length of the vector,
    use this class instead of the Matrix class.
    
*/
class RowVector : public Matrix {
    public:
        /** Creates a RowVector of the specified length. */
        RowVector(int c) : Matrix(1,c) {}
        
        /** Creates a RowVector from a vector of doubles. */
        RowVector(std::vector<double> &a);
        
        /** Creates a RowVector from an array of doubles,
            with the size of the array as the second argument. */
        RowVector(double *a, int size);
        
        /** Calculates and returns the length of the vector. */
        double length() ;
        
        /** This method is undefined for a RowVector since a RowVector
            can only have one row. */
        void appendRow();
};


/** The ColumnVector class, which inherits from the general Matrix class.
    If you want to do vector-specific operations like get the length of the vector,
    use this class instead of the Matrix class.    
*/
class ColumnVector : public Matrix {
    public:
        /** Creates a ColumnVector of the specified length. */
        ColumnVector(int r) : Matrix(r,1) {}

        /** Creates a ColumnVector from a vector of doubles. */
        ColumnVector(std::vector<double> &a);

        /** Creates a ColumnVector from an array of doubles,
            with the size of the array as the second argument. */
        ColumnVector(double *a, int size);

        /** Calculates and returns the length of the vector. */
        double length() ;

        /** This method is undefined for a ColumnVector since a ColumnVector
            can only have one column. */
        void appendCol();
};

#endif