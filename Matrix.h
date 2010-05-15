#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
# include <boost/iterator/iterator_facade.hpp>

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

class MatrixIterator; // forward declaration necessary


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
        int rows() const;
        
        /** Returns the number of columns in the matrix. */
        int cols() const;
        
        /** Creates a Matrix object from a 2d vector of doubles. */
        Matrix(std::vector<std::vector<double> >& a);

        /** Creates a Matrix object from an array of doubles.
            The array should be a 1-d array, even if it is
            a matrix. The # of rows and # of columns are then
            passed as the second and third parameter. For example:
            
            \code
            // Here we're creating a 2x2 identity matrix:
            double v[] = {1,0,0,1};
            Matrix A(v,2,2);
            
            // print out the matrix:
            cout << A << endl;
            \endcode
        */
        Matrix(double *a, int rows, int cols);

        
        /** Populates the matrix with random integers in the range 0-9. */
        Matrix& populateRandom();

        /** Populates the matrix with random integers in the range 0-9. Ensures that the matrix is symmetric. */
        Matrix& populateSymmetric();

        /** Makes this matrix an identity matrix. Throws an error if 
        this is not a square matrix. */
        Matrix& populateIdentity();
        
        /** Returns a Matrix object that is the transpose of the current Matrix. */
        Matrix transpose();

        /** Returns a Matrix object that is the inverse of the current Matrix. */
        Matrix inverse();
        
        /** Returns the determinant of the Matrix. */
        double det();
        
        /** This allows you to access the elements in the matrix using subscripts.

            Example:
            \code
                Matrix m(10,10);        // create a 10x10 Matrix
                m(0,0) = 10;            // set it's first element to 10
                cout << m(9,9) << endl; // print it's last element
            \endcode
            This is similar to MATLAB's notation for matrices, but our matrices
            are zero-indexed.
            Data is accessed via (row#, colunm#).
        */
        double& operator()(int i, int j) const;
        
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
        
        /** Returns an iterator to the beginning of the matrix. */
        MatrixIterator begin() const;

        /** Returns an iterator to one past the end of the matrix. */
        MatrixIterator end() const;
        
    protected:
        /** Here's where the matrix is actually stored. */
        std::vector<std::vector<double> > mutable data;
};

/** \var static const Matrix NullMatrix(0,0)
    The NullMatrix is a special type of Matrix with zero rows and zero columns.
    If a function is supposed to return a Matrix object, but an error has occured
    and it can't return the proper object, it should return a Matrix with zero rows
    and zero columns by saying:
    
    \code
    return new Matrix(0,0);
    \endcode
    
    The return type should be compared with NullMatrix. For example, gaussJordan
    and gaussianElimination both return a Matrix with zero rows and zero columns
    if no solution could be found; one way to use these functions would be:
    
    \code
    Matrix x = gaussianElimination(A,b); // where A and b are two previously defined matrices
    if (x == NullMatrix)
    {
        // uh oh!
    }else { ... }
    
    \endcode
*/
static const Matrix NullMatrix(0,0);

/*! \fn Matrix operator*(const Matrix &a, const Matrix &b);
   
    Multiplies two matrices and returns the resulting Matrix object.
*/
Matrix operator*(const Matrix &a, const Matrix &b);


/*! \fn Matrix operator*(const double s, const Matrix &a);
   
    Multiplies a Matrix object by a scalar (double) and returns the resulting Matrix object.
*/
Matrix operator*(const double s, const Matrix &a);


/*! \fn Matrix operator*(const Matrix &a, const double s);
   
    Multiplies a Matrix object by a scalar (double) and returns the resulting Matrix object.
*/
Matrix operator*(const Matrix &a, const double s);


/*! \fn Matrix operator+(const Matrix &a, const Matrix &b);
    
    Adds two Matrix objects elementwise and returns the resulting Matrix object.
*/
Matrix operator+(const Matrix &a, const Matrix &b);


/*! \fn Matrix operator-(const Matrix &a, const Matrix &b);
    
    Subtracts the second matrix from the first matrix returns the resulting Matrix object.
*/
Matrix operator-(const Matrix &a, const Matrix &b);


/*! \fn std::ostream& operator<<(std::ostream& s, const Matrix &m);
    
    Prints out a Matrix object.
*/
std::ostream& operator<<(std::ostream& s, const Matrix &m);


/*! \fn bool operator==(const Matrix &a, const Matrix &b);
    
    Tests if two Matrix objects are equivalent.
*/
bool operator==(const Matrix &a, const Matrix &b);


/** The RowVector class, which inherits from the general Matrix class.
    If you want to do vector-specific operations like get the length of the vector,
    use this class instead of the Matrix class.
    
*/
class RowVector : public Matrix {
    public:
        /** Creates a RowVector of the specified length. */
        explicit RowVector(int c) : Matrix(1,c) {}
        
        /** Creates a RowVector from a vector of doubles. */
        RowVector(std::vector<double> &a);
        
        /** Creates a RowVector from an array of doubles,
            with the size of the array as the second argument. */
        RowVector(double *a, int size);

        /** Creates a RowVector from a Matrix */
        RowVector(Matrix a) : Matrix(a) {};
        
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
        explicit ColumnVector(int r) : Matrix(r,1) {}        

        /** Creates a ColumnVector from a vector of doubles. */
        ColumnVector(std::vector<double> &a);

        /** Creates a ColumnVector from an array of doubles,
            with the size of the array as the second argument. */
        ColumnVector(double *a, int size);

        /** Creates a ColumnVector from a Matrix */
        ColumnVector(Matrix a) : Matrix(a) {};

        /** Calculates and returns the length of the vector. */
        double length() ;

        /** This method is undefined for a ColumnVector since a ColumnVector
            can only have one column. */
        void appendCol();
};

/** The MatrixIterator class. When you ask for an iterator to a Matrix object,
    you get back a MatrixIterator.
*/

class MatrixIterator : public boost::iterator_facade<MatrixIterator, double, boost::bidirectional_traversal_tag>
{
    public:
        /** Default constructor. */
        MatrixIterator() : m(0), row(0), col(0) {};
        
        /** Create a MatrixIterator out of a Matrix.
            The MatrixIterator points to the first element in the Matrix.
        */
        MatrixIterator(const Matrix& other) : m(&other), row(0), col(0) {};

        /** Create a MatrixIterator out of a Matrix.
            The MatrixIterator points to the element in the Matrix
            at row arow and column acol.
        */
        MatrixIterator(const Matrix& other, const int arow, const int acol) : m(&other), row(arow), col(acol) {};

        /** Copy constructor. */
        MatrixIterator(const MatrixIterator&);
    private:    
        friend class boost::iterator_core_access;        
        
        /** Access the value referred to. */
        double& dereference() const;
        
        /** Compare for equality with another iterator. */
        bool equal(const MatrixIterator&) const;
        
        /** Advance by one position. */
        void increment();
        
        /** Retreat by one position. */
        void decrement();
        
        /** Advance by n positions. */
        void advance(int);
        
        /** Measure the distance to another iterator. */
        int distance_to(MatrixIterator) const;
        
        /** the element we're pointing to in the matrix. */
        const Matrix *m;
        int row;
        int col;
};

#endif