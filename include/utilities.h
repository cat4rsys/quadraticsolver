#ifndef H_UTILITIES
#define H_UTILITIES

enum StatusDouble
{
    GREATER,
    EQUALS,
    LESS
};

void customAssert(bool expression, const char * file, int line);

StatusDouble compareDouble(double number1, double number2);

void skipInput(int symbol);

#endif // H_UTILITUS
