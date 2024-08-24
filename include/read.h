#ifndef H_READ
#define H_READ
#include "iosolver.h"
#include "solve.h"

/**
 * \brief Reads "q\n", entered by user
 *
 * \return codeError        - code of error
 *
 * \note If user entered something, that starts with q, but it is not "q\n", function returns UNKNOWN_SYMBOL
 */
SolverErrors readExit();

/**
 * \brief Reads one number. Stops when user enters not a number
 *
 * \param symbol            - entered by user symbol
 * \param prevSymbol        - previously entered by user symbol
 * \param num               - readable number
 *
 * \return num              - number, that user entered
 * \return codeError        - code of error
 */
SolverErrors readNum(int * symbol, int * prevSymbol, double * num);

/**
 * \brief Reads exponential part of number
 *
 * \param symbol            - entered by user symbol
 * \param prevSymbol        - previously entered by user symbol
 * \param num               - number, that stands before 'e' or 'E' symbol
 *
 * \return num              - number after transformations
 * \return errorCode        - code of error
 */
SolverErrors readE(int * symbol, int * prevSymbol, double * num);

/**
 * \brief Reads the 'x' or 'X' symbol
 *
 * \param ifMult            - if user wrote '/' equals -1, if user wrote '*' equals 1, if user
 *                            did not wrote one of this symbols before in this monomial equals 0
 * \param power             - power of monomial before entering 'x' or 'X' symbol
 * \param ifNum             - if user wrote number ifNum equals 1, if not - ifNum equals 0
 * \param num               - number, that user entered
 *
 * \return num              - number after entering 'x' or 'X' symbol
 * \return errorCode        - code of error, if it is in input, or NORMAL if input correct
 * \return power            - power of monomial after entering 'x' or 'X' symbol
 *
 * \note If user did not entered the number, num will equal 1.0 after entering 'x' or 'X' symbol (for example x = 1*x) \n
 * In this function errorCode is always NORMAL
 */
SolverErrors readVar(int ifMult, int * power, int ifNum, double * num);

/**
 * \brief Reads the '*' or '/' symbol
 *
 * \param symbol            - entered by user symbol
 * \param prevSymbol        - previously entered by user symbol
 * \param multiplicatedNum  - equivalent number of numbers, that was entered before last number
 * \param num               - lastly entered number
 *
 * \return multiplicatedNum - equivalent number of all entered numbers
 * \return ifMult           - if user wrote '/' equals -1, if user wrote '*' equals 1, if user \n
 *                            did not wrote one of this symbols before in this monomial equals 0
 * \return errorCode        - code of error, if it is in input, or NORMAL if input correct
 */
SolverErrors readMultiplication(int * symbol, int * prevSymbol, double * multiplicatedNum, double * num, int * ifMult);

/**
 * \brief + or - between monomials
 *
 * \param symbol           - symbol, that was enterred between two monomials
 * \param part             - left or right part of equation?
 *
 * \return sign of next monomial
 */
int readSign(int symbol, PartsOfEquation part);

/**
 * \brief Reads one monomial
 *
 * \param symbol           - enterred by user symbol
 * \param prevSymbol       - previously enterred by user symbol
 * \param power            - power of monomial
 * \param number           - coefficient of monomial
 *
 * \return power and coefficient of entered monomial
 */
SolverErrors readMonomial(int * symbol, int * prevSymbol, int * power, double * number);

/**
 * \brief Records symbol and reads next
 *
 * \param symbol           - processed symbol
 * \param prevSymbol       - previously processed symbol
 *
 * \return symbol          - new, not-processed symbol
 * \return prevSymbol      - processed symbol (before readNext - symbol)
 */
void readNext(int * symbol, int * prevSymbol);

#endif // H_READ
