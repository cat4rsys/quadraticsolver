#ifndef H_IOSOLVER
#define H_IOSOLVER

#include <solve.h>

const int normalAccuracy = 3;                    /**< Accuracy of output in simple mode */

/**
 * \brief Parts of equation
 */
enum PartsOfEquation
{
    LEFT_PART,                                   /**< Left part of equation */
    RIGHT_PART                                   /**< Right part of equation */
};

/**
 * \brief All error codes
 */
enum SolverErrors
{
    NORMAL,                                      /**< No errors */
    RETURN_IN_MAIN_MENU,                         /**< Returning in main menu */
    UNKNOWN_SYMBOL,                              /**< Unknown symbol in input (example: 3*x*t=0) */
    TWO_OR_MORE_EQUALS,                          /**< Two or more equals in input (example: 1=0=3) */
    INCORRECT_POWER,                             /**< Incorrect power of monomial (power can be least or equal 2
                                                                                   and greater or equal 0)       */
    TWO_OR_MORE_FRACTIONAL,                      /**< In one number two or more fractional parts (example: 1.2.3) */
    FLOAT_EXPONENTIAL,                           /**< In one number exponential part is float (example:1e2.3) */
    TWO_OR_MORE_EXPONENTIAL,                     /**< In one number two or more exponential parts (example: 1e2e3) */
    NUM_AFTER_X,                                 /**< After x entered number (example: x3 -> correctly x*3) */
    TOO_MANY_OPERATIONS,                         /**< After symbol of operation entered another
                                                      symbol of operation (example: 1++2) */
    NO_EQUAL                                     /**< In equation is no "=" symbol (example: 12x+xx) */
};

/**
 * \brief Prints help menu if argument equals "--help"
 */
void helpMenu();

/**
 * \brief Picks mode of work by argument of terminal
 */
void pickMode(char * arg);

/**
 * \brief Turns on simple mode
 */
void simpleMode();

/**
 * \brief Turns on detail mode
 */
void detailMode();

/**
 * \brief Turns on test mode
 */
void testMode();

/**
 * \brief Reads all equation, entered by user and records it as coefficient of ax^2 + bx + c = 0
 *
 * \param coefficient - struct for coefficients of equation
 *
 * \return struct with coeffitients of equation
 */
SolverErrors inputOfEquation(EquationData * coefficient);

/**
 * \brief Writes monomial into struct with coeffitients
 *
 * \param sign        - sign of coeffitient
 * \param num         - coeffitient of monomial
 * \param power       - power of monomial
 * \param coeffitient - struct with coeffitients
 *
 * \return Updated struct with coeffitients or error of input
 */
SolverErrors writeMonomial(int sign, double num, int power, EquationData * coefficient);

/**
 * \brief Checks if symbol is beginning of monomial
 *
 * \param symbol - entered symbol
 *
 * \returns 1 if symbol is beginning of monomial and 0 if symbol is not
 */
int isBeginnigMonomial(int symbol);

/**
 * \brief Checks if symbol is ending of monomial
 *
 * \param symbol     - entered symbol
 * \param prevSymbol - previously entered symbol
 *
 * \returns 1 if symbol is beginning of monomial and 0 if symbol is not
 */
int isEndingMonomial(int symbol, int prevSymbol);

/**
 * \brief Prints error, coded by errorCode
 *
 * \param [in] errorCode - code of error
 */
void printInputError(SolverErrors errorCode);

/**
 * \brief Prints error of boot if arguments is incorrect
 */
void printBootError();

/**
 * \brief Prints roots by struct named root or error if it happend
 *
 * \param root      - struct with roots and number of roots
 * \param errorCode - code of error
 * \param accuracy  - accuracy of output
 */
void printRoots(Roots root, SolverErrors errorCode, int accuracy);

/**
 * \brief Gets accuracy
 */
int getAccuracy();

/**
 * \brief Just prints "Good bye" for user
 */
void goodBye();

#endif // H_IOSOLVER
