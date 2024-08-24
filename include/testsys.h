#ifndef H_TESTSYS
#define H_TESTSYS

/**
 * \brief Possible cases of test
 */
enum ResultOfTest
{
    CORRECT,                                     /**< Test passed correctly */
    WRONG                                        /**< Test passed wrongly */
};

/**
 * \brief Struct, that contains information about test
 */
typedef struct
{
    int numberOfThisTest;                        /**< Number of test */
    double a;                                    /**< a-coefficient */
    double b;                                    /**< b-coefficient */
    double c;                                    /**< c-coefficient */
    double x1;                                   /**< Expected less root */
    double x2;                                   /**< Expected greater root */
    NumberOfRoots numberOfRoots;                 /**< Expected number of roots */
} TestData;

const TestData test_array[] = {
    {1, 1,  4,     4,   -2,   0,   ONE_ROOT},
    {2, 1,  0, -1.44, -1.2, 1.2,  TWO_ROOTS},
    {3, 0,  3,     6,   -2,   0,   ONE_ROOT},
    {4, 3,  6,     0,   -2,   0,  TWO_ROOTS},
    {5, 3, -6,     0,    0,   2,  TWO_ROOTS},
    {6, 0,  0,     1,    0,   0, ZERO_ROOTS},
    {7, 0,  0,     0,    0,   0,  INF_ROOTS},
    {8, 1,  3,    -4,   -4,   1,  TWO_ROOTS}
};

/**
 * \brief  Check test by information about test
 *
 * \param  test - information about test
 *
 * \return Result of test. If test passed wrongly gives information about test and calculated roots
 */
ResultOfTest checkTest(TestData test);

#endif // H_TESTSYS
