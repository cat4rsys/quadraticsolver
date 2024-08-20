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
    if (getchar() != '\n' || (*u != 'b' && *u != 'a' && *u != 'q')) {
        printf("Wrong input. Try again:\n");
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
    input(koef);
    if (errorCode == RETURN_IN_MAIN_MENU)
        return;
    int accuracy = getAccuracy();
    output(koef[2], koef[1], koef[0], errorCode, accuracy);
    printf("Enter anything for exit to the menu\n");
    skipInput();
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
