#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "iosolver.h"
#include "utilities.h"

void skipInput(int symbol)
{
    if (symbol != '\n') {
        while (getchar() != '\n') {
            continue;
        }
    }
}

StatusDouble compareDouble(double number1, double number2)
{
    if ( fabs(number1 - number2) < eps ) {
        return EQUALS;
    }

    if (   (number1 - number2)   > eps ) {
        return GREATER;
    }

    return LESS;
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
