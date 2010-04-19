#include "../Matrix.h"
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class TestMatrix : public CppUnit::TestCase {
    CPPUNIT_TEST_SUITE(TestMatrix);
    CPPUNIT_TEST(simpleConstructorTest);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();
        
    protected:
        void simpleConstructorTest();
        
    private:
        Matrix *A;
};