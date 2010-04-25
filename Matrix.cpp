#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
#include "Matrix.h"
#include "MatrixFunctions.h"
#include <boost/shared_ptr.hpp>
using namespace std;
using boost::shared_ptr;
Matrix::Matrix(int r, int c)
{
    /* 
        since 'data' is a vector,
        it will run the default constructor
        of all the members. So all members
        will automatically be initialized to 0.
        
    */
    assert(r>=0);
    assert(c>=0);
    data.resize(r);
    for (int i=0;i<r;i++)
    {
        data[i].resize(c);
    }    
}

int Matrix::rows() 
{
    return data.size();
}

int Matrix::cols() 
{
    return data[0].size();
}


// Create a matrix from a vector.
Matrix::Matrix(vector<vector<double> >& a)
{
    int rows = a.size();
    int cols = a[0].size();
    data.resize(rows);
    for (int i=0;i<rows;i++)
    {
        data[i].resize(cols);
        data[i].assign(a[i].begin(),a[i].end());
    }
    
}

// Matrix from array
Matrix::Matrix(double *a, int rows, int cols)
{
    data.resize(rows);
    for (int i=0;i<rows;i++)
    {
        data[i].resize(cols);
        data[i].assign(&a[i*rows],&a[(i*rows)+cols]);
    }
}

// append a row
void Matrix::appendRow(std::vector<double>& r)
{
    assert(cols()==r.size());
    data.resize(data.size()+1);
    
    int f = rows()-1;
    data[f].resize(r.size());
    data[f].assign(r.begin(),r.end());
}

// append a row - array version
void Matrix::appendRow(double *r, int size)
{
    assert(cols()==size);
    data.resize(data.size()+1);
    
    int f = rows()-1;
    data[f].resize(size);
    data[f].assign(r,&r[size]);
}

/*  append a row - matrix version
    we use resize because if the matrix is quite big,
    resize is going to be more efficient than adding
    elements with push_back.    
*/

void Matrix::appendRow(Matrix& b)
{
    assert(b.cols() == cols());
    int cur_rows = rows();
    data.resize(rows()+b.rows());
    
    for (int i=cur_rows;i<rows();i++)
    {
        data[i].resize(cols());
        for (int j=0;j<cols();j++)
        {
            data[i][j] = b(i-cur_rows,j);
        }
    }
}

// append a col - matrix version
void Matrix::appendCol(Matrix& b)
{
    assert(b.rows() == rows());
    int cur_cols = cols();
    
    for (int i=0;i<rows();i++)
    {
        data[i].resize(cur_cols + b.cols());
        for (int j=cur_cols;j<cur_cols + b.cols();j++)
        {
            data[i][j] = b(i,j-cur_cols);
        }
    }
}

// append a col
void Matrix::appendCol(std::vector<double>& r)
{
    assert(rows()==r.size());
    int cur_cols = cols();
    for (int i=0;i<r.size();i++)
    {
        data[i].resize(cur_cols + 1);
        data[i][cur_cols] = r[i];
    }
}

// append a col
void Matrix::appendCol(double *r, int size)
{
    assert(rows()==size);
    int cur_cols = cols();
    for (int i=0;i<size;i++)
    {
        data[i].resize(cur_cols + 1);
        data[i][cur_cols] = r[i];
    }
}

// populate the matrix with random numbers in the range 0-9
Matrix& Matrix::populateRandom()
{
    srand ( time(NULL) ); // seed the matrix
    for (int i=0;i<rows();i++)
    {
        for (int j=0;j<cols();j++)
        {
            data[i][j] = rand() % 10;
        }                
    }            
    return *this;
}

Matrix& Matrix::populateIdentity()
{
    // if it's not a square matrix, we cant make an identity matrix.
    assert(cols() == rows());
    
    for (int i=0;i<rows();i++)
    {
        for (int j=0;j<cols();j++)
        {
            if(i==j){
                data[i][j] = 1;                
            }else{
                data[i][j] = 0;
            }
        }        
    }
    
    return *this;
}


/* Returns an iterator to the beginning of the matrix. */
MatrixIterator Matrix::begin()
{
    shared_ptr<MatrixIterator> m(new MatrixIterator(this));
    return *m;
}

/* Returns an iterator to one past the end of the matrix. */
MatrixIterator Matrix::end()
{
    shared_ptr<MatrixIterator> m(new MatrixIterator(this,this->rows(), 0));
    return *m;
}


// how to multiply two Matrix objects
Matrix operator*( Matrix &a,  Matrix &b)
{
    assert(a.cols() > 0);
    assert (a.cols() == b.rows());
    vector<vector<double> > c;
    c.resize(a.rows());
    
    for (int i=0;i<a.rows();i++)
    {
        c[i].resize(b.cols());
        for (int j=0;j<b.cols();j++)
        {
            c[i][j] = 0;
            for (int k=0;k<a.cols();k++)
            {
                 c[i][j] += a(i,k)*b(k,j);
            }
        }
    }

    shared_ptr<Matrix> res(new Matrix(c));
    return *res;
}

// a scalar * a matrix
Matrix operator*(double s, Matrix &a)
{
    shared_ptr<Matrix> b(new Matrix(a.rows(), a.cols()));
    
    for (int i=0;i<a.rows();i++)
    {
        for (int j=0;j<a.cols();j++)
        {
            (*b)(i,j) = s * a(i,j);
        }        
    }
    return *b;
}

// a scalar * a matrix (the other way)
Matrix operator*(Matrix &a, double s)
{
    return s * a;

}


