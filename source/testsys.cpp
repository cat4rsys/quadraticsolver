#include <stdio.h>
#include "solve.h"
#include "utilities.h"
#include "testsys.h"

ResultOfTest checkTest(TestData test)
{
    Roots calculatedRoots = {};
    Roots realRoots = {test.x1, test.x2, test.numberOfRoots};
    EquationData coefficients = {test.a, test.b, test.c};

    coefficients.type = getType(coefficients);
    solveEquation(coefficients, &calculatedRoots);

    if ( compareDouble(calculatedRoots.x1, realRoots.x1) == EQUALS &&
         compareDouble(calculatedRoots.x2, realRoots.x2) == EQUALS &&
         calculatedRoots.numberOfRoots == realRoots.numberOfRoots ) {
        printf("Test %d CORRECT\n", test.numberOfThisTest);
        return CORRECT;
    }

    printf("ERROR at test №%d (a = %lg, b = %lg, c = %lg):\n", test.numberOfThisTest, coefficients.a, coefficients.b, coefficients.c);
    printf("Expected:   x1 = %lg, x2 = %lg, number of roots = %d\n", realRoots.x1, realRoots.x2, realRoots.numberOfRoots);
    printf("Calculated: x1 = %lg, x2 = %lg, number of roots = %d\n",
           calculatedRoots.x1, calculatedRoots.x2, calculatedRoots.numberOfRoots);

    return WRONG;
}

