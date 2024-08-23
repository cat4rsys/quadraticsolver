#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <cstring>
#include "read.h"
#include "iosolver.h"
#include "solve.h"
#include "testsys.h"
#include "utilities.h"

void helpMenu()
{
    printf("%sQuadratic equation solver%s\n\n", CYAN, STANDART);
    printf("Program has three modes of work:\n\n");
    printf("DESCRIPTION:\n");
    printf("Simple mode - mode with minimum output and opportunity to enter equations endlessly.\n");
    printf("Detail mode - mode, that instructing you, but you can enter only one equation.\n");
    printf("Test mode - mode allowing to test how program solving equations. For developers.\n");
    printf("(For first use recommended to use Detail mode)\n");
    printf("\nThese are common Quadratic Solver commands:\n");
    printf("    --help - description of program and commands.\n\n");
    printf("    simple - turning on simple mode.\n");
    printf("    detail - turning on detail mode.\n");
    printf("    test   - turning on test mode.\n\n");
}

void pickMode(char * arg)
{
    if ( !strcmp(arg, "--help") ) {
        helpMenu();
    }
    else if ( !strcmp(arg, "simple") ) {
        simpleMode();
    }
    else if ( !strcmp(arg, "detail") ) {
        detailMode();
    }
    else if ( !strcmp(arg, "test") ) {
        testMode();
    }
    else {
        printBootError();
    }
}

void simpleMode()
{
    printf("Enter your equations. To exit enter \"q\".\n");

    SolverErrors errorCode = NORMAL;

    while ( errorCode != RETURN_IN_MAIN_MENU ) {
        EquationData coefficients = {0, 0, 0};

        errorCode = inputOfEquation(&coefficients);

        Roots roots = {};

        coefficients.type = getType(coefficients);
        solveEquation(coefficients, &roots);

        printRoots(roots, errorCode, normalAccuracy);
    }

    goodBye();
}

void detailMode()
{
    SolverErrors errorCode = NORMAL;
    EquationData coefficients = {0, 0, 0};

    printf("Enter your equation. To exit enter \"q\".\n");
    printf("Program can't solve equations with brackets.\n");
    printf("Program ignores blanks.\n");
    printf("For writing square of x you can use \"xx\"\n");

    if ( inputOfEquation(&coefficients) == RETURN_IN_MAIN_MENU )
        return;

    int accuracy = getAccuracy();

    Roots roots = {};

    coefficients.type = getType(coefficients);
    solveEquation(coefficients, &roots);

    printRoots(roots, errorCode, accuracy);

    printf("Enter anything for exit to the menu\n");
    skipInput('0');

    goodBye();
}

void testMode()
{
    int i = 0;

    for(; i < numberOfTests; i++) {
        if ( checkTest(test_array[i]) == WRONG ) {
            return;
        }
    }

    printf("All tests are correct\n");
}

SolverErrors inputOfEquation(EquationData * coefficient)
{
    customAssert(coefficient != NULL, __FILE__, __LINE__);

    PartsOfEquation part = LEFT_PART;
    SolverErrors errorCode = NORMAL;
    int prevSymbol = 0;
    int symbol = getchar();
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
                errorCode = writeMonomial(sign, num, power, coefficient);
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

int isBeginnigMonomial(int symbol)
{
    if (isdigit(symbol) || symbol == 'x') {
        return 1;
    }
    else {
        return 0;
    }
}

int isEndingMonomial(int symbol, int prevSymbol)
{
    if ( (symbol == '+' || symbol == '-' || symbol == '\n' || symbol == '=') &&
        (tolower(prevSymbol) != 'x' || tolower(prevSymbol) != 'e') ) {
        return 1;
    }
    else {
        return 0;
    }
}


SolverErrors writeMonomial(int sign, double num, int power, EquationData * coefficient)
{
    customAssert(coefficient != NULL, __FILE__, __LINE__);

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
        printf("%sERROR: Unknown symbol in input%s\n", RED, STANDART);
        break;
    case TWO_OR_MORE_EQUALS:
        printf("%sERROR: Two or more \'=\' symbols%s\n", RED, STANDART);
        break;
    case INCORRECT_POWER:
        printf("%sERROR: Power of your equation is more then two or contains monomials with negative power%s\n", RED, STANDART);
        break;
    case TWO_OR_MORE_FRACTIONAL:
        printf("%sERROR: Two or more \'.\' symbols in one number%s\n", RED, STANDART);
        break;
    case FLOAT_EXPONENTIAL:
        printf("%sERROR: Exponential part can be only integer%s\n", RED, STANDART);
        break;
    case TWO_OR_MORE_EXPONENTIAL:
        printf("%sERROR: In one number can be only one exponential part\n%s", RED, STANDART);
        break;
    case NUM_AFTER_X:
        printf("%sERROR: After \"x\" expected *, /, +, -\n%s", RED, STANDART);
        break;
    case TOO_MANY_OPERATIONS:
        printf("%sERROR: You can't write symbol of operation after symbol of operation.%s\n", RED, STANDART);
        break;
    case NO_EQUAL:
        printf("%sERROR: Your equation has not \'=\' symbol.%s\n", RED, STANDART);
        break;
    case NORMAL:
        printf("%sEquation inputed correct%s\n", RED, STANDART);
        break;
    case RETURN_IN_MAIN_MENU:
        printf("%sExiting%s\n", RED, STANDART);
        break;
    default:
        printf("%sUNKNOWN ERROR%s\n", RED, STANDART);
        break;
    }
}

void printBootError()
{
    printf("%sERROR OF BOOT\n", RED);
    printf("Try \"--help\" for help%s\n", STANDART);
}

void printRoots(Roots root, SolverErrors errorCode, int accuracy)
{
    if (errorCode == NORMAL) {
        switch(root.numberOfRoots) {
        case INF_ROOTS:
            printf("%sANSWER: The equation has infinite number of roots.%s\n", PURPLE, STANDART);
            break;
        case ZERO_ROOTS:
            printf("%sANSWER: The equation has NO roots!%s\n", RED, STANDART);
            break;
        case ONE_ROOT:
            printf("%sANSWER: x = %.*e.%s\n", YELLOW, accuracy, root.x1, STANDART);
            break;
        case TWO_ROOTS:
            printf("%sANSWER: x1 = %.*e, x2 = %.*e%s\n", GREEN, accuracy, root.x1, accuracy, root.x2, STANDART);
            break;
        default:
            printf("%sUNKNOWN ERROR%s\n", RED, STANDART);
            break;
        }
    }
    else {
        printInputError(errorCode);
    }
}

int getAccuracy()
{
    int accuracy = 0;
    int v = 0;

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

void goodBye()
{
    printf("Thank you for using my program. Good bye!");
}
