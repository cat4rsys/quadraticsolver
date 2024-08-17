/*------------------------------------------------------------------------------------------------------
                                                 iosolver.h
                          funcs and consts, that controls input and output in solver
                                                   consts
eps            - few number. needed for comparison double
normalAccuracy - standart accuracy. uses in simple mode
                                                    funcs
mainmenu       - func, that outputs main menu and remembering choice of user
simpleMode     - func, that turns on simple mode
detailMode     - func, that turns on detail mode
input          - func, that reads equation and record numbers in coefficient[], where coefficient[i] = a in
               this form of writing: a*(x^i)
record         - func, that records number in coefficient or returns as errorCode -4 if power of equation
               is more than two
error          - func, that outputs description of error, that coded by errorCode
output         - func, that checking type of equation(quadratic, linear or zero-powered) and outputs the roots
               of equation or error if it happened.
getAccuracy    - func, that getting accuracy of output
skipInput      - func, that skips all input
goodBye        - final func. just says good bye for user
------------------------------------------------------------------------------------------------------*/

const double eps = 1e-37;
const int normalAccuracy = 3;

enum SolverErrors
{
    RETURN_IN_MAIN_MENU = 1,
    UNKNOWN_SYMBOL,
    TWO_OR_MORE_EQUALS,
    POWER_MORE_THAN_TWO,
    TWO_OR_MORE_FRACTIONAL,
    FLOAT_EXPONENTIAL,
    TWO_OR_MORE_EXPONENTIAL,
    NUM_AFTER_X
};

void mainMenu(char * choice);

void simpleMode(void);

void detailMode(void);

void input(double coefficient[], int * errorCode);

int record(int sign, double num, int ifMult, double multiplicatedNum, int tempNumInE, int numInE, int power, double coefficient[]);

void error(int errorCode);

void output(double a, double b, double c, int err, int accuracy);

int getAccuracy(void);

void skipInput(void);

void goodBye(void);

