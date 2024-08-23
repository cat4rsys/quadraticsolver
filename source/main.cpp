#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>
#include "read.h"
#include "iosolver.h"
#include "solve.h"

int main(int argc, char * argv[])
{
    if (argc != 2) {
        printBootError();
        return 1;
    }

    pickMode(argv[1]);
}
