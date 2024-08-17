/*------------------------------------------------------------------------------------------------------
                                               read.h
        funcs, that reads symbols and returns zero or returns not-zero if there is error in input
readQ   - func, that reads "q" and returns as errorCode -1 if user wrote "q\n" and -2 if user wrote
          anything else
readNum - func, that reads any number. returns as errorCode -8 if user wrote number after "x"
readDot - func, that reads dot. returns as errorCode -5 if in number two or more "." or -6 if exponential
          part has "."
readE   - func, that reads "e" or "E" as beginning of exponential part. returns -7 as errorCode if there
          are two or more exponential parts in one number
readX   - func, that reads
------------------------------------------------------------------------------------------------------*/
int readQ(void);

int readNum(char symbol, char prevSymbol, int ifE, int * numInE, int signE, int inFractional, double * num, int * ifNum);

int readDot(int * inFractional, int * signE, int inE);

int readE(int * ifE, int * tempNumInE, int * numInE, int * signE, int * inFractional);

int readX(int * ifMult, int * power, int ifNum, double * num);
