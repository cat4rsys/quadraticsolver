#ifndef H_SOLVE
#define H_SOLVE
#include <stdio.h>

/**
 * \brief Enumeration for number of roots
 */
enum NumberOfRoots
{
    ZERO_ROOTS,                                  /**< Equation has zero roots */
    ONE_ROOT,                                    /**< Equation has one root */
    TWO_ROOTS,                                   /**< Equation has two roots */
    INF_ROOTS                                    /**< Equation has infinity number of roots */
};

/**
 * \brief Enumeration for types of equations
 */
enum TypeOfEquation
{
    SQUARE,                                      /**< ax^2 + bx + c = 0 */
    SQUARE_WITHOUT_C,                            /**< ax^2 + bx = 0 */
    LINEAR,                                      /**< bx + c = 0 */
    WITHOUT_VARIABLE                             /**< c = 0 */
};

/**
 * \brief Struct for information about equation, user entered
 */
struct EquationData
{
    double a;                                    /**< a-coefficient */
    double b;                                    /**< b-coefficient */
    double c;                                    /**< c-coefficient */
    TypeOfEquation type;                         /**< Type of equation */
};

/**
 *\brief Struct for information about roots
 */
typedef struct
{
    double x1;                                   /**< Less root */
    double x2;                                   /**< Greater root */
    NumberOfRoots numberOfRoots;                 /**< Number of roots */
} Roots;

/**
 * \brief  Solves equation and writes roots
 * \param  coefficient - struct with coefficients and type of equation
 * \return Roots and number of roots. Function writes it in struct Roots
 */
void solveEquation(EquationData coefficient, Roots * root);

/**
 * \brief  Gets type of equation by coefficients
 * \param  coefficient - coefficients of equation
 * \return type of equation
 */
TypeOfEquation getType(EquationData coefficient);

#endif // H_SOLVE
