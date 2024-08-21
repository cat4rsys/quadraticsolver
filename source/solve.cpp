#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "read.h"
#include "iosolver.h"
#include "solve.h"

void solveSquare(Coeffs coefficient, Roots * root)
{
    double discriminant = (coefficient.b) * (coefficient.b) - 4 * (coefficient.a) * (coefficient.c);
    if (doubleIsZero(discriminant)) {
        root->x1 = -(coefficient.b) / (2 * (coefficient.a));
        root->numberOfRoots = 1;
    }
    else if (discriminant < 0) // Brackets
        root->numberOfRoots = 0;
    else {
        double sqrtDiscriminant = sqrt(discriminant);
        // TODO blank line
        root->x1 = (-(coefficient.b) - sqrtDiscriminant) / (2 * (coefficient.a));
        root->x2 = (-(coefficient.b) + sqrtDiscriminant) / (2 * (coefficient.a));
        root->numberOfRoots = 2;
    }
}

void solveSquareWithoutC(Coeffs coefficient, Roots * root) // Make coeffs const ptr
{
    double anotherRoot = - (coefficient.b) / (coefficient.a);
    if (doubleIsZero(anotherRoot)) {
        root->x1 = 0;
        root->numberOfRoots = 1;
    }
    else if (anotherRoot > 0) { // TODO use EPS
        root->x1 = 0;
        root->x2 = anotherRoot;
        root->numberOfRoots = 2;
    }
    else if (anotherRoot < 0) {
        root->x2 = 0;
        root->x1 = anotherRoot;
        root->numberOfRoots = 2;
    }
}

void solveLinear(Coeffs coefficient, Roots * root) // TODO const
{
    root->x1 = - (coefficient.c) / (coefficient.b);
    root->numberOfRoots = 1;
}

void solveWithoutVariable(Coeffs coefficient, Roots * root) // TODO const
{
    if (doubleIsZero(coefficient.c))
        root->numberOfRoots = infRoots;
    else
        root->numberOfRoots = 0;
}

void solveEquation(Coeffs coefficient, Roots * root)
{
    switch(coefficient.type) {
    case SQUARE:
        solveSquare(coefficient, root);
        break;
    case SQUARE_WITHOUT_C:
        solveSquareWithoutC(coefficient, root);
        break;
    case LINEAR:
        solveLinear(coefficient, root);
        break;
    case WITHOUT_VARIABLE:
        solveWithoutVariable(coefficient, root);
        break;
    }
}
