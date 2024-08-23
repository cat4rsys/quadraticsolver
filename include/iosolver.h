#ifndef H_IOSOLVER
#define H_IOSOLVER
#include <solve.h>

const double eps            = 1e-25;
const int    normalAccuracy = 3;
const int    numberOfTests  = 8;

// COLORS

const char RED[] = "\033[3;31m";
const char CYAN[] = "\033[1;36m";
const char GREEN[] = "\033[3;32m";
const char PURPLE[] = "\033[3;35m";
const char YELLOW[] = "\033[3;33m";
const char STANDART[] = "\033[0m";

enum PartsOfEquation
{
    LEFT_PART,
    RIGHT_PART
};

enum SolverErrors
{
    NORMAL,
    RETURN_IN_MAIN_MENU,
    UNKNOWN_SYMBOL,
    TWO_OR_MORE_EQUALS,
    INCORRECT_POWER,
    TWO_OR_MORE_FRACTIONAL,
    FLOAT_EXPONENTIAL,
    TWO_OR_MORE_EXPONENTIAL,
    NUM_AFTER_X,
    TOO_MANY_OPERATIONS,
    NO_EQUAL
};

void helpMenu();

void pickMode(char * arg);

void simpleMode();

void detailMode();

void testMode();

///--------------------------------------------input-----------------------------------------------
/// \n Reads all equation, entered by user and records it as coefficient of ax^2 + bx + c = 0
///
/// @return coefficient[]   - array for coefficients c, b and a
///------------------------------------------------------------------------------------------------

SolverErrors inputOfEquation(EquationData * coefficient);

SolverErrors writeMonomial(int sign, double num, int power, EquationData * coefficient);

///-----------------------------------------------error--------------------------------------------
/// \n Prints error, coded by errorCode
///
/// @param [in] errorCode - code of error
///------------------------------------------------------------------------------------------------

int isBeginnigMonomial(int symbol);

int isEndingMonomial(int symbol, int prevSymbol);

void printInputError(SolverErrors errorCode);

void printBootError();

void printRoots(Roots root, SolverErrors errorCode, int accuracy);

int getAccuracy();

void goodBye();

#endif // H_IOSOLVER
