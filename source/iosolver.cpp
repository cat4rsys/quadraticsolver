#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <cassert>
#include <cstring>
#include "read.h"
#include "iosolver.h"
#include "solve.h"

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

    for(; i < 8; i++) {
        if ( checkTest(test_array[i]) == WRONG ) {
            return;
        }
    }

    printf("All tests are correct\n");
}

SolverErrors inputOfEquation(EquationData * coefficient)
{
    assert(coefficient != NULL);

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

SolverErrors writeMonomial(int sign, double num, int power, EquationData * coefficient)
{
    assert(coefficient != NULL);

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

TypeOfEquation getType(EquationData coefficient)
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

void skipInput(int symbol)
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

ResultOfTest checkTest(TestData test)
{
    Roots calculatedRoots = {};
    Roots realRoots = {test.x1, test.x2, test.numberOfRoots};
    EquationData coefficients = {test.a, test.b, test.c};

    coefficients.type = getType(coefficients);
    solveEquation(coefficients, &calculatedRoots);

    if ( compareDouble(calculatedRoots.x1, realRoots.x1) == EQUALS &&
         compareDouble(calculatedRoots.x2, realRoots.x2) == EQUALS &&
         calculatedRoots.numberOfRoots == realRoots.numberOfRoots ) {
        return CORRECT;
    }

    printf("ERROR at test №%d (a = %lg, b = %lg, c = %lg):\n", test.numberOfThisTest, coefficients.a, coefficients.b, coefficients.c);
    printf("Expected: x1 = %lg, x2 = %lg, number of roots = %d\n", realRoots.x1, realRoots.x2, realRoots.numberOfRoots);
    printf("Calculated: x1 = %lg, x2 = %lg, number of roots = %d\n",
           calculatedRoots.x1, calculatedRoots.x2, calculatedRoots.numberOfRoots);

    return WRONG;
}

void customAssert(bool expression, const char * file, int line)
{
    if ( expression ) {
        return;
    }
    else {
        printf("%sAssertion failed: file %s, line %d%s\n", RED, file, line, STANDART);
        return;
    }
}
