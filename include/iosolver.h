#ifndef H_IOSOLVER
#define H_IOSOLVER

const double eps            = 1e-25;
const int    normalAccuracy = 3;
const int    infRoots       = 100;
const int    numberOfTests  = 8;

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
} Coeffs;

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
} Test;

const Test test_array[] = {
    {1, 1, 4, 4, -2, 0, ONE_ROOT},
    {2, 1, 0, -1.44, -1.2, 1.2, TWO_ROOTS},
    {3, 0, 3, 6, -2, 0, ONE_ROOT},
    {4, 3, 6, 0, -2, 0, TWO_ROOTS},
    {5, 3, -6, 0, 0, 2, TWO_ROOTS},
    {6, 0, 0, 1, 0, 0, ZERO_ROOTS},
    {7, 0, 0, 0, 0, 0, INF_ROOTS},
    {8, 1, 3, -4, -4, 1, TWO_ROOTS}
};

void mainMenu(void);

ModesOfWork pickAction(void);

void doAction(ModesOfWork mode);

void simpleMode(void);

void detailMode(void);

void testMode(void);

///--------------------------------------------input-----------------------------------------------
/// \n Reads all equation, entered by user and records it as coefficient of ax^2 + bx + c = 0
///
/// @return coefficient[]   - array for coefficients c, b and a
///------------------------------------------------------------------------------------------------

SolverErrors inputOfEquation(Coeffs * coefficient);

SolverErrors writeMonomial(int sign, double num, int power, Coeffs * coefficient);

///-----------------------------------------------error--------------------------------------------
/// \n Prints error, coded by errorCode
///
/// @param [in] errorCode - code of error
///------------------------------------------------------------------------------------------------

void printInputError(SolverErrors errorCode);

void getType(Coeffs * coefficient);

void printRoots(Coeffs coefficient, SolverErrors errorCode, int accuracy);

int isBeginnigMonomial(char symbol);

int isEndingMonomial(char symbol, char prevSymbol);

int getAccuracy(void);

void skipInput(char symbol);

void goodBye(void);

StatusDouble compareDouble(double number1, double number2);

ResultOfTest test(Test test);

#endif // H_IOSOLVER
