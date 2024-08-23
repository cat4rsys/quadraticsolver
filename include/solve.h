#ifndef H_SOLVE
#define H_SOLVE
#include <stdio.h>

enum NumberOfRoots
{
    ZERO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INF_ROOTS
};

enum TypeOfEquation
{
    SQUARE,
    SQUARE_WITHOUT_C,
    LINEAR,
    WITHOUT_VARIABLE
};

struct EquationData
{
    double a;
    double b;
    double c;
    TypeOfEquation type;
};

typedef struct
{
    double x1;
    double x2;
    NumberOfRoots numberOfRoots;
} Roots;

void solveEquation(EquationData coefficient, Roots * root);

TypeOfEquation getType(EquationData coefficient);

#endif // H_SOLVE
