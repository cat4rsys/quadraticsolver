#ifndef H_IOSOLVER
#define H_IOSOLVER

const double eps            = 1e-25;
const int    normalAccuracy = 3;

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
    POWER_MORE_THAN_TWO,
    TWO_OR_MORE_FRACTIONAL,
    FLOAT_EXPONENTIAL,
    TWO_OR_MORE_EXPONENTIAL,
    NUM_AFTER_X,
    TOO_MANY_OPERATIONS
};

#endif

void mainMenu(char * choice);

void simpleMode(void);

void detailMode(void);

///--------------------------------------------input-----------------------------------------------
/// \n Reads all equation, entered by user and records it as coefficient of ax^2 + bx + c = 0
///
/// @return coefficient[]   - array for coefficients c, b and a
///------------------------------------------------------------------------------------------------

SolverErrors input(double coefficient[]);

SolverErrors record(int sign, double num, int power, double coefficient[]);

///-----------------------------------------------error--------------------------------------------
/// \n Prints error, coded by errorCode
///
/// @param [in] errorCode - code of error
///------------------------------------------------------------------------------------------------

void error(SolverErrors errorCode);

void output(double a, double b, double c, SolverErrors errorCode, int accuracy);

int isBeginnigMonomial(char symbol);

int isEndingMonomial(char symbol, char prevSymbol);

int getAccuracy(void);

void skipInput(void);

void goodBye(void);

