#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cassert>
#include "Matrix.h"
using namespace std;

Matrix::Matrix(int r, int c) : rows(r), cols(c)
{
    data.resize(rows);
    for (int i=0;i<rows;i++)
    {
        data[i].resize(cols);                
    }
    
}

// create the matrix from a vector
Matrix::Matrix(vector<vector<int> >& a)
{
    rows = a.size();
    cols = a[0].size();
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
vector<vector<int> >& Matrix::populateRandom()
{
    srand ( time(NULL) ); // seed the matrix
    for (int i=0;i<rows;i++)
    {
        for (int j=0;j<cols;j++)
        {
            data[i][j] = rand() % 10;
        }                
    }            
    return data;
}

// how to multiply two Matrix objects
Matrix& operator*(const Matrix &a, const Matrix &b)
{
    assert(a.cols > 0);
    assert (a.cols == b.rows);
    vector<vector<int> > c;
    c.resize(a.rows);
    
    for (int i=0;i<a.rows;i++)
    {
        c[i].resize(b.cols);
        for (int j=0;j<b.cols;j++)
        {
            c[i][j] = 0;
            for (int k=0;k<a.cols;k++)
            {
                 c[i][j] += a.data[i][k]*b.data[k][j];
            }
        }
    }

    Matrix *res = new Matrix(c);
    return *res;
}

// how to print out a matrix
ostream& operator<<(ostream& s, const Matrix m)
{
    s << "[ " << endl;
    for (int i=0;i<m.rows;i++)
    {
        s << "[";
        for (int j=0;j<m.cols;j++)
        {
            s << " " << m.data[i][j] << " ";
        }
        s << "]" << endl;
    }
    s << "]" << endl;

}
