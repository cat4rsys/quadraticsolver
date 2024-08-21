#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "..\include\read.h"
#include "..\include\iosolver.h"

void mainMenu(char * u)
{
    printf("Quadratic equation solver\n");
    printf("Program has two modes of work:\n");
    printf("Simple mode - mode with minimum output and opportunity to enter equations endlessly.\n");
    printf("Detail mode - mode, that instructing you, but you can enter only one equation\n");
    printf("(For first use recommended to use Detail mode)\n");
    printf("Choose mode:\n");
    printf("a - Simple mode\n");
    printf("b - Detail mode\n");
    printf("Or enter \"q\" for quit\n");

    *u = getchar();
    char temp = 0;
    while ((temp = getchar()) != '\n' || (*u != 'b' && *u != 'a' && *u != 'q')) {
        printf("Wrong input. Try again:\n");
        if (temp != '\n')
            skipInput();
        *u = getchar();
    }
}

void simpleMode()
{
    printf("Enter your equations. To exit to the menu enter \"q\".\n");
    SolverErrors errorCode = NORMAL;
    double koef[3] = {};

    while (errorCode != RETURN_IN_MAIN_MENU) {
        koef[0] = koef[1] = koef[2] = 0.0;
        errorCode = input(koef);
        //printf("%lf, %lf, %lf\n", koef[2], koef[1], koef[0]);
        output(koef[2], koef[1], koef[0], errorCode, normalAccuracy);
    }
}

void detailMode()
{
    SolverErrors errorCode = NORMAL;
    double koef[3] = {};

    printf("Enter your equation. To exit to the menu enter \"q\".\n");
    printf("Program can't solve equations with brackets.\n");
    printf("Program ignores blanks.\n");
    printf("For writing square of x you can use \"xx\"\n");
    if (input(koef) == RETURN_IN_MAIN_MENU)
        return;
    int accuracy = getAccuracy();
    output(koef[2], koef[1], koef[0], errorCode, accuracy);
    printf("Enter anything for exit to the menu\n");
    skipInput();
}

SolverErrors input(double coefficient[])
{
    PartsOfEquation part = LEFT_PART;
    SolverErrors errorCode = NORMAL;
    char prevSymbol = 0;
    char symbol = getchar();
    int sign = +1;
    while (symbol != '\n') {
        if (symbol == 'q' && prevSymbol == 0)
            return readExit();
        else if (symbol == ' ');
        else if (symbol == '+' || symbol == '-') {
            if (prevSymbol == '+' || prevSymbol == '-' || prevSymbol == '*' || prevSymbol == '/') {
                skipInput();
                return TOO_MANY_OPERATIONS;
            }
            sign = readSign(symbol, part);
        }
        else if (symbol == '=') {
            sign = -1;
            if (part == LEFT_PART)
                part = RIGHT_PART;
            else {
                skipInput();
                return TWO_OR_MORE_EQUALS;
            }
        }
        else if (symbol == '\n') {
            return NORMAL;
        }
        else if (isBeginnigMonomial(symbol)) {
            double num = 0;
            int power = 0;
            if ((errorCode = readMonomial(&symbol, &prevSymbol, &power, &num)) == NORMAL) {
                record(sign, num, power, coefficient);
                continue;
            }
            else {
                skipInput();
                return errorCode;
            }
        }
        else {
            skipInput();
            return UNKNOWN_SYMBOL;
        }
        if (errorCode != NORMAL) {
            skipInput();
            return errorCode;
        }
        readNext(&symbol, &prevSymbol);
    }
    return NORMAL;
}

SolverErrors record(int sign, double num, int power, double coefficient[])
{
    if (power > 2) {
        skipInput();
        return POWER_MORE_THAN_TWO;
    }
    coefficient[power] += sign * num;
    return NORMAL;
}

void error(SolverErrors errorCode)
{
    if (errorCode == UNKNOWN_SYMBOL)
        printf("ERROR: Unknown symbol in input\n");
    if (errorCode == TWO_OR_MORE_EQUALS)
        printf("ERROR: Two or more \'=\' symbols\n");
    if (errorCode == POWER_MORE_THAN_TWO)
        printf("ERROR: Power of your equation is more then two\n");
    if (errorCode == TWO_OR_MORE_FRACTIONAL)
        printf("ERROR: Two or more \'.\' symbols in one number\n");
    if (errorCode == FLOAT_EXPONENTIAL)
        printf("ERROR: Exponential part can be only integer\n");
    if (errorCode == TWO_OR_MORE_EXPONENTIAL)
        printf("ERROR: In one number can be only one exponential part\n");
    if (errorCode == NUM_AFTER_X)
        printf("ERROR: After \"x\" expected *, /, +, -\n");
    if (errorCode == TOO_MANY_OPERATIONS)
        printf("ERROR: You can't write symbol of operation after symbol of operation.\n");
}

void output(double a, double b, double c, SolverErrors errorCode, int accuracy)
{
    double d = 0;
    if (errorCode == NORMAL){
        d = b * b - 4 * a * c;
        if (fabs(a) > eps) {
            if (fabs(d) < eps)
                printf("x1 = x2 = %.*e\n", accuracy, - b / (2.0 * a) );
            else if (d >= 0) {
                d = sqrt(d);
                double firstRoot = (-b + d) / (2 * a);
                double secondRoot = (-b - d) / (2 * a);
                printf("x1 = %.*e, x2 = %.*e\n", accuracy, firstRoot, accuracy, secondRoot);
            }
            else {
                d = sqrt(-d);
                double realRoot = -b / (2.0 * a);
                double imaginaryRoot = d / (2.0 * a);
                printf("x1 = %.*e + %.*e * i, x2 = %.*e + %.*e * i.\n", accuracy, realRoot, imaginaryRoot, realRoot, accuracy, realRoot, accuracy, imaginaryRoot);
            }
        }
        else if (fabs(b) > eps) {
            double root = - c / b;
            printf("Equation is linear. x = %.*e.\n", accuracy, root);
        }
        else if (fabs(c) > eps)
            printf("The equation has NO roots!\n");
        else
            printf("The equation has infinite number of roots.\n");
    }
    else{
        error(errorCode);
    }
}

int isBeginnigMonomial(char symbol)
{
    if (isdigit(symbol) || symbol == 'x')
        return 1;
    else
        return 0;
}

int isEndingMonomial(char symbol, char prevSymbol)
{
    if ((symbol == '+' || symbol == '-' || symbol == '\n' || symbol == '=') && (prevSymbol != 'x' || prevSymbol != 'X' || prevSymbol != 'e' || prevSymbol != 'E'))
        return 1;
    else
        return 0;
}

int getAccuracy()
{
    int accuracy = 0;
    char v = 0;
    printf("Enter accuracy of output: ");
    while ((v = getchar()) != '\n') { // считывание точности
    if (!(isdigit(v)) || (accuracy == 0 && v == '0')) {
        skipInput();
        accuracy = 0;
        printf("Wrong input. Try again: ");
    }
    else
        accuracy = accuracy * 10 + v - '0';
    }
    return accuracy;
}

void skipInput()
{
    while (getchar() != '\n')
        continue;
}

void goodBye()
{
    printf("Thank you for using my program. Good bye!");
}
