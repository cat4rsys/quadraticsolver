#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "read.h"
#include "iosolver.h"
#include "utilities.h"

SolverErrors readExit()
{
    if ( getchar() == '\n' ) {
        return RETURN_IN_MAIN_MENU;
    }
    else {
        skipInput('0');

        return UNKNOWN_SYMBOL;
    }
}

SolverErrors readNum(int * symbol, int * prevSymbol, double * num)
{
    CUSTOM_ASSERT(symbol     != NULL);
    CUSTOM_ASSERT(prevSymbol != NULL);
    CUSTOM_ASSERT(num        != NULL);

    if ( *prevSymbol == 'x' || *prevSymbol == 'X' ) {
        return NUM_AFTER_X;
    }

    int ifDot        = 0;
    int numsAfterDot = 0;

    while ( *symbol == ' ' || isdigit(*symbol) || *symbol == '.' || *symbol == ',' ) {
        if ( isdigit(*symbol) ) {
            *num = *num * 10 + *symbol - '0';
            if ( ifDot == 1 ) {
                numsAfterDot++;
            }
        }

        if ( *symbol == '.' || *symbol == ',' ) {
            if (ifDot == 1) {
                return TWO_OR_MORE_FRACTIONAL;
            }
            ifDot = 1;
        }

        readNext(symbol, prevSymbol);
    }

    for ( ; numsAfterDot > 0; numsAfterDot-- ) {
        *num /= 10.0;
    }

    return NORMAL;
}

SolverErrors readVar(int ifMult, int * power, int ifNum, double * num)
{
    CUSTOM_ASSERT(power != NULL);
    CUSTOM_ASSERT(num   != NULL);

    if ( !(ifNum) ) {
        *num = 1.0;
    }

    if ( ifMult == 1 || ifMult == 0 ) {
        *power += 1;
    }
    else {
        *power -= 1;
    }

    return NORMAL;
}

SolverErrors readE(int * symbol, int * prevSymbol, double * num)
{
    CUSTOM_ASSERT(symbol     != NULL);
    CUSTOM_ASSERT(prevSymbol != NULL);
    CUSTOM_ASSERT(num        != NULL);

    int signE  = +1;
    int numInE = 0;

    readNext(symbol, prevSymbol);

    while ( isdigit(*symbol) || ((*symbol == '+' || *symbol == '-') && tolower(*prevSymbol) == 'e') ) {
        if ( *symbol == '+' ) {
            signE = +1;
        }
        if ( *symbol == '-' ) {
            signE = -1;
        }

        if ( isdigit(*symbol) ) {
            numInE = numInE * 10 + *symbol - '0';
        }

        readNext(symbol, prevSymbol);
    }

    if ( *symbol == '.' or *symbol == ',' ) {
        return FLOAT_EXPONENTIAL;
    }

    if ( tolower(*symbol) == 'e' ) {
        return TWO_OR_MORE_EXPONENTIAL;
    }

    if ( signE == +1 ) {
        for ( ; numInE != 0; numInE-- ) {
            *num *= 10.0;
        }
    }
    else {
        for ( ; numInE != 0; numInE-- ) {
            *num /= 10.0;
        }
    }

    return NORMAL;
}

SolverErrors readMultiplication(int * symbol, int * prevSymbol, double * multiplicatedNum, double * num, int * ifMult)
{
    CUSTOM_ASSERT(symbol           != NULL);
    CUSTOM_ASSERT(prevSymbol       != NULL);
    CUSTOM_ASSERT(multiplicatedNum != NULL);
    CUSTOM_ASSERT(num              != NULL);
    CUSTOM_ASSERT(ifMult           != NULL);

    if ( *prevSymbol == '+' || *prevSymbol == '-' || *prevSymbol == '*' || *prevSymbol == '/' ) {
        return TOO_MANY_OPERATIONS;
    }

    ( *symbol == '*' ) ? *multiplicatedNum *= *num : *multiplicatedNum /= *num;

    if ( *ifMult == 0 ) {
        *multiplicatedNum = *num;
    }

    ( *symbol == '*' ) ? *ifMult = 1 : *ifMult = -1;

    *num = 0;

    readNext(symbol, prevSymbol);

    return NORMAL;
}

int readSign(int symbol, PartsOfEquation part)
{
    if (      symbol == '+' && part == LEFT_PART  ) {
        return +1;
    }
    else if ( symbol == '-' && part == RIGHT_PART ) {
        return +1;
    }
    else if ( symbol == '+' && part == RIGHT_PART ) {
        return -1;
    }
    else if ( symbol == '-' && part == LEFT_PART ) {
        return -1;
    }

    return 0;
}

SolverErrors readMonomial(int * symbol, int * prevSymbol, int * power, double * number)
{
    CUSTOM_ASSERT(symbol     != NULL);
    CUSTOM_ASSERT(prevSymbol != NULL);
    CUSTOM_ASSERT(power      != NULL);
    CUSTOM_ASSERT(number     != NULL);

    SolverErrors errorCode = NORMAL;

    int ifNum  = 0;
    int ifMult = 0;

    double num              = 0;
    double multiplicatedNum = 0;

    while ( !isEndingMonomial(*symbol, *prevSymbol) ) {
        if ( *symbol == 'x' || *symbol == 'X' ) {
            if ( (errorCode = readVar(ifMult, power, ifNum, &num)) != NORMAL ) {
                return errorCode;
            }

            readNext(symbol, prevSymbol);
        }

        else if ( *symbol == '*' || *symbol == '/' ) {
            if ( (errorCode = readMultiplication(symbol, prevSymbol, &multiplicatedNum, &num, &ifMult)) != NORMAL ) {
                return errorCode;
            }

            ifNum = 0;
        }

        else if ( *symbol == 'e' || *symbol =='E' ) {
            if ( (errorCode = readE(symbol, prevSymbol, &num)) != NORMAL ) {
                return errorCode;
            }
        }

        else if ( isdigit(*symbol )) {
            if ( (errorCode = readNum(symbol, prevSymbol, &num)) != NORMAL ) {
                return errorCode;
            }

            ifNum = 1;
        }

        else if ( *symbol == ' ' ) {
            readNext(symbol, prevSymbol);
        }

        else {
            return UNKNOWN_SYMBOL;
        }
    }

    switch(ifMult) {
    case 0:
        *number = num;
        break;
    case 1:
        *number = multiplicatedNum * num;
        break;
    case -1:
        *number = multiplicatedNum / num;
        break;
    default:
        printf("UNKNOWN ERROR\n");
        break;
    }

    return NORMAL;
}

void readNext(int * symbol, int * prevSymbol)
{
    CUSTOM_ASSERT(symbol     != NULL);
    CUSTOM_ASSERT(prevSymbol != NULL);

    if ( *symbol != ' ' ) {
        *prevSymbol = *symbol;
    }
    *symbol = getchar();
}
