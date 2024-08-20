#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "..\include\read.h"
#include "..\include\iosolver.h"

int main()
{
    char choice = 0;

    mainMenu(&choice);
    while (choice != 'q') {
        (choice == 'a') ? simpleMode() : detailMode();
        system("cls");
        mainMenu(&choice);
    }
    goodBye();
}