// how to add two matrices
Matrix operator+(Matrix &a, Matrix &b){
    assert(a.cols() == b.cols() && a.rows() == b.rows());    
    shared_ptr<Matrix> c(new Matrix(a.rows(),a.cols()));
    
    for (int i=0;i<a.rows();i++)
    {
        for (int j=0;j<a.cols();j++)
        {
            (*c)(i,j) = a(i,j) + b(i,j);
        }        
    }
    
    return *c;
}

// how to subtract two matrices
Matrix operator-(Matrix &a, Matrix &b){
    assert(a.cols() == b.cols() && a.rows() == b.rows());    
    shared_ptr<Matrix> c(new Matrix(a.rows(),a.cols()));
    
    for (int i=0;i<a.rows();i++)
    {
        for (int j=0;j<a.cols();j++)
        {
            (*c)(i,j) = a(i,j) - b(i,j);
        }        
    }
    
    return *c;
}

// how to print out a matrix
ostream& operator<<(ostream& s,  Matrix &m)
{
    s << "[ " << endl;
    for (int i=0;i<m.rows();i++)
    {
        s << "[";
        for (int j=0;j<m.cols();j++)
        {
            s << " " << m(i,j) << " ";
        }
        s << "]" << endl;
    }
    s << "]" << endl;
}

// access the data in the matrix directly
double& Matrix::operator()(int i, int j)
{
    return data[i][j];
}

Matrix Matrix::transpose()
{
    shared_ptr<Matrix> c(new Matrix(cols(),rows()));
    for (int i=0;i<rows();i++)
    {
        for (int j=0;j<cols();j++)
        {
            (*c)(j,i) = data[i][j];
        }        
    }
    return *c;
}

// get the inverse of the matrix
Matrix Matrix::inverse()
{
    assert(rows() == cols()); // must be a square matrix
    
    // just solve for the identity matrix using Gauss-Jordan.
    shared_ptr<Matrix> b(new Matrix(rows(),cols()));
    b->populateIdentity();
    return gaussJordan(*this,*b);
}

// test two Matrix objects to see if they are equal
bool operator==(Matrix &a, Matrix &b)
{
    if(a.cols() != b.cols() && a.rows() != b.rows()) { return false; }    
    for (int i=0;i<a.rows();i++)
    {
        for (int j=0;j<a.cols();j++)
        {
            if(a(i,j)!=b(i,j))
            {
                return false;
            }
        }        
    }
    return true;
}

void Matrix::swapRows(int rowA, int rowB)
{
    assert(rowA >= 0 && rowB >= 0 && rowA < rows() && rowB < rows());

    double temp[cols()];
    
    for (int i=0;i<cols();i++)
    {
        temp[i] = data[rowA][i];
        data[rowA][i] = data[rowB][i];
        data[rowB][i] = temp[i];
    }    
}

void Matrix::swapCols(int colA, int colB)
{
    assert(colA >= 0 && colB >= 0 && colA < cols() && colB < cols());
    
    int temp[rows()];
    
    for (int i=0;i<rows();i++)
    {
        temp[i] = data[i][colA];
        data[i][colA] = data[i][colB];
        data[i][colB] = temp[i];
    }    
}

/* RowVector */
double RowVector::length() 
{
    double sum = 0;
    for (int i=0;i<cols();i++)
    {
        sum += data[0][i] * data[0][i];
    }
    return sqrt(sum);
}

RowVector::RowVector(std::vector<double> &a) : Matrix(1,a.size())
{
    for (int i=0;i<cols();i++)
    {
        data[0][i] = a[i];
    }    
}

RowVector::RowVector(double *a, int size) : Matrix(1,size)
{
    for (int i=0;i<cols();i++)
    {
        data[0][i] = a[i];
    }        
}

/* ColumnVector */
double ColumnVector::length() 
{
    double sum = 0;
    for (int i=0;i<rows();i++)
    {
        sum += data[i][0] * data[i][0];
    }
    return sqrt(sum);
}

ColumnVector::ColumnVector(std::vector<double> &a) : Matrix(a.size(),1)
{
    for (int i=0;i<rows();i++)
    {
        data[i][0] = a[i];
    }    
}

ColumnVector::ColumnVector(double *a, int size) : Matrix(size,1)
{
    for (int i=0;i<rows();i++)
    {
        data[i][0] = a[i];
    }        
}

/* MatrixIterator. */

/* Copy constructor. */
MatrixIterator::MatrixIterator(const MatrixIterator& other)
{
    this->m = other.m;
    this->row = other.row;
    this->col = other.col;
}

/** Access the value referred to. */
double& MatrixIterator::dereference() const
{
    return ((*m)(row,col));
}

/** Compare for equality with another iterator. */
bool MatrixIterator::equal(const MatrixIterator& other) const
{
    return (this->row == other.row && this->col == other.col && this->m == other.m);
}

/** Advance by one position. */
void MatrixIterator::increment()
{
    /*  if we're at the last column of the current row,
        go to the next row. */        
    if (col==(m->cols()-1))
    {
        col = 0;
        row++;
    }else{
        col++;
    }
}

/** Retreat by one position. */
void MatrixIterator::decrement()
{
    /*  if we're at the first column of the current row,
        go to the previous row. */        
    if (col==0)
    {
        col = m->cols() - 1;
        row--;
    }else{
        col--;
    }
}

/** Advance by n positions. */
void MatrixIterator::advance(int n)
{
    int addrows = floor(n/(m->cols()));
    int addcols = n % m->cols();
    col += addcols;
    row += addrows;
}

/** Measure the distance to another iterator. */
int MatrixIterator::distance_to(MatrixIterator other) const
{
    int my_abs_location = (row * m->cols()) + col;
    int other_abs_location = (other.row * other.m->cols()) + other.col;
    return other_abs_location - my_abs_location;
}