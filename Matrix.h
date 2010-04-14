#include <iostream>
#include <vector>
/* using namespace std; */
class Matrix {
    public:
        Matrix(int r, int c);
        int rows();
        int cols();
        // create the matrix from a vector
        Matrix(std::vector<std::vector<int> >& a);
        
        // populate the matrix with random numbers in the range 0-9
        Matrix& populateRandom();
        
        // make this matrix an identity matrix
        Matrix& populateIdentity();
        
        // transpose of the Matrix
        Matrix& transpose();
            
        // access the data in the matrix directly
        int& operator()(int i, int j);
        
        // add a row
        virtual void appendRow(std::vector<int> &r);
        virtual void appendRow(int *r, int size);

        // add a col
        virtual void appendCol(std::vector<int> &r);
        virtual void appendCol(int *r, int size);

    protected:
        std::vector<std::vector<int> > data;
};


// how to multiply two Matrix objects
Matrix& operator*(Matrix &a,  Matrix &b);

// how to multiply a Matrix object by a scalar
Matrix& operator*(double s, Matrix &a);

// how to add two Matrix objects
Matrix& operator+(Matrix &a, Matrix &b);

// how to subtract two Matrix objects
Matrix& operator-(Matrix &a, Matrix &b);


// how to print out a matrix
std::ostream& operator<<(std::ostream& s,  Matrix &m);

// test if two Matrix objects are equivalent
bool operator==(Matrix &a, Matrix &b);

/*
    Here are two classes that inherit from class Matrix.
    There are some things you can do with vectors that you can't do
    with matrices, such as get their length. If you need to do vector-specific
    operations, make sure you use a RowVector or ColumnVector.
    
    RowVector: Creates a matrix of 1 row of the specified length.   
    ColumnVector: Creates a matrix of 1 column of the specified length.
*/
   
class RowVector : public Matrix {
    public:
        RowVector(int c) : Matrix(1,c) {}
        RowVector(std::vector<int> &a);
        RowVector(int *a, int size);
        double length() ;
        void appendRow();
        void appendCol();         
};

class ColumnVector : public Matrix {
    public:
        ColumnVector(int r) : Matrix(r,1) {}
        ColumnVector(std::vector<int> &a);
        ColumnVector(int *a, int size);
        double length() ;
        void appendRow();
        void appendCol();
};
