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

///--------------------------------------------readExit-------------------------------------------
///
SolverErrors readExit(void);

SolverErrors readNum(char * symbol, char * prevSymbol, double * num);

SolverErrors readE(char * symbol, char * prevSymbol, double * num);

SolverErrors readVar(int * ifMult, int * power, int ifNum, double * num);

SolverErrors readMultiplication(char * symbol, char * prevSymbol, double * multiplicatedNum, double * num, int * ifMult);

///-------------------------------------------readSign---------------------------------------------
//! Reads + or - between monomials
//!
//! @param symbol - symbol, that was enterred between two monomials
//! @param part   - left or right part of equation?
//!
//! @return sign of next monomial
///------------------------------------------------------------------------------------------------

int readSign(char symbol, int part);

///------------------------------------------readMonomial------------------------------------------
//! Reads one monomial
//! @param symbol     - enterred by user symbol
//! @param prevSymbol - previously enterred by user symbol
//! @param power      - power of monomial
//! @param number     - coefficient of monomial
//!
//! @return power and coefficient of entered monomial
///------------------------------------------------------------------------------------------------
SolverErrors readMonomial(char * symbol, char * prevSymbol, int * power, double * number);

SolverErrors input(double coefficient[]);

SolverErrors record(int sign, double num, int power, double coefficient[]);

void error(SolverErrors errorCode);

void output(double a, double b, double c, SolverErrors errorCode, int accuracy);
