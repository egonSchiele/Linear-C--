#include "UnitTest++/UnitTest++.h"
#include "UnitTest++/ReportAssert.h"
#include "../Matrix.h"
#include "../MatrixFunctions.h"
#include <vector>
#include <cmath>
using namespace std;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    These are tests for the following classes and all their methods:

        Matrix
        RowVector
        ColumnVector

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

struct TestMatrix
{
    TestMatrix()
    {
        m = new Matrix(3,3);
        sq = new Matrix(2,2);
        i.resize(2);
        i[0].resize(2);
        i[1].resize(2);
        i[0][0] = 1;
        i[0][1] = 0;
        i[1][0] = 0;
        i[1][1] = 1;

        a.resize(2);
        a[0].resize(2);
        a[1].resize(2);
        a[0][0] = 1;
        a[0][1] = 2;
        a[1][0] = 3;
        a[1][1] = 4;

        at.resize(2);
        at[0].resize(2);
        at[1].resize(2);
        at[0][0] = 1;
        at[0][1] = 3;
        at[1][0] = 2;
        at[1][1] = 4;

        twoa.resize(2);
        twoa[0].resize(2);
        twoa[1].resize(2);
        twoa[0][0] = 2;
        twoa[0][1] = 4;
        twoa[1][0] = 6;
        twoa[1][1] = 8;
        
        r = new RowVector(2);
        c = new ColumnVector(2);
    }
    ~TestMatrix()
    {
        delete m;
        delete sq;
        delete r;
        delete c;
    }
        Matrix *m; // 3x3 matrix
        Matrix *sq; // 2x2 matrix
        vector<vector<double> > i; // 2d vector of identity matrix
        vector<vector<double> > a; // simple 2x2 non-singular matrix
        vector<vector<double> > twoa; // a * 2
        vector<vector<double> > at; // transpose of a
    
        RowVector *r;
        ColumnVector *c;
};

TEST_FIXTURE(TestMatrix, TestSimpleConstructor)
{
    // Check that the vector behind the simple constructor has been resized properly.
    CHECK(m->rows()==3);
    CHECK(m->cols()==3);
}

TEST_FIXTURE(TestMatrix, TestVectorConstructor )
{
    // Tests to make sure a Matrix object can
    // be constructed using a 2d vector.
    delete m;
    m = new Matrix(i);
    CHECK(m->rows()==2);
    CHECK(m->cols()==2);
}

TEST_FIXTURE(TestMatrix,TestArrayConstructor)
{
    m->populateIdentity();
    double a[] = {1,0,0,0,1,0,0,0,1};
    Matrix *I = new Matrix(a,3,3);
    CHECK((*m)==(*I));
    
    // testing on non-square matrices.
    double var[] = {1, -2, -3, -4, 0, 0, 0, 3, 2, 1, 1, 0, 0, 2, 5, 3, 0, 1};
    Matrix m2(var,3,6);    
    CHECK(m2(1,1) == 3);
    delete I;
}

TEST_FIXTURE(TestMatrix,TestRows)
{
    CHECK(m->rows()==3);
}

TEST_FIXTURE(TestMatrix,TestCols)
{
    CHECK(m->cols()==3);
}

// what happens if we make a matrix object
// that's empty? We should get 0 rows and 0 cols.
TEST_FIXTURE(TestMatrix,TestZeroRows)
{
    delete m;
    m = new Matrix(0,0);
    CHECK(m->rows()==0);
}

TEST_FIXTURE(TestMatrix,TestZeroCols)
{
    delete m;
    m = new Matrix(0,0);
    CHECK(m->cols()==0);
}

TEST_FIXTURE(TestMatrix,TestPopulateIdentity)
{
    // test that populateIdentity actually makes an identity matrix
    m->populateIdentity();
    CHECK((*m)(0,0) == 1);
    CHECK((*m)(0,1) == 0);
    CHECK((*m)(0,2) == 0);
    CHECK((*m)(1,0) == 0);
    CHECK((*m)(1,1) == 1);
    CHECK((*m)(1,2) == 0);
    CHECK((*m)(2,0) == 0);
    CHECK((*m)(2,1) == 0);
    CHECK((*m)(2,2) == 1);
}

TEST_FIXTURE(TestMatrix,TestPopulateSymmetric)
{
    m->populateSymmetric();
    CHECK(isSymmetric(*m));
}

TEST_FIXTURE(TestMatrix,TestTranspose)
{
    m->populateIdentity();
    CHECK((*m)==m->transpose());
        
    m = new Matrix(a);
    Matrix *n = new Matrix(at);
    CHECK(m->transpose()==(*n));
    delete n;    
}

TEST_FIXTURE(TestMatrix,TestInverse)
{
    delete m;
    m = new Matrix(a);
    Matrix n = m->inverse();
    Matrix I(2,2);
    I.populateIdentity();
    CHECK((*m)*n==I);
}

