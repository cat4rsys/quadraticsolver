#ifndef H_TESTSYS
#define H_TESTSYS

enum ResultOfTest
{
    CORRECT,
    WRONG
};

typedef struct
{
    int numberOfThisTest;
    double a;
    double b;
    double c;
    double x1;
    double x2;
    NumberOfRoots numberOfRoots;
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

ResultOfTest checkTest(TestData test);

#endif // H_TESTSYS
