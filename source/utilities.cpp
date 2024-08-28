#include <stdio.h>
#include <math.h>
#include <windows.h>
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
    const double eps = 1e-25;                    /**< error of double */

    if ( fabs(number1 - number2) < eps ) return EQUALS;
    if (     (number1 - number2) > eps ) return GREATER;

    return LESS;
}

void setColor(WORD color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
