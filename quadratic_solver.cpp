#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double eps = 1e-37;
const int normalAccuracy = 3;

void mainmenu(char * choice);

void input(double coefficient[], int * errorCode);

void error(int errorCode);

void output(double a, double b, double c, int err, int accuracy);

int getAccuracy(void);

void skipInput(void);

void goodBye(void);

int isDigit(char symbol);

void simpleMode(void);

void detailMode(void);

int record(int ifNum, int sign, double num, int ifMult, double multiplicatedNum, int signE, int numInE, int power, double coefficient[]);

int readQ(void);

int readNum(char symbol, int ifE, int * numInE, int signE, int inFractional, double * num, int * ifNum);

int readDot(int * inFractional, int * signE, int inE);

int readE(int * ifE, int * tempNumInE, int * numInE, int * signE, int * inFractional);

void readX(int * ifMult, int * power);

int main()
{
    char choice = 0;

    mainmenu(&choice);
    while (choice != 'q'){
        (choice == 'a') ? simpleMode() : detailMode();
        mainmenu(&choice);
    }
    goodBye();
}

void mainmenu(char * u)
{
    printf("\nQuadratic equation solver\n");
    printf("Program has two modes of work:\n");
    printf("Simple mode - mode with minimum output and opportunity to enter equations endlessly.\n");
    printf("Detail mode - mode, that instructing you, but you can enter only one equation\n");
    printf("(For first use recommended to use Detail mode)\n");
    printf("Choose mode:\n");
    printf("a - Simple mode\n");
    printf("b - Detail mode\n");
    printf("Or enter \"q\" for quit\n");

    *u = getchar();
    while (getchar() != '\n' || (*u != 'b' && *u != 'a' && *u != 'q')){
        printf("Wrong input. Try again:\n");
        skipInput();
        *u = getchar();
    }
}

void simpleMode(void)
{
    printf("Enter your equations. To exit to the menu enter \"q\".\n");
    int errorCode = 0;
    double koef[3];
    while (errorCode != -1){
        koef[0] = koef[1] = koef[2] = 0.0;
        input(koef, &errorCode);
        //printf("%lf, %lf, %lf\n", koef[2], koef[1], koef[0]);
        output(koef[2], koef[1], koef[0], errorCode, normalAccuracy);
    }
}

void detailMode(void)
{
    int errorCode = 0;
    double koef[3] = {};

    printf("Enter your equation. To exit to the menu enter \"q\".\n");
    printf("Program can't solve equations with brackets.\n");
    printf("Program ignores blanks.\n");
    printf("For writing square of x you can use \"xx\"\n");
    input(koef, &errorCode);
            printf("test\n");
    if (errorCode == -1){
        return;
    }
    int accuracy = getAccuracy();
    output(koef[2], koef[1], koef[0], errorCode, accuracy);
}

