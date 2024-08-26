#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <cstring>
#include <windows.h>
#include "read.h"
#include "iosolver.h"
#include "solve.h"
#include "testsys.h"
#include "utilities.h"

void helpMenu()
{
    setColor(CYAN);
    printf("Quadratic equation solver\n\n");
    setColor(STANDART);
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
    setColor(RED);
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
    case NORMAL:
        printf("Equation inputed correct\n");
        break;
    case RETURN_IN_MAIN_MENU:
        printf("Exiting\n");
        break;
    default:
        printf("UNKNOWN ERROR\n");
        break;
    }
    setColor(STANDART);
}

void printBootError()
{
    setColor(RED);
    printf("ERROR OF BOOT\n");
    printf("Try \"--help\" for help\n");
    setColor(STANDART)
}

void printRoots(Roots root, SolverErrors errorCode, int accuracy)
{
    if (errorCode == NORMAL) {
        switch(root.numberOfRoots) {
        case INF_ROOTS:
            setColor(PURPLE);
            printf("ANSWER: The equation has infinite number of roots.\n");
            break;
        case ZERO_ROOTS:
            setColor(RED);
            printf("ANSWER: The equation has NO roots!\n");
            break;
        case ONE_ROOT:
            setColor(YELLOW);
            printf("ANSWER: x = %.*e.\n", accuracy, root.x1);
            break;
        case TWO_ROOTS:
            setColor(GREEN);
            printf("ANSWER: x1 = %.*e, x2 = %.*e\n", accuracy, root.x1, accuracy, root.x2);
            break;
        default:
            setColor(RED);
            printf("UNKNOWN ERROR\n");
            break;
        }

        setColor(STANDART);
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
