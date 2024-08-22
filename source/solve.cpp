#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>
#include "read.h"
#include "iosolver.h"
#include "solve.h"

void solveSquare(EquationData coefficients, Roots * root)
{
    assert(root != NULL);

    double discriminant = (coefficients.b) * (coefficients.b) - 4 * (coefficients.a) * (coefficients.c);

    if ( compareDouble(discriminant, 0) == EQUALS ) {
        root->x1 = - (coefficients.b) / (2 * (coefficients.a));
        root->numberOfRoots = ONE_ROOT;
    }

    else if ( compareDouble(discriminant, 0) == LESS ) {
        root->numberOfRoots = ZERO_ROOTS;
    }

    else if ( compareDouble(discriminant, 0) == GREATER ) {
        double sqrtDiscriminant = sqrt(discriminant);

        root->x1 = ( - (coefficients.b) - sqrtDiscriminant) / (2 * (coefficients.a));
        root->x2 = ( - (coefficients.b) + sqrtDiscriminant) / (2 * (coefficients.a));
        root->numberOfRoots = TWO_ROOTS;
    }
}

void solveSquareWithoutC(EquationData coefficients, Roots * root)
{
    assert(root != NULL);

    double anotherRoot = - (coefficients.b) / (coefficients.a);

    if ( compareDouble(anotherRoot, 0) == EQUALS ) {
        root->x1 = 0;
        root->numberOfRoots = ONE_ROOT;
    }

    else if ( compareDouble(anotherRoot, 0) == LESS ) {
        root->x1 = 0;
        root->x2 = anotherRoot;
        root->numberOfRoots = TWO_ROOTS;
    }

    else if ( compareDouble(anotherRoot, 0) == GREATER ) {
        root->x2 = 0;
        root->x1 = anotherRoot;
        root->numberOfRoots = TWO_ROOTS;
    }
}

void solveLinear(EquationData coefficients, Roots * root)
{
    assert(root != NULL);

    root->x1 = - (coefficients.c) / (coefficients.b);
    root->numberOfRoots = ONE_ROOT;
}

void solveWithoutVariable(EquationData coefficients, Roots * root)
{
    assert(root != NULL);

    if ( compareDouble(coefficients.c, 0) == EQUALS ) {
        root->numberOfRoots = INF_ROOTS;
    }
    else {
        root->numberOfRoots = ZERO_ROOTS;
    }
}

void solveEquation(EquationData coefficients, Roots * root)
{
    assert(root != NULL);

    switch(coefficients.type) {
    case SQUARE:
        solveSquare(coefficients, root);
        break;
    case SQUARE_WITHOUT_C:
        solveSquareWithoutC(coefficients, root);
        break;
    case LINEAR:
        solveLinear(coefficients, root);
        break;
    case WITHOUT_VARIABLE:
        solveWithoutVariable(coefficients, root);
        break;
    default:
        printf("UNKNOWN ERROR\n");
        break;
    }
}