TEST_FIXTURE(TestMatrix,TestDeterminant)
{
    delete m;
    // 3x3 matrix with determinant = 14
    double ar[] = {3, 1, 8, 2, -5, 4, -1, 6, -2};
    m = new Matrix(ar,3,3);
    CHECK(fabs(m->det() - 14) < .01);
}

TEST_FIXTURE(TestMatrix,TestTrace)
{
    m->populateIdentity();
    CHECK(m->trace() == 3);
}


TEST_FIXTURE(TestMatrix,TestElementAccess)
{
    // Test that we can access each element of the Matrix using
    // m(0,0), m(0,1) etc syntax.
    
    (*sq)(0,0) = 1;
    (*sq)(0,1) = 0;
    (*sq)(1,0) = 0;
    (*sq)(1,1) = 1;
    
    Matrix I(2,2);
    I.populateIdentity();
    CHECK((*sq)==I);
}

TEST_FIXTURE(TestMatrix,TestAppendRow)
{
    delete m;
    m = new Matrix(1,2);
    Matrix *n = new Matrix(1,2);
    (*m)(0,0) = 1;
    (*m)(0,1) = 0;
    (*n)(0,0) = 0;
    (*n)(0,1) = 1;
    m->appendRow(*n);
    
    Matrix *I = new Matrix(2,2);
    I->populateIdentity();
    
    CHECK((*m)==(*I));
}

TEST_FIXTURE(TestMatrix,TestAppendCol)
{
    delete m;
    m = new Matrix(2,1);
    Matrix *n = new Matrix(2,1);
    (*m)(0,0) = 1;
    (*m)(1,0) = 0;
    (*n)(0,0) = 0;
    (*n)(1,0) = 1;
    m->appendCol(*n);
    
    Matrix *I = new Matrix(2,2);
    I->populateIdentity();
    
    CHECK((*m)==(*I));
}

TEST_FIXTURE(TestMatrix,TestAppendRowVec)
{
    delete m;
    m = new Matrix(1,2);
    (*m)(0,0) = 1;
    (*m)(0,1) = 0;

    vector<double> v;
    v.resize(2);
    v[0] = 0;
    v[1] = 1;
    
    m->appendRow(v);
    
    Matrix *I = new Matrix(2,2);
    I->populateIdentity();
    
    CHECK((*m)==(*I));
}

TEST_FIXTURE(TestMatrix,TestAppendColVec)
{
    delete m;
    m = new Matrix(2,1);
    (*m)(0,0) = 1;
    (*m)(1,0) = 0;

    vector<double> v;
    v.resize(2);
    v[0] = 0;
    v[1] = 1;
    
    m->appendCol(v);
    
    Matrix *I = new Matrix(2,2);
    I->populateIdentity();
    
    CHECK((*m)==(*I));
}

TEST_FIXTURE(TestMatrix,TestAppendRowArray)
{
    delete m;
    m = new Matrix(1,2);
    (*m)(0,0) = 1;
    (*m)(0,1) = 0;

    double a[] = {0,1};
        
    m->appendRow(a,2);
    
    Matrix *I = new Matrix(2,2);
    I->populateIdentity();
    
    CHECK((*m)==(*I));
}

TEST_FIXTURE(TestMatrix,TestAppendColArray)
{
    delete m;
    m = new Matrix(2,1);
    (*m)(0,0) = 1;
    (*m)(1,0) = 0;

    double a[] = {0,1};
        
    m->appendCol(a,2);
    
    Matrix *I = new Matrix(2,2);
    I->populateIdentity();
    
    CHECK((*m)==(*I));
}

TEST_FIXTURE(TestMatrix,swapRows)
{
    sq->populateIdentity();    
    sq->swapRows(0,1);
    CHECK((*sq)(0,0)==0);
}

TEST_FIXTURE(TestMatrix,swapCols)
{
    sq->populateIdentity();    
    sq->swapCols(0,1);
    CHECK((*sq)(0,0)==0);
}

TEST_FIXTURE(TestMatrix,TestBeginIterator)
{
    delete m;
    m = new Matrix(a);
    double d = *(m->begin());
    CHECK(d==(*m)(0,0));
}

TEST_FIXTURE(TestMatrix,TestEndIterator)
{
    delete m;
    m = new Matrix(a);
    MatrixIterator it = m->end();
    CHECK(*(--it)==(*m)(1,1));
}

TEST_FIXTURE(TestMatrix,TestNullMatrix)
{
    // Check the static variable NullMatrix
    delete m;
    m = new Matrix(0,0);
    CHECK((*m)==NullMatrix);
}

