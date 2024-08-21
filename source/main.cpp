#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "read.h"
#include "iosolver.h"
#include "solve.h"

int main()
{
    ModesOfWork mode = pickAction();

    while (mode != EXIT) {
        doAction(mode);
        system("cls");
        mode = pickAction();
    }

    goodBye();
}
