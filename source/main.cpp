#include "iosolver.h"

int main(int argc, const char * argv[])
{
    if (argc != 2) {
        printBootError();
        return 1;
    }

    execMode(argv[1]);

    return 0;
}