int record(int ifNum, int sign, double num, int ifMult, double multiplicatedNum, int tempNumInE, int numInE, int power, double coefficient[])
{
    numInE += tempNumInE;
    if (numInE != 0){
        if (numInE > 0)
            for(;numInE > 0; numInE--, num *= 10.0);
        else
            for(;numInE < 0; numInE++, num /= 10.0);
    }
    if (!ifNum && fabs(num) < eps)
        num = 1.0;
    if (power > 2){
        skipInput();
        return -4;
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

    while ((v = getchar()) != '='){ // считывание левой части уравнения
        if (v == 'q')
            *errorCode = readQ();
        else if (isDigit(v))
            *errorCode = readNum(v, ifE, &numInE, signE, inFractional, &num, &ifNum);
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
            readX(&ifMult, &power);
        }
        else if (v == '+'){
            if (prevSymbol == 'e' || prevSymbol == 'E'){
                signE = +1;
            }
            else{
                record(ifNum, sign, num, ifMult, multiplicatedNum, tempNumInE, numInE, power, coefficient);
                power = innum = ifNum = num = numInE = ifE = inFractional = prevSymbol = ifMult = multiplicatedNum = tempNumInE = 0;
                sign = +1;
            }
        }
        else if (v == '-'){
            if (prevSymbol == 'e' || prevSymbol == 'E'){
                signE = -1;
            }
            else{
                record(ifNum, sign, num, ifMult, multiplicatedNum, tempNumInE, numInE, power, coefficient);
                power = innum = ifNum = num = numInE = ifE = inFractional = prevSymbol = ifMult = multiplicatedNum = tempNumInE = 0;
                sign = -1;
            }
        }
        else if (v == ' ');
        else{ // ошибка в случае ввода постороннего символа
            *errorCode = -2;
            skipInput();
        }
        if (*errorCode != 0)
            return;
        prevSymbol = v;
    }
    record(ifNum, sign, num, ifMult, multiplicatedNum, tempNumInE, numInE, power, coefficient);
    power = innum = ifNum = num = numInE = ifE = inFractional = prevSymbol = ifMult = multiplicatedNum = tempNumInE = 0;
    sign = -1;
    while (((v = getchar()) != '\n')){ // считывание правой части уравнения
        if (isDigit(v)){
            *errorCode = readNum(v, ifE, &numInE, signE, inFractional, &num, &ifNum);
        }
        else if ((v == '.') || (v == ',')){
            *errorCode = readDot(&inFractional, &signE, ifE);
        }
        else if (v == 'e' || v == 'E'){
            *errorCode = readE(&ifE, &tempNumInE, &numInE, &signE, &inFractional);
        }
        else if (v == 'x'){
            readX(&ifMult, &power);
        }
        else if (v == '=')
        {
            *errorCode = -3;
            skipInput();
        }
        else if (v == '+'){
            if (prevSymbol == 'e' || prevSymbol == 'E'){
                signE = +1;
            }
            else{
                record(ifNum, sign, num, ifMult, multiplicatedNum, tempNumInE, numInE, power, coefficient);
                power = innum = ifNum = num = numInE = ifE = inFractional = prevSymbol = ifMult = multiplicatedNum = tempNumInE = 0;
                sign = -1;
            }
        }
        else if (v == '-'){
            if (prevSymbol == 'e' || prevSymbol == 'E'){
                signE = -1;
            }
            else{
                record(ifNum, sign, num, ifMult, multiplicatedNum, tempNumInE, numInE, power, coefficient);
                power = innum = ifNum = num = numInE = ifE = inFractional = prevSymbol = ifMult = multiplicatedNum = tempNumInE = 0;
                sign = +1;
            }
        }
        else if (v == ' ');
        else{
            *errorCode = -2;
            skipInput();
            return;
        }
        if (*errorCode != 0)
            return;
    }
    record(ifNum, sign, num, ifMult, multiplicatedNum, tempNumInE, numInE, power, coefficient);
}

int readQ(void)
{
    if (getchar() == '\n'){
        return -1;
    }
    else{
        skipInput();
        return -2;
    }
}

int readNum(char symbol, int ifE, int * numInE, int signE, int inFractional, double * num, int * ifNum)
{
    if (ifE)
        *numInE = *numInE * 10 + signE * (symbol - '0');
    else{
        if (inFractional)
            *numInE -= 1;
        *num = *num * 10 + symbol - '0';
        *ifNum = 1;
    }
    return 0;
}

int readDot(int * inFractional, int * signE, int inE)
{
    if (*inFractional){
        skipInput();
        return -5;
    }
    if (inE){
        skipInput();
        return -6;
    }
    *inFractional = 1;
    *signE = -1;
    return 0;
}

void readX(int * ifMult, int * power)
{
    if (*ifMult == 1 || *ifMult == 0){
        *power += 1;
        *ifMult = 1;
    }
    else
        *power-=1;
}
int readE(int * ifE, int * tempNumInE, int * numInE, int * signE, int * inFractional)
{
    if (*ifE){
        skipInput();
        return -7;
    }
    *ifE = 1;
    *inFractional = 0;
    *tempNumInE += *numInE;
    *numInE = 0;
    *signE = +1;
    return 0;
}

void error(int errorCode)
{
    if (errorCode == -2)
        printf("ERROR: Unknown symbol in input\n");
    if (errorCode == -3)
        printf("ERROR: Two or more \'=\' symbols\n");
    if (errorCode == -4)
        printf("ERROR: Power of your equation is more then two\n");
    if (errorCode == -5)
        printf("ERROR: Two or more \'.\' symbols in one number\n");
    if (errorCode == -6)
        printf("ERROR: Exponential part can be only integer\n");
    if (errorCode == -7)
        printf("ERROR: In one number can be only one exponential part\n");
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

int getAccuracy(void)
{
    int accuracy = 0;
    char v = 0;
    printf("Enter accuracy of output: ");
    while ((v = getchar()) != '\n'){ // считывание точности
    if (!(isDigit(v)) || (accuracy == 0 && v == '0')){
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

int isDigit(char symbol)
{
    if (symbol >= '0' && symbol <= '9')
        return 1;
    else
        return 0;
}
