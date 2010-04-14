#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <cmath>
#include "Matrix.h"
using namespace std;

Matrix::Matrix(int r, int c)
{
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

// create the matrix from a vector
Matrix::Matrix(vector<vector<int> >& a)
{
    int rows = a.size();
    int cols = a[0].size();
    data.resize(rows);
    for (int i=0;i<rows;i++)
    {
        data[i].resize(cols);
        for (int j=0;j<cols;j++)
        {
            data[i][j] = a[i][j];
        }
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

// how to multiply two Matrix objects
Matrix& operator*( Matrix &a,  Matrix &b)
{
    assert(a.cols() > 0);
    assert (a.cols() == b.rows());
    vector<vector<int> > c;
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

    Matrix *res = new Matrix(c);
    return *res;
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
int& Matrix::operator()(int i, int j)
{
    return data[i][j];
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

RowVector::RowVector(std::vector<int> &a) : Matrix(1,a.size())
{
    for (int i=0;i<cols();i++)
    {
        data[0][i] = a[i];
    }    
}

RowVector::RowVector(int *a, int size) : Matrix(1,size)
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

ColumnVector::ColumnVector(std::vector<int> &a) : Matrix(a.size(),1)
{
    for (int i=0;i<rows();i++)
    {
        data[i][0] = a[i];
    }    
}

ColumnVector::ColumnVector(int *a, int size) : Matrix(size,1)
{
    for (int i=0;i<rows();i++)
    {
        data[i][0] = a[i];
    }        
}