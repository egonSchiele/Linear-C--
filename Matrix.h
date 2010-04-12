#include <iostream>
#include <vector>
/* using namespace std; */
class Matrix {
    public:
        std::vector<std::vector<int> > data;
        int rows;
        int cols;        
        Matrix(int r, int c);
        
        // create the matrix from a vector
        Matrix(std::vector<std::vector<int> >& a);
        
        // populate the matrix with random numbers in the range 0-9
        std::vector<std::vector<int> >& populateRandom();
};

// how to multiply two Matrix objects
Matrix& operator*(const Matrix &a, const Matrix &b);

// how to print out a matrix
std::ostream& operator<<(std::ostream& s, const Matrix m);