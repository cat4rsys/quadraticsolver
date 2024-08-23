#ifndef H_IOSOLVER
#define H_IOSOLVER

const double eps            = 1e-25;
const int    normalAccuracy = 3;
const int    infRoots       = 100;
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

enum ResultOfTest
{
    CORRECT,
    WRONG
};

enum ModesOfWork
{
    SIMPLE,
    DETAIL,
    TEST,
    EXIT
};

enum NumberOfRoots
{
    ZERO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INF_ROOTS
};

enum StatusDouble
{
    GREATER,
    EQUALS,
    LESS
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

enum TypeOfEquation
{
    SQUARE,
    SQUARE_WITHOUT_C,
    LINEAR,
    WITHOUT_VARIABLE
};

typedef struct
{
    double a;
    double b;
    double c;
    TypeOfEquation type;
} EquationData;

typedef struct
{
    double x1;
    double x2;
    NumberOfRoots numberOfRoots;
} Roots;

typedef struct
{
    int numberOfThisTest;
    double a;
    double b;
    double c;
    double x1;
    double x2;
    NumberOfRoots numberOfRoots;
} TestData;

const TestData test_array[] = {
    {1, 1,  4,     4,   -2,   0,   ONE_ROOT},
    {2, 1,  0, -1.44, -1.2, 1.2,  TWO_ROOTS},
    {3, 0,  3,     6,   -2,   0,   ONE_ROOT},
    {4, 3,  6,     0,   -2,   0,  TWO_ROOTS},
    {5, 3, -6,     0,    0,   2,  TWO_ROOTS},
    {6, 0,  0,     1,    0,   0, ZERO_ROOTS},
    {7, 0,  0,     0,    0,   0,  INF_ROOTS},
    {8, 1,  3,    -4,   -4,   1,  TWO_ROOTS}
};

void helpMenu();

void pickMode(char * arg);

/*ModesOfWork pickAction();

void doAction(ModesOfWork mode);*/

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

void printInputError(SolverErrors errorCode);

void printBootError();

TypeOfEquation getType(EquationData coefficient);

void printRoots(Roots root, SolverErrors errorCode, int accuracy);

int isBeginnigMonomial(int symbol);

int isEndingMonomial(int symbol, int prevSymbol);

int getAccuracy();

void skipInput(int symbol);

void goodBye();

StatusDouble compareDouble(double number1, double number2);

ResultOfTest checkTest(TestData test);

void customAssert(bool expression, const char * file, int line);

#endif // H_IOSOLVER
