#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "read.h"
#include "iosolver.h"
#include "solve.h"
#include "utilities.h"

/**
 * \brief Solves square equation
 *
 * \param[in]  coeffitient - struct with coefficients and type of equation
 * \param[out] root        - struct with roots and number of roots
 */
static void solveSquare(EquationData coefficient, Roots * root);

/**
 * \brief Solves square equation without c-coeffitient
 *
 * \param[in]  coeffitient - struct with coefficients and type of equation
 * \param[out] root        - struct with roots and number of roots
 */
static void solveSquareWithoutC(EquationData coefficient, Roots * root);

/**
 * \brief Solves linear equation
 *
 * \param[in]  coeffitient - struct with coefficients and type of equation
 * \param[out] root        - struct with roots and number of roots
 */
static void solveLinear(EquationData coefficient, Roots * root);

/**
 * \brief Solves equation without variables
 *
 * \param[in]  coeffitient - struct with coefficients and type of equation
 * \param[out] root        - struct with roots and number of roots
 */
static void solveWithoutVariable(EquationData coefficient, Roots * root);

static void solveSquare(EquationData coefficients, Roots * root)
{
    customAssert(root != NULL);

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

static void solveSquareWithoutC(EquationData coefficients, Roots * root)
{
    customAssert(root != NULL);

    double anotherRoot = - (coefficients.b) / (coefficients.a);

    if ( compareDouble(anotherRoot, 0) == EQUALS ) {
        root->x1 = 0;
        root->numberOfRoots = ONE_ROOT;
    }

    else if ( compareDouble(anotherRoot, 0) == LESS ) {
        root->x2 = 0;
        root->x1 = anotherRoot;
        root->numberOfRoots = TWO_ROOTS;
    }

    else if ( compareDouble(anotherRoot, 0) == GREATER ) {
        root->x1 = 0;
        root->x2 = anotherRoot;
        root->numberOfRoots = TWO_ROOTS;
    }
}

static void solveLinear(EquationData coefficients, Roots * root)
{
    customAssert(root != NULL);

    root->x1 = - (coefficients.c) / (coefficients.b);
    root->numberOfRoots = ONE_ROOT;
}

static void solveWithoutVariable(EquationData coefficients, Roots * root)
{
    customAssert(root != NULL);

    if ( compareDouble(coefficients.c, 0) == EQUALS ) {
        root->numberOfRoots = INF_ROOTS;
    }
    else {
        root->numberOfRoots = ZERO_ROOTS;
    }
}

void solveEquation(EquationData coefficients, Roots * root)
{
    customAssert(root != NULL);

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

TypeOfEquation getType(EquationData coefficient)
{
    if ( compareDouble(coefficient.a, 0) == EQUALS ) {
        if ( compareDouble(coefficient.b, 0) == EQUALS )
            return WITHOUT_VARIABLE;
        else
            return LINEAR;
    }
    else {
        if ( compareDouble(coefficient.c, 0) == EQUALS )
            return SQUARE_WITHOUT_C;
        else
            return SQUARE;
    }
}

