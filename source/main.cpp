#include <stdio.h>
#include "iosolver.h"

int main(int argc, char * argv[])
{
    if (argc != 2) {
        printBootError();
        return 1;
    }

    pickMode(argv[1]);
}
