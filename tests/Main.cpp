#include "UnitTest++/UnitTest++.h"
#include "UnitTest++/ReportAssert.h"
#include "../Matrix.h"
#include "../MatrixFunctions.h"
#include <vector>
using namespace std;

// These are sample tests that show the different features of the framework
struct TestMatrix
{
    TestMatrix()
    {
        m = new Matrix(3,3);

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

    }
    ~TestMatrix()
    {
        delete m;
    }
        Matrix *m;
        vector<vector<double> > i; // 2d vector of identity matrix
        vector<vector<double> > a; // simple non-singular matrix
        vector<vector<double> > at; // transpose of a

};

TEST_FIXTURE(TestMatrix, TestSimpleConstructor)
{
    // Check that the vector behind the simple constructor has been resized properly.
    CHECK(m->rows()==3);
    CHECK(m->cols()==3);
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

TEST_FIXTURE(TestMatrix, TestVectorConstructor )
{
    // Tests to make sure a Matrix object can
    // be constructed using a 2d vector.
    delete m;
    m = new Matrix(i);
    CHECK(m->rows()==2);
    CHECK(m->cols()==2);
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
    Matrix *n = &(m->inverse());
    Matrix *I = new Matrix(2,2);
    I->populateIdentity();
    
    CHECK((*m)*(*n)==(*I));
    
    delete n;
    delete I;    
}

TEST_FIXTURE(TestMatrix,TestElementAccess)
{
    // Test that we can access each element of the Matrix using
    // m(0,0), m(0,1) etc syntax.
    
    delete m;
    m = new Matrix(2,2);
    (*m)(0,0) = 1;
    (*m)(0,1) = 0;
    (*m)(1,0) = 0;
    (*m)(1,1) = 1;
    
    Matrix *I = new Matrix(2,2);
    I->populateIdentity();
    CHECK((*m)==(*I));
    
    delete I;
}

/*
TEST_FIXTURE(TestMatrix,TestAppendRow)
{
    delete m;
    m = new Matrix(1,2);
    m(0,0) = 1;
    m(0,1) = 0;
}
*/

// ADD TESTS FOR REST OF MATRIX CLASS
// AS WELL AS ROWVECTOR AND COLUMNVECTOR CLASS
// HERE.


// ADD TESTS FOR MATRIX FUNCTIONS HERE.

int main(int argc, char * argv[])
{
    return UnitTest::RunAllTests();
}