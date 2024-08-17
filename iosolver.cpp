#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "include/read.h"
#include "include/iosolver.h"

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
    if (*u != 'b' && *u != 'a' && *u != 'q') {
        printf("Wrong input. Try again:\n");
        skipInput();
        *u = getchar();
    }
}

void simpleMode()
{
    printf("Enter your equations. To exit to the menu enter \"q\".\n");
    int errorCode = 0;
    double koef[3];
    while (errorCode != RETURN_IN_MAIN_MENU) {
        koef[0] = koef[1] = koef[2] = 0.0;
        input(koef, &errorCode);
        //printf("%lf, %lf, %lf\n", koef[2], koef[1], koef[0]);
        output(koef[2], koef[1], koef[0], errorCode, normalAccuracy);
    }
}

void detailMode()
{
    int errorCode = 0;
    double koef[3] = {};

    printf("Enter your equation. To exit to the menu enter \"q\".\n");
    printf("Program can't solve equations with brackets.\n");
    printf("Program ignores blanks.\n");
    printf("For writing square of x you can use \"xx\"\n");
    input(koef, &errorCode);
            printf("test\n");
    if (errorCode == RETURN_IN_MAIN_MENU)
        return;
    int accuracy = getAccuracy();
    output(koef[2], koef[1], koef[0], errorCode, accuracy);
}

void input(double coefficient[], int * errorCode)
{
    char v; // переменная для ввода решений пользователя
    int sign; // переменная для хранения знака одночлена
    int innum; // переменная для отслеживания внутри ли мы числа
    double num; // переменная для хранения числа
    int power; // переменная для хранения степени одночлена
    int inFractional; // переменная для хранения внутри ли мы дроби
    int numInE; // переменная для хранения экспоненциальной части числа
    int ifE; // переменная для отслеживания внутри ли мы экс. части
    int prevSymbol; // переменная для хранения предыдущего считанного символа
    int signE; // переменная для хранения знака экс. части
    double multiplicatedNum; // переменная для хранения предыдущего значения num для операций * и /
    int ifMult;
    int tempNumInE = 0;
    int ifNum; // переменная для отслеживания был ли ввод числа
    *errorCode = 0;
    power = innum = ifNum = num = numInE = ifE = inFractional = prevSymbol = ifMult = multiplicatedNum = tempNumInE = 0;
    sign = +1;

    while ((v = getchar()) != '=') { // считывание левой части уравнения
        if (v == 'q')
            *errorCode = readExit();
        else if (isdigit(v))
            *errorCode = readNum(v, prevSymbol, ifE, &numInE, signE, inFractional, &num, &ifNum);
        else if ((v == '.') || (v == ','))
            *errorCode = readDot(&inFractional, &signE, ifE);
        else if (v == 'e' || v == 'E')
            *errorCode = readE(&ifE, &tempNumInE, &numInE, &signE, &inFractional);
        else if (v == '*'){
            tempNumInE += numInE;
            numInE = 0;
            ifE = 0;
            inFractional = 0;
            multiplicatedNum *= num;
            ifNum = 0;
            if (ifMult == 0)
                multiplicatedNum = num;
            ifMult = 1;
            num = 0;
        }
        else if (v == '/'){
            ifE = 0;
            inFractional = 0;
            multiplicatedNum /= (num*1.0);
            if (ifMult == 0)
                multiplicatedNum = num;
            ifMult = -1;
            num = 0;
        }
        else if (v == 'x'){
            *errorCode = readVar(&ifMult, &power, ifNum, &num);
        }
        else if (v == '+'){
            if (prevSymbol == 'e' || prevSymbol == 'E'){
                signE = +1;
            }
            else{
                record(sign, num, ifMult, multiplicatedNum, tempNumInE, numInE, power, coefficient);
                power = innum = ifNum = num = numInE = ifE = inFractional = prevSymbol = ifMult = multiplicatedNum = tempNumInE = 0;
                sign = +1;
            }
        }
        else if (v == '-'){
            if (prevSymbol == 'e' || prevSymbol == 'E'){
                signE = -1;
            }
            else{
                record(sign, num, ifMult, multiplicatedNum, tempNumInE, numInE, power, coefficient);
                power = innum = ifNum = num = numInE = ifE = inFractional = prevSymbol = ifMult = multiplicatedNum = tempNumInE = 0;
                sign = -1;
            }
        }
        else if (v == ' ');
        else{ // ошибка в случае ввода постороннего символа
            *errorCode = UNKNOWN_SYMBOL;
            skipInput();
        }
        if (*errorCode != 0)
            return;
        prevSymbol = v;
    }
    record(sign, num, ifMult, multiplicatedNum, tempNumInE, numInE, power, coefficient);
    power = innum = ifNum = num = numInE = ifE = inFractional = prevSymbol = ifMult = multiplicatedNum = tempNumInE = 0;
    sign = -1;
    while (((v = getchar()) != '\n')){ // считывание правой части уравнения
        if (isdigit(v)){
            *errorCode = readNum(v, prevSymbol, ifE, &numInE, signE, inFractional, &num, &ifNum);
        }
        else if ((v == '.') || (v == ',')){
            *errorCode = readDot(&inFractional, &signE, ifE);
        }
        else if (v == 'e' || v == 'E'){
            *errorCode = readE(&ifE, &tempNumInE, &numInE, &signE, &inFractional);
        }
        else if (v == 'x'){
            *errorCode = readVar(&ifMult, &power, ifNum, &num);
        }
        else if (v == '=')
        {
            *errorCode = TWO_OR_MORE_EQUALS;
            skipInput();
        }
        else if (v == '+'){
            if (prevSymbol == 'e' || prevSymbol == 'E'){
                signE = +1;
            }
            else{
                record(sign, num, ifMult, multiplicatedNum, tempNumInE, numInE, power, coefficient);
                power = innum = ifNum = num = numInE = ifE = inFractional = prevSymbol = ifMult = multiplicatedNum = tempNumInE = 0;
                sign = -1;
            }
        }
        else if (v == '-'){
            if (prevSymbol == 'e' || prevSymbol == 'E'){
                signE = -1;
            }
            else{
                record(sign, num, ifMult, multiplicatedNum, tempNumInE, numInE, power, coefficient);
                power = innum = ifNum = num = numInE = ifE = inFractional = prevSymbol = ifMult = multiplicatedNum = tempNumInE = 0;
                sign = +1;
            }
        }
        else if (v == ' ');
        else{
            *errorCode = UNKNOWN_SYMBOL;
            skipInput();
            return;
        }
        if (*errorCode != 0)
            return;
    }
    record(sign, num, ifMult, multiplicatedNum, tempNumInE, numInE, power, coefficient);
}

int record(int sign, double num, int ifMult, double multiplicatedNum, int tempNumInE, int numInE, int power, double coefficient[])
{
    numInE += tempNumInE;
    if (numInE != 0){
        if (numInE > 0)
            for(;numInE > 0; numInE--, num *= 10.0);
        else
            for(;numInE < 0; numInE++, num /= 10.0);
    }
    if (power > 2){
        skipInput();
        return POWER_MORE_THAN_TWO;
    }
    if (fabs(multiplicatedNum) < eps)
        multiplicatedNum = 1;
    if (ifMult == 0)
        coefficient[power] += sign * num;
    else if (ifMult == 1)
        coefficient[power] += sign * num * multiplicatedNum;
    else if (ifMult == -1)
        coefficient[power] += sign * multiplicatedNum / num;
    return 0;
}

void error(int errorCode)
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
        printf("ERROR: After \"x\" expected *, /, +, -");
}

void output(double a, double b, double c, int err, int accuracy)
{
    double d = 0;
    if (err == 0){
        d = b * b - 4 * a * c;
        if (fabs(a) > eps){
            if (fabs(d) < eps)
                printf("x1 = x2 = %.*e\n", accuracy, - b / (2.0 * a) );
            else if (d >= 0){
                d = sqrt(d);
                double firstRoot = (-b + d) / (2 * a);
                double secondRoot = (-b - d) / (2 * a);
                printf("x1 = %.*e, x2 = %.*e\n", accuracy, firstRoot, accuracy, secondRoot);
            }
            else{
                d = sqrt(-d);
                double realRoot = -b / (2.0 * a);
                double imaginaryRoot = d / (2.0 * a);
                printf("x1 = %.*e + %.*e * i, x2 = %.*e + %.*e * i.\n", accuracy, realRoot, imaginaryRoot, realRoot, accuracy, realRoot, accuracy, imaginaryRoot);
            }
        }
        else if (fabs(b) > eps){
            double root = - c / b;
            printf("Equation is linear. x = %.*e.\n", accuracy, root);
        }
        else if (fabs(c) > eps)
            printf("The equation has NO roots!\n");
        else
            printf("The equation has infinite number of roots.\n");
    }
    else{
        error(err);
    }
}

int getAccuracy()
{
    int accuracy = 0;
    char v = 0;
    printf("Enter accuracy of output: ");
    while ((v = getchar()) != '\n'){ // считывание точности
    if (!(isdigit(v)) || (accuracy == 0 && v == '0')){
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
