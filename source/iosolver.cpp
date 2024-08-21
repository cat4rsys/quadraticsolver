#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "read.h"
#include "iosolver.h"
#include "solve.h"

void mainMenu()
{
    printf("Quadratic equation solver\n");
    printf("Program has two modes of work:\n");
    printf("Simple mode - mode with minimum output and opportunity to enter equations endlessly.\n");
    printf("Detail mode - mode, that instructing you, but you can enter only one equation\n");
    printf("(For first use recommended to use Detail mode)\n");
    printf("Choose mode:\n");
    printf("a - Simple mode\n");
    printf("b - Detail mode\n");
    printf("t - Test mode\n");
    printf("Or enter \"q\" for quit\n");
}

ModesOfWork pickAction()
{
    char action = getchar();
    char temp = 0;

    while ( (temp = getchar()) != '\n' || (action != 'b' && action != 'a' && action != 'q' && action != 't') ) {
        printf("Wrong input. Try again:\n");
        skipInput(temp);
        action = getchar();
    }

    return readMode(action);
}

void doAction(ModesOfWork mode)
{
    switch(mode) {
    case TEST:
        testMode();
        break;
    case SIMPLE:
        simpleMode();
        break;
    case DETAIL:
        detailMode();
        break;
    }
}

void simpleMode()
{
    printf("Enter your equations. To exit to the menu enter \"q\".\n");

    SolverErrors errorCode = NORMAL;
    Coeffs coefficients = {};

    while ( errorCode != RETURN_IN_MAIN_MENU ) {
        coefficients = {0, 0, 0};

        errorCode = inputOfEquation(&coefficients);
        printRoots(coefficients, errorCode, normalAccuracy);
    }
}

void detailMode()
{
    SolverErrors errorCode = NORMAL;
    Coeffs coefficients = {};

    printf("Enter your equation. To exit to the menu enter \"q\".\n");
    printf("Program can't solve equations with brackets.\n");
    printf("Program ignores blanks.\n");
    printf("For writing square of x you can use \"xx\"\n");

    if ( inputOfEquation(&coefficients) == RETURN_IN_MAIN_MENU )
        return;

    int accuracy = getAccuracy();

    printRoots(coefficients, errorCode, accuracy);

    printf("Enter anything for exit to the menu\n");
    skipInput('0');
}

void testMode()
{
    int i = 0;

    for(; i == numberOfTests - 1; i++) {
        if ( test(test_array[i]) == WRONG ) {
            return;
        }
    }

    printf("All tests are correct. Enter anything for exit to the menu\n");
    skipInput('0');
}

SolverErrors inputOfEquation(Coeffs * coefficient)
{
    PartsOfEquation part = LEFT_PART;
    SolverErrors errorCode = NORMAL;
    char prevSymbol = 0;
    char symbol = getchar();
    int sign = +1;

    while ( symbol != '\n' ) {
        if ( symbol == 'q' && prevSymbol == 0 ) {
            return readExit();
        }

        else if ( symbol == ' ' );

        else if ( symbol == '+' || symbol == '-' ) {
            if ( prevSymbol == '+' || prevSymbol == '-' || prevSymbol == '*' || prevSymbol == '/' ) {
                skipInput(symbol);
                return TOO_MANY_OPERATIONS;
            }

            sign = readSign(symbol, part);
        }

        else if ( symbol == '=' ) {
            sign = -1;

            if (part == LEFT_PART) {
                part = RIGHT_PART;
            }
            else {
                skipInput(symbol);
                return TWO_OR_MORE_EQUALS;
            }
        }

        else if ( symbol == '\n' ) {
            return NORMAL;
        }

        else if ( isBeginnigMonomial(symbol) ) {
            double num = 0;
            int power = 0;

            if ( (errorCode = readMonomial(&symbol, &prevSymbol, &power, &num)) == NORMAL ) {
                errorCode = writeMonomial(sign, num, power, &*coefficient);
                continue;
            }
            else {
                skipInput(symbol);
                return errorCode;
            }
        }

        else {
            skipInput(symbol);
            return UNKNOWN_SYMBOL;
        }

        if ( errorCode != NORMAL ) {
            skipInput(symbol);
            return errorCode;
        }

        readNext(&symbol, &prevSymbol);
    }

    if ( part == LEFT_PART ) {
        return NO_EQUAL;
    }
    else {
        return NORMAL;
    }
}

SolverErrors writeMonomial(int sign, double num, int power, Coeffs * coefficient)
{
    switch (power) {
    case 2:
        coefficient->a += sign * num;
        break;
    case 1:
        coefficient->b += sign * num;
        break;
    case 0:
        coefficient->c += sign * num;
        break;
    default:
        return INCORRECT_POWER;
    }
    return NORMAL;
}

