#ifndef H_UTILITIES
#define H_UTILITIES

const double eps            = 1e-25; /**< error of double */

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
 * \param file - name of file in which assert used
 * \param line - number of line in which assert used
 */
void customAssert(bool expression, const char * file, int line);

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
 * \param symbol - last entered symbol */
void skipInput(int symbol);

#endif // H_UTILITUS
