#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>
#include "read.h"
#include "iosolver.h"
#include "solve.h"

int main()
{
    system("cls");
    mainMenu();
    ModesOfWork mode = pickAction();

    while (mode != EXIT) {
        doAction(mode);

        system("cls");
        mainMenu();
        mode = pickAction();
    }

    goodBye();
}
