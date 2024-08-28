#ifndef H_UTILITIES
#define H_UTILITIES

#include "iosolver.h"

const double eps = 1e-25;                        /**< error of double */

// COLORS

const int RED       = 12;                        /**< Red text color */
const int CYAN      = 11;                        /**< Cyan text color */
const int GREEN     = 10;                        /**< Green text color */
const int PURPLE    = 13;                        /**< Purple text color */
const int YELLOW    = 14;                        /**< Yellow text color */
const int STANDART  = 15;                        /**< Standart text color */

/**
 * \brief Result of comparing two doubles
 */
enum StatusDouble
{
    GREATER,                                     /**< First double is greater than second */
    EQUALS,                                      /**< First double equals second */
    LESS                                         /**< First double is less than second */
};

/**
 * \brief Assert, that doesn't stop program. Just gives warning about failed aseertion
 *
 * \param expression - expression for assertion
 */
#define CUSTOM_ASSERT(expression) {                                          \
    if( !expression ) {                                                     \
        setColor(RED);                                                      \
        printf("Assertion failed: file %s, line %d\n", __FILE__, __LINE__); \
        setColor(STANDART);                                                 \
    }                                                                       \
}

/**
 * \brief Compares two doubles
 *
 * \param number1 - first number
 * \param number2 - second number
 *
 * \return status of comparing of two doubles
 */
StatusDouble compareDouble(double number1, double number2);

/**
 * \brief Skips input if last entered symbol not "\n"
 *
 * \param symbol - last entered symbol
 */
void skipInput(int symbol);

/**
 * \brief Sets color for output
 *
 * \param color - number of color
 */
void setColor(int color);

#endif // H_UTILITUS
