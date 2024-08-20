#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "..\include\read.h"
#include "..\include\iosolver.h"

SolverErrors readExit()
{
    if (getchar() == '\n') {
        return RETURN_IN_MAIN_MENU;
    }
    else {
        skipInput();
        return UNKNOWN_SYMBOL;
    }
}

SolverErrors readNum(char * symbol, char * prevSymbol, double * num)
{
    if (*prevSymbol == 'x' || *prevSymbol == 'X') {
        skipInput();
        return NUM_AFTER_X;
    }
    int ifDot = 0;
    int numsAfterDot = 0;
    while (*symbol == ' ' || isdigit(*symbol) || *symbol == '.' || *symbol == ',') {
        if (isdigit(*symbol)) {
            *num = *num * 10 + *symbol - '0';
            if (ifDot == 1)
                numsAfterDot++;
        }
        if (*symbol == '.' || *symbol == ',')
            if (ifDot == 0)
                ifDot = 1;
            else
                return TWO_OR_MORE_FRACTIONAL;
        *prevSymbol = *symbol;
        *symbol = getchar();
    }
    for (; numsAfterDot > 0; numsAfterDot--)
        *num /= 10.0;
    return NORMAL;
}

SolverErrors readVar(int ifMult, int * power, int ifNum, double * num)
{
    if (!(ifNum) && (fabs(*num)) < eps)
        *num = 1.0;
    if (ifMult == 1 || ifMult == 0) {
        *power += 1;
    }
    else
        *power -= 1;
    return NORMAL;
}

SolverErrors readE(char * symbol, char * prevSymbol, double * num)
{
    int signE = +1;
    int numInE = 0;
    int blockExit = 1;
    *prevSymbol = *symbol;
    *symbol = getchar();
    while (isdigit(*symbol) || ((*symbol == '+' || *symbol == '-') && tolower(*prevSymbol) == 'e')) {
        if (*symbol == '+')
            signE = +1;
        if (*symbol == '-')
            signE = -1;
        if (isdigit(*symbol))
            numInE = numInE * 10 + *symbol - '0';
        *prevSymbol = *symbol;
        *symbol = getchar();
    }
    if (tolower(*symbol) == 'e')
        return TWO_OR_MORE_EXPONENTIAL;
    if (signE == +1) {
        for (; numInE != 0; numInE--)
            *num *= 10.0;
    }
    else {
        for (; numInE != 0; numInE--)
            *num /= 10.0;
    }
    return NORMAL;
}

SolverErrors readMultiplication(char * symbol, char * prevSymbol, double * multiplicatedNum, double * num, int * ifMult)
{
    if (*prevSymbol == '+' || *prevSymbol == '-' || *prevSymbol == '*' || *prevSymbol == '/')
        return TOO_MANY_OPERATIONS;
    (*symbol == '*') ? *multiplicatedNum *= *num : *multiplicatedNum /= *num;
    if (*ifMult == 0)
        *multiplicatedNum = *num;
    (*symbol == '*') ? *ifMult = 1: *ifMult = -1;
    *num = 0;
    *prevSymbol = *symbol;
    *symbol = getchar();
    return NORMAL;
}

int readSign(char symbol, int part)
{
    if (symbol == '+' && part == LEFT_PART)
        return +1;
    if (symbol == '-' && part == RIGHT_PART)
        return +1;
    if (symbol == '+' && part == RIGHT_PART)
        return -1;
    if (symbol == '-' && part == LEFT_PART)
        return -1;
    return 0;
}

SolverErrors readMonomial(char * symbol, char * prevSymbol, int * power, double * number)
{
    SolverErrors errorCode = NORMAL;
    int ifNum = 0;
    int ifMult = 0;
    double num = 0;
    double multiplicatedNum = 0;
    while (!isEndingMonomial(*symbol, *prevSymbol)) {
        if (*symbol == 'x' || *symbol == 'X') {
            if ((errorCode = readVar(ifMult, &*power, ifNum, &num)) != NORMAL)
                return errorCode;
            *prevSymbol = *symbol;
            *symbol = getchar();
        }
        else if (*symbol == '*' || *symbol == '/') {
            if ((errorCode = readMultiplication(&*symbol, &*prevSymbol, &multiplicatedNum, &num, &ifMult)) != NORMAL)
                return errorCode;
            ifNum = 0;
        }
        else if (*symbol == 'e' || *symbol =='E') {
            if ((errorCode = readE(&*symbol, &*prevSymbol, &num)) != NORMAL)
                return errorCode;
        }
        else if (isdigit(*symbol)) {
            if ((errorCode = readNum(&*symbol, &*prevSymbol, &num)) != NORMAL)
                return errorCode;
            ifNum = 1;
        }
        else
            return UNKNOWN_SYMBOL;
    }
    switch(ifMult) {
    case 0:
        *number = num;
        break;
    case 1:
        *number = multiplicatedNum * num;
        break;
    case 2:
        *number = multiplicatedNum / num;
        break;
    }
    return NORMAL;
}

SolverErrors input(double coefficient[])
{
    int part = LEFT_PART;
    SolverErrors errorCode = NORMAL;
    char prevSymbol = 0;
    char symbol = getchar();
    int sign = +1;
    while (symbol != '\n') {
        if (symbol == ' ');
        else if (symbol == '+' || symbol == '-') {
            if (prevSymbol == '+' || prevSymbol == '-' || prevSymbol == '*' || prevSymbol == '/') {
                skipInput();
                return TOO_MANY_OPERATIONS;
            }
            sign = readSign(symbol, part);
        }
        else if (symbol == '=') {
            sign = -1;
            if (part == LEFT_PART)
                part = RIGHT_PART;
            else {
                skipInput();
                return TWO_OR_MORE_EQUALS;
            }
        }
        else if (symbol == '\n') {
            return NORMAL;
        }
        else if (isBeginnigMonomial(symbol)) {
            double num = 0;
            int power = 0;
            if ((errorCode = readMonomial(&symbol, &prevSymbol, &power, &num)) == NORMAL) {
                record(sign, num, power, coefficient);
                continue;
            }
            else {
                skipInput();
                return errorCode;
            }
        }
        else {
            skipInput();
            return UNKNOWN_SYMBOL;
        }
        if (errorCode != NORMAL) {
            skipInput();
            return errorCode;
        }
        prevSymbol = symbol;
        symbol = getchar();
    }
    return NORMAL;
}

SolverErrors record(int sign, double num, int power, double coefficient[])
{
    if (power > 2) {
        skipInput();
        return POWER_MORE_THAN_TWO;
    }
    coefficient[power] += sign * num;
    return NORMAL;
}

void error(SolverErrors errorCode)
{
    if (errorCode == UNKNOWN_SYMBOL)
        printf("ERROR: Unknown symbol in input\n");
    if (errorCode == TWO_OR_MORE_EQUALS)
        printf("ERROR: Two or more \'=\' symbols\n");
    if (errorCode == POWER_MORE_THAN_TWO)
        printf("ERROR: Power of your equation is more then two\n");
    if (errorCode == TWO_OR_MORE_FRACTIONAL)
        printf("ERROR: Two or more \'.\' symbols in one number\n");
    if (errorCode == FLOAT_EXPONENTIAL)
        printf("ERROR: Exponential part can be only integer\n");
    if (errorCode == TWO_OR_MORE_EXPONENTIAL)
        printf("ERROR: In one number can be only one exponential part\n");
    if (errorCode == NUM_AFTER_X)
        printf("ERROR: After \"x\" expected *, /, +, -\n");
    if (errorCode == TOO_MANY_OPERATIONS)
        printf("ERROR: You can't write symbol of operation after symbol of operation.\n");
}

void output(double a, double b, double c, SolverErrors errorCode, int accuracy)
{
    double d = 0;
    if (errorCode == NORMAL){
        d = b * b - 4 * a * c;
        if (fabs(a) > eps) {
            if (fabs(d) < eps)
                printf("x1 = x2 = %.*e\n", accuracy, - b / (2.0 * a) );
            else if (d >= 0) {
                d = sqrt(d);
                double firstRoot = (-b + d) / (2 * a);
                double secondRoot = (-b - d) / (2 * a);
                printf("x1 = %.*e, x2 = %.*e\n", accuracy, firstRoot, accuracy, secondRoot);
            }
            else {
                d = sqrt(-d);
                double realRoot = -b / (2.0 * a);
                double imaginaryRoot = d / (2.0 * a);
                printf("x1 = %.*e + %.*e * i, x2 = %.*e + %.*e * i.\n", accuracy, realRoot, imaginaryRoot, realRoot, accuracy, realRoot, accuracy, imaginaryRoot);
            }
        }
        else if (fabs(b) > eps) {
            double root = - c / b;
            printf("Equation is linear. x = %.*e.\n", accuracy, root);
        }
        else if (fabs(c) > eps)
            printf("The equation has NO roots!\n");
        else
            printf("The equation has infinite number of roots.\n");
    }
    else{
        error(errorCode);
    }
}
