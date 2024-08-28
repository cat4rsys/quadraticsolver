#include <stdio.h>
#include <ctype.h>
#include <cstring>
#include "read.h"
#include "iosolver.h"
#include "testsys.h"
#include "utilities.h"

const char * helpFlag   = "--help";
const char * simpleFlag = "--simple";
const char * detailFlag = "--detail";
const char * testFlag   = "--test";

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
    printf("    %s   - description of program and commands.\n\n", helpFlag);
    printf("    %s - turning on simple mode.\n", simpleFlag);
    printf("    %s - turning on detail mode.\n", detailFlag);
    printf("    %s   - turning on test mode.\n", testFlag);
}

void execMode(const char * arg)
{
    if ( !strcmp(arg, helpFlag) ) {
        helpMenu();
    }
    else if ( !strcmp(arg, simpleFlag) ) {
        simpleMode();
    }
    else if ( !strcmp(arg, detailFlag) ) {
        detailMode();
    }
    else if ( !strcmp(arg, testFlag) ) {
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
    SolverErrors errorCode    = NORMAL;
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
#ifdef FILEON

    FILE * pointerFile = fopen("files\\testdata.txt", "r");
    if ( pointerFile == NULL ) {
        setColor(RED);
        printf("ERROR OF READING FILE");
        setColor(STANDART);
    }
    TestData test = {};
    for(; fscanf(pointerFile, "%d %lf %lf %lf %lf %lf %d",
                 &test.numberOfThisTest, &test.a, &test.b, &test.c, &test.x1, &test.x2, ((int*)&(test.numberOfRoots))) != EOF;) {
        if ( checkTest(test) == WRONG ) {
            return;
        }
    }

    fclose(pointerFile);

#else

    for(int i = 0; i < numberOfTests; i++) {
        if ( checkTest(test_array[i]) == WRONG ) {
            return;
        }
    }

#endif

    setColor(GREEN);
    printf("All tests are correct\n");
    setColor(STANDART);
}

SolverErrors inputOfEquation(EquationData * coefficient)
{
    CUSTOM_ASSERT(coefficient != NULL);

    PartsOfEquation part   = LEFT_PART;
    SolverErrors errorCode = NORMAL;

    int prevSymbol = 0;
    int symbol     = getchar();

    int sign = +1;

    while ( symbol != '\n' ) {
        if ( symbol == 'q' && prevSymbol == 0 ) {
            return readExit();
        }
        else if ( symbol == ' ' ) {
        }
        else if ( symbol == '+' || symbol == '-' ) {
            if ( prevSymbol == '+' || prevSymbol == '-' || prevSymbol == '*' || prevSymbol == '/' ) {
                skipInput(symbol);
                return TOO_MANY_OPERATIONS;
            }

            sign = readSign(symbol, part);
        }
        else if ( symbol == '=' ) {
            sign = -1;

            if (part == RIGHT_PART) {
                skipInput(symbol);
                return TWO_OR_MORE_EQUALS;
            }

            part = RIGHT_PART;
        }
        else if ( symbol == '\n' ) {
            return NORMAL;
        }
        else if ( isBeginningMonomial(symbol) ) {
            double num = 0.0;
            int power  = 0;

            errorCode = readMonomial(&symbol, &prevSymbol, &power, &num);
            if ( errorCode != NORMAL ) {
                skipInput(symbol);
                return errorCode;
            }

            errorCode = writeMonomial(sign, num, power, coefficient);
            continue;
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

    return NORMAL;
}

bool isBeginningMonomial(int symbol)
{
    if (isdigit(symbol) || symbol == 'x') {
        return 1;
    }

    return 0;
}

bool isEndingMonomial(int symbol, int prevSymbol)
{
    if (strchr("+-=\n", symbol) && (tolower(prevSymbol) != 'x' || tolower(prevSymbol) != 'e') ) {
        return 1;
    }

    return 0;
}

SolverErrors writeMonomial(int sign, double num, int power, EquationData * coefficient)
{
    CUSTOM_ASSERT(coefficient != NULL);

    num *= sign;

    switch (power) {
    case 2:
        coefficient->a += num;
        break;
    case 1:
        coefficient->b += num;
        break;
    case 0:
        coefficient->c += num;
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
    setColor(STANDART);
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
    int symbol   = 0;

    printf("Enter accuracy of output: ");

    while ( (symbol = getchar()) != '\n' ) {
        if ( !(isdigit(symbol)) || (accuracy == 0 && symbol == '0') ) {
            skipInput(symbol);
            accuracy = 0;
            printf("Wrong input. Try again: ");
        }
        else {
            accuracy = accuracy * 10 + symbol - '0';
        }
    }

    return accuracy;
}

void goodBye()
{
    printf("Thank you for using my program. Good bye!");
}