void printInputError(SolverErrors errorCode)
{
    switch (errorCode) {
    case UNKNOWN_SYMBOL:
        printf("ERROR: Unknown symbol in input\n");
        break;
    case TWO_OR_MORE_EQUALS:
        printf("ERROR: Two or more \'=\' symbols\n");
        break;
    case INCORRECT_POWER:
        printf("ERROR: Power of your equation is more then two or contains monomials with negative power\n");
        break;
    case TWO_OR_MORE_FRACTIONAL:
        printf("ERROR: Two or more \'.\' symbols in one number\n");
        break;
    case FLOAT_EXPONENTIAL:
        printf("ERROR: Exponential part can be only integer\n");
        break;
    case TWO_OR_MORE_EXPONENTIAL:
        printf("ERROR: In one number can be only one exponential part\n");
        break;
    case NUM_AFTER_X:
        printf("ERROR: After \"x\" expected *, /, +, -\n");
        break;
    case TOO_MANY_OPERATIONS:
        printf("ERROR: You can't write symbol of operation after symbol of operation.\n");
        break;
    case NO_EQUAL:
        printf("ERROR: Your equation has not \'=\' symbol.\n");
        break;
    }
}

TypeOfEquation getType(Coeffs coefficient)
{
    if ( compareDouble(coefficient.a, 0) == EQUALS ) {
        if ( compareDouble(coefficient.b, 0) == EQUALS )
            return WITHOUT_VARIABLE;
        else
            return LINEAR;
    }
    else {
        if ( compareDouble(coefficient.c, 0) == EQUALS )
            return SQUARE_WITHOUT_C;
        else
            return SQUARE;
    }
}

// TODO asserts
// TODO naming
void printRoots(Coeffs coefficient, SolverErrors errorCode, int accuracy)
{
    if (errorCode == NORMAL) {
        Roots root = {};

        coefficient.type = getType(coefficient);
        solveEquation(coefficient, &root);

        switch(root.numberOfRoots) {
        case INF_ROOTS:
            printf("The equation has infinite number of roots.\n");
            break;
        case ZERO_ROOTS:
            printf("The equation has NO roots!\n");
            break;
        case ONE_ROOT:
            printf("x = %.*e.\n", accuracy, root.x1);
            break;
        case TWO_ROOTS:
            printf("x1 = %.*e, x2 = %.*e\n", accuracy, root.x1, accuracy, root.x2);
            break;
        }
    }
    else {
        printInputError(errorCode);
    }
}

int isBeginnigMonomial(char symbol)
{
    if (isdigit(symbol) || symbol == 'x') {
        return 1;
    }
    else {
        return 0;
    }
}

int isEndingMonomial(char symbol, char prevSymbol)
{
    if ( (symbol == '+' || symbol == '-' || symbol == '\n' || symbol == '=') &&
        (prevSymbol != 'x' || prevSymbol != 'X' || prevSymbol != 'e' || prevSymbol != 'E') ) {
        return 1;
    }
    else {
        return 0;
    }
}

int getAccuracy()
{
    int accuracy = 0;
    char v = 0;

    printf("Enter accuracy of output: ");

    while ( (v = getchar()) != '\n' ) {
        if ( !(isdigit(v)) || (accuracy == 0 && v == '0') ) {
            skipInput(v);
            accuracy = 0;
            printf("Wrong input. Try again: ");
        }
        else {
            accuracy = accuracy * 10 + v - '0';
        }
    }

    return accuracy;
}

void skipInput(char symbol)
{
    if (symbol != '\n') {
        while (getchar() != '\n') {
            continue;
        }
    }
}

void goodBye()
{
    printf("Thank you for using my program. Good bye!");
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

ResultOfTest test(Test test)
{
    Roots calculatedRoots = {};
    Roots realRoots = {test.x1, test.x2, test.numberOfRoots};
    Coeffs coefficients = {test.a, test.b, test.c};

    coefficients.type = getType(coefficients);
    solveEquation(coefficients, &calculatedRoots);

    if ( calculatedRoots.x1 == realRoots.x1 && calculatedRoots.x2 == realRoots.x2 &&
        calculatedRoots.numberOfRoots == realRoots.numberOfRoots ) {
        return CORRECT;
    }

    printf("ERROR at test №%d (a = %lg, b = %lg, c = %lg):\n", test.numberOfThisTest, coefficients.a, coefficients.b, coefficients.c);
    printf("Expected: x1 = %lg, x2 = %lg, number of roots = %d\n", realRoots.x1, realRoots.x2, realRoots.numberOfRoots);
    printf("Calculated: x1 = %lg, x2 = %lg, number of roots = %d\n",
           calculatedRoots.x1, calculatedRoots.x2, calculatedRoots.numberOfRoots);

    printf("Enter anything for exit to the menu\n");
    skipInput('0');

    return WRONG;
}
