#include <stdio.h>
#include <math.h>
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

void customAssert(bool expression, const char * file, int line)
{
    if ( expression ) {
        return;
    }
    else {
        printf("%sAssertion failed: file %s, line %d%s\n", RED, file, line, STANDART);
        return;
    }
}

StatusDouble compareDouble(double number1, double number2)
{
    if ( fabs(number1 - number2) < eps ) {
        return EQUALS;
    }

    if ( (number1 - number2) > eps ) {
        return GREATER;
    }

    return LESS;
}
