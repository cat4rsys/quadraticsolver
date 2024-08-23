#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <cassert>
#include "read.h"
#include "iosolver.h"
#include "solve.h"

void mainMenu()
{
    printf("Quadratic equation solver\n");
    printf("Program has two modes of work:\n");
    printf("Simple mode - mode with minimum output and opportunity to enter equations endlessly.\n");
    printf("Detail mode - mode, that instructing you, but you can enter only one equation.\n");
    printf("Test mode - mode allowing to test how program solving equations. For developers.\n");
    printf("(For first use recommended to use Detail mode)\n");
    printf("Choose mode:\n");
    printf("a - Simple mode\n");
    printf("b - Detail mode\n");
    printf("t - Test mode\n");
    printf("Or enter \"q\" for quit\n");
}

ModesOfWork pickAction()
{
    int action = getchar();
    int temp = 0;

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
    case EXIT:
        break;
    default:
        printf("UNKNOWN ERROR\n");
        return;
    }
}

void simpleMode()
{
    printf("Enter your equations. To exit to the menu enter \"q\".\n");

    SolverErrors errorCode = NORMAL;

    while ( errorCode != RETURN_IN_MAIN_MENU ) {
        EquationData coefficients = {0, 0, 0};

        errorCode = inputOfEquation(&coefficients);

        Roots roots = {};

        coefficients.type = getType(coefficients);
        solveEquation(coefficients, &roots);

        printRoots(roots, errorCode, normalAccuracy);
    }
}

void detailMode()
{
    SolverErrors errorCode = NORMAL;
    EquationData coefficients = {0, 0, 0};

    printf("Enter your equation. To exit to the menu enter \"q\".\n");
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
}

void testMode()
{
    int i = 0;

    for(; i == numberOfTests - 1; i++) {
        if ( checkTest(test_array[i]) == WRONG ) {
            return;
        }
    }

    printf("All tests are correct. Enter anything for exit to the menu\n");
    skipInput('0');
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
        printf("%sReturning in main menu%s\n", RED, STANDART);
        break;
    default:
        printf("%sUNKNOWN ERROR%s\n", RED, STANDART);
        break;
    }
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
        default:
            printf("UNKNOWN ERROR\n");
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

    printf("Enter anything for exit to the menu\n");
    skipInput('0');

    return WRONG;
}