TEST_FIXTURE(TestMatrix,CheckOperatorScalarMultiplyLeft)
{
    delete m;
    m = new Matrix(a);
    Matrix *n = new Matrix(twoa);
    *m = 2 * (*m);
    CHECK((*m)==(*n));    
}

TEST_FIXTURE(TestMatrix,CheckOperatorScalarMultiplyRight)
{
    delete m;
    m = new Matrix(a);
    Matrix *n = new Matrix(twoa);
    *m = (*m) * 2;
    CHECK((*m)==(*n));    
}

TEST_FIXTURE(TestMatrix,CheckOperatorAdd)
{
    sq->populateIdentity();
    double ar1[] = {1,0,0,0};
    double ar2[] = {0,0,0,1};
    Matrix *a = new Matrix(ar1,2,2);
    Matrix *b = new Matrix(ar2,2,2);
    Matrix *c = new Matrix(2,2);
    *c = (*a) + (*b);
    
    CHECK((*sq)==(*c));    
}

TEST_FIXTURE(TestMatrix,CheckOperatorSubtract)
{
    sq->populateIdentity();
    double ar1[] = {2,0,0,1};
    double ar2[] = {1,0,0,0};
    Matrix *a = new Matrix(ar1,2,2);
    Matrix *b = new Matrix(ar2,2,2);
    Matrix *c = new Matrix(2,2);
    *c = (*a) - (*b);
    
    CHECK((*sq)==(*c));    
}

TEST_FIXTURE(TestMatrix,CheckOperatorEquals)
{
    // Make sure operator == gives the correct answer.
    Matrix *p = new Matrix(2,2);
    Matrix *n = new Matrix(2,2);
    p->populateIdentity();
    n->populateIdentity();
    CHECK((*p)==(*n));
    delete n;
    delete p;
}

/* * * * * * * * * * * * * * * * * * * * 
     RowVector Tests Follow:
 * * * * * * * * * * * * * * * * * * * */

TEST_FIXTURE(TestMatrix,RVCheckSimpleConstructor)
{
    CHECK(r->cols()==2);
}

TEST_FIXTURE(TestMatrix,RVCheckVectorConstructor)
{
    delete r;
    vector<double> v;
    v.resize(2);
    v[0] = 1;
    v[1] = 0;
    r = new RowVector(v);
    CHECK((*r)(0,0)==1);
    CHECK((*r)(0,1)==0);
}

TEST_FIXTURE(TestMatrix,RVCheckArrayConstructor)
{
    delete r;
    double v[] = {1,0};
    r = new RowVector(v,2);
    CHECK((*r)(0,0)==1);
    CHECK((*r)(0,1)==0);
}

TEST_FIXTURE(TestMatrix,RVCheckLength)
{
    delete r;
    double v[] = {1,0};
    r = new RowVector(v,2);
    CHECK(r->length()==1);
}

/* * * * * * * * * * * * * * * * * * * * 
     ColumnVector Tests Follow:
 * * * * * * * * * * * * * * * * * * * */

TEST_FIXTURE(TestMatrix,CVCheckSimpleConstructor)
{
    CHECK(c->rows()==2);
}

TEST_FIXTURE(TestMatrix,CVCheckVectorConstructor)
{
    delete c;
    vector<double> v;
    v.resize(2);
    v[0] = 1;
    v[1] = 0;
    c = new ColumnVector(v);
    CHECK((*c)(0,0)==1);
    CHECK((*c)(1,0)==0);
}

TEST_FIXTURE(TestMatrix,CVCheckArrayConstructor)
{
    delete c;
    double v[] = {1,0};
    c = new ColumnVector(v,2);
    CHECK((*c)(0,0)==1);
    CHECK((*c)(1,0)==0);
}

TEST_FIXTURE(TestMatrix,CVCheckLength)
{
    delete c;
    double v[] = {1,0};
    c = new ColumnVector(v,2);
    CHECK(c->length()==1);
}

/* * * * * * * * * * * * * * * * * * * * 
     MatrixIterator tests follow:
 * * * * * * * * * * * * * * * * * * * */

TEST_FIXTURE(TestMatrix,CheckItMatrixConstructor)
{
    delete m;
    m = new Matrix(a);
    MatrixIterator i(*m);
    CHECK(*i==(*m)(0,0));
}

TEST_FIXTURE(TestMatrix,CheckItMatrixConstructorExplicitElement)
{
    delete m;
    m = new Matrix(a);
    MatrixIterator i(*m,1,0);
    CHECK(*i==(*m)(1,0));
}

TEST_FIXTURE(TestMatrix,CheckItCopyConstructor)
{
    delete m;
    m = new Matrix(a);
    MatrixIterator i(*m,1,0);
    MatrixIterator j(i);
    i++;
    j++;
    CHECK(*i==*j);
}

int main(int argc, char * argv[])
{
    return UnitTest::RunAllTests();
}