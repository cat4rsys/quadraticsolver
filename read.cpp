#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/read.h"
#include "include/iosolver.h"

int readExit()
{
    if (getchar() == '\n') {
        return RETURN_IN_MAIN_MENU;
    }
    else {
        skipInput();
        return UNKNOWN_SYMBOL;
    }
}

int readNum(char symbol, char prevSymbol, int ifE, int * numInE, int signE, int inFractional, double * num, int * ifNum)
{
    if (prevSymbol == 'x' || prevSymbol == 'X') {
        skipInput();
        return NUM_AFTER_X;
    }
    if (ifE)
        *numInE = *numInE * 10 + signE * (symbol - '0');
    else {
        if (inFractional)
            *numInE -= 1;
        *num = *num * 10 + symbol - '0';
        *ifNum = 1;
    }
    return 0;
}

int readDot(int * inFractional, int * signE, int inE)
{
    if (*inFractional) {
        skipInput();
        return TWO_OR_MORE_FRACTIONAL;
    }
    if (inE){
        skipInput();
        return FLOAT_EXPONENTIAL;
    }
    *inFractional = 1;
    *signE = -1;
    return 0;
}

int readVar(int * ifMult, int * power, int ifNum, double * num)
{
    if (!(ifNum) && (fabs(*num)) < eps)
        *num = 1.0;
    if (*ifMult == 1 || *ifMult == 0) {
        *power += 1;
        *ifMult = 1;
    }
    else
        *power -= 1;
    return 0;
}

int readE(int * ifE, int * tempNumInE, int * numInE, int * signE, int * inFractional)
{
    if (*ifE) {
        skipInput();
        return TWO_OR_MORE_EXPONENTIAL;
    }
    *ifE = 1;
    *inFractional = 0;
    *tempNumInE += *numInE;
    *numInE = 0;
    *signE = +1;
    return 0;
}
