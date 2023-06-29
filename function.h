#ifndef FUNCTION_LIB
#define FUNCTION_LIB

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <cassert>

/** \brief constant value for epsilon
 *
 */

const double EPSILON = 1e-6;

/** \brief constant value for number of unit tests
 *
 */
const int TEST_COUNT = 10;

/** \brief struct for unit tests
 *
 * \param a - quadratic coefficient
 * \param b - linear coefficient
 * \param c - free term
 * \param x1 - first solution
 * \param x2 - second solution
 * \param nSolutions - number of solutions
 */
struct tests
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
    int nSolutions;
};

/** \brief doubles compare (equal or not, and why)
 *
 */
enum for_compare_doubles
{
    EQUAL,
    FIRST_IS_BIGGER,
    SECOND_IS_BIGGER
};

/** \brief correct/uncorrect input
 *
 */
enum check_correct_input
{
    UNCORRECT_INPUT,
    CORRECT_INPUT
};

/** \brief zero/not a zero value
 *
 */
enum check_zero
{
    NOT_A_ZERO,
    ZERO
};

/** \brief number of solutions for quadratic equation
 *
 */
enum number_of_solutions {
    INFINITE_NUMBER_OF_SOLUTIONS = -1,
    NO_SOLUTIONS,
    ONE_SOLUTION,
    TWO_SOLUTIONS
};

/** \brief calculates the discriminate
 *
 * \param a - quadratic coefficient
 * \param b - linear coefficient
 * \param c - free term
 * \return double value of discriminate
 */
double solve_discriminate (const double a, const double b, const double c);

/** \brief finds the largest number of two
 *
 * \param val1 - first number to compare
 * \param val2 - second number to compare
 * \return double value of the largest number
 */
double max_for_doubles (const double val1, const double val2);

/** \brief finds the smallest number of two
 *
 * \param val1 - first number to compare
 * \param val2 - second number to compare
 * \return double value of the smallest number
 */
double min_for_doubles (const double val1, const double val2);

/** \brief print solutions of eduation
 *
 * \param nSolutions - number of solutions
 * \param x1 - first solution
 * \param x2 - second solution
 */
void show_roots (const int nSolutions, const double x1, const double x2);

/** \brief solve quadratic or linear equation
 *
 * \param a - quadratic coefficient
 * \param b - linear coefficient
 * \param c - free term
 * \param x1 - first solution
 * \param x2 - second solution
 * \param nSolutions - number of solutions
 */
void solve_all (const double a, const double b, const double c, double* x1, double* x2, int* nSolutions);

/** \brief unit test once
 *
 * \param a - quadratic coefficient
 * \param b - linear coefficient
 * \param c - free term
 * \param true_x1 - correct value of first root
 * \param true_x2 - correct value of second root
 * \param true_nSolutions - correct value of number of roots
 * \return int test result (0 - incorrect, 1 - correct)
 */
int one_quadratic_unit_test (const double a, const double b, const double c, double true_x1, double true_x2, const int true_nSolutions);

/** \brief get coefficients of quadratic equation
 *
 * \param a - quadratic coefficient
 * \param b - linear coefficient
 * \param c - free term
 * \return int if input correct (0 - incorrect, 1 - correct)
 */
int scan_coefficients (double* a, double* b, double* c);

/** \brief compares two numbers
 *
 * \param val1 - first number to compare
 * \param val2 - second number to compare
 * \return int compare result (0 - numbers are equal, 1 - first if bigger, 2 - second is bigger)
 */
int compare_two_doubles (const double val1, const double val2);

/** \brief solve quadratic equation
 *
 * \param a - quadratic coefficient
 * \param b - linear coefficient
 * \param c - free term
 * \param x1 - first solution
 * \param x2 - second solution
 * \return int number of solutions
 */
int solve_quadratic (const double a, const double b, const double c, double* x1, double* x2);

/** \brief solve linear equation
 *
 * \param b - linear coefficient
 * \param c - free term
 * \param x - solution
 * \return int number of solutions
 */
int solve_linear (const double b, const double c, double* x);

/** \brief checks if the number is equal to zero
 *
 * \param value - the number
 * \return int result of checking (0 - not a zero, 1 - zero)
 */
int check_zero_value (const double value);

/** \brief do many unit tests and show number of errors
 *
 */
void all_unit_tests_for_quadratic ();

#endif
