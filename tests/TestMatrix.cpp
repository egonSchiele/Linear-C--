#include "TestMatrix.h"
#include <iostream>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
using namespace std;

void TestMatrix::setUp()
{
    A = new Matrix(3,3);
}

void TestMatrix::tearDown()
{
    delete A;
}

void TestMatrix::simpleConstructorTest()
{
    CPPUNIT_ASSERT_MESSAGE("The # of rows in the matrix is not correct.",A->rows()==3);
    CPPUNIT_ASSERT_MESSAGE("The # of columns in the matrix is not correct.",A->cols()==3);
}
