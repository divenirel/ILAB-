#include "functions.h"

double solve_discriminate (const double a, const double b, const double c)
{
    assert(std::isfinite(a));
    assert(std::isfinite(b));
    assert(std::isfinite(c));

    double discriminate = NAN;
    discriminate = b * b - 4 * a * c;

    return discriminate;
}

int scan_coefficients (double* a, double* b, double* c)
{
    assert(a);
    assert(b);
    assert(c);

    int nInput = scanf("%lg %lg %lg", a, b, c);

    if (nInput == 3) return CORRECT_INPUT;
    else             return UNCORRECT_INPUT;
}

int solve_linear (const double b, const double c, double* x)
{
    assert(x);
    assert(std::isfinite(b));
    assert(std::isfinite(c));

    if (check_zero_value(b) == ZERO)
    {
        if (check_zero_value(c) == NOT_A_ZERO)
        {
            return NO_SOLUTIONS;
        }
        else
            return INFINITE_NUMBER_OF_SOLUTIONS;
    }
    else
    {
        *x = -c / b;
        if (check_zero_value(c) == ZERO)
            *x = fabs(*x);

        return ONE_SOLUTION;
    }

}

int solve_quadratic (const double a, const double b, const double c, double* x1, double* x2)
{
        assert(std::isfinite(a));
        assert(std::isfinite(b));
        assert(std::isfinite(c));
        assert(x1);
        assert(x2);
        assert(x1 != x2);

        if (check_zero_value(a) == ZERO)
        {
            int solution_counter = solve_linear(b, c, x1);
            return solution_counter;
        }

        if (check_zero_value(c) == ZERO)
        {
            *x1 = 0;
            int tmp_solution_counter = solve_linear(a, b, x2) + 1;
            if (compare_two_doubles(*x1, *x2) == EQUAL)
                tmp_solution_counter -= 1;

            return tmp_solution_counter;
        }

        double discriminate = solve_discriminate (a, b, c);

        if (compare_two_doubles(discriminate, 0) == SECOND_IS_BIGGER)
        {
            return NO_SOLUTIONS;
        }

        double sqrt_disc = sqrt(discriminate);
        double a_multiply_2 = 2 * a;

        if (compare_two_doubles(discriminate, 0) == FIRST_IS_BIGGER)
        {
           *x1 = (-b + sqrt_disc) / a_multiply_2;
           *x2 = (-b - sqrt_disc) / a_multiply_2;
           //printf ("x1 = %lg, x2 = %lg\n", *x1, *x2);
           return TWO_SOLUTIONS;
        }
        else if (check_zero_value(discriminate))
        {
           *x1 = -b / a_multiply_2;
           return ONE_SOLUTION;
        }
        else
        {
           return NO_SOLUTIONS;
        }
}

int check_zero_value (const double value)
{
    assert(std::isfinite(value));

    if (compare_two_doubles(fabs(value), EPSILON) == SECOND_IS_BIGGER)
        return ZERO;
    else
        return NOT_A_ZERO;
}

int compare_two_doubles (const double val1, const double val2)
{
    assert(std::isfinite(val1));
    assert(std::isfinite(val2));

    if      (fabs(val1 - val2) < EPSILON)   return EQUAL;
    else if (val1 - val2 > 0 )              return FIRST_IS_BIGGER;
    else                                    return SECOND_IS_BIGGER;
}

void solve_all (const double a, const double b, const double c, double* x1, double* x2, int* nSolutions)
{
    if (check_zero_value(a) == NOT_A_ZERO)
    {
        *nSolutions = solve_quadratic (a, b, c, x1, x2);
    }
    else
        *nSolutions = solve_linear (b, c, x1);
}

int one_quadratic_unit_test (const double a, const double b, const double c, double true_x1, double true_x2, const int true_nSolutions)
{
    double x1 = NAN;
    double x2 = NAN;
    int nSolutions = -2;

    solve_all (a, b, c, &x1, &x2, &nSolutions);

    switch (nSolutions)
    {
        case NO_SOLUTIONS:

            if (nSolutions == true_nSolutions)
            {
                printf ("OK\n");
                return 0;
            }
            else
            {
                printf ("ERROR ! nSolutions = %d, true_nSolutions = %d\n", nSolutions, true_nSolutions);
                return 1;
            }

        case ONE_SOLUTION:

            if (compare_two_doubles(x1, true_x1) == EQUAL)
            {
                printf ("OK\n");
                return 0;
            }
            else
            {
                printf ("ERROR ! nSolutions = %d, true_nSolutions = %d, x1 = %lg, true_x1 = %lg\n", nSolutions, true_nSolutions, x1, true_x1);
                return 1;
            }

        case TWO_SOLUTIONS:
        {
            double tmp_x1 = x1;
            double tmp_x2 = x2;
            x1 = max_for_doubles(tmp_x1,tmp_x2);
            x2 = min_for_doubles(tmp_x1,tmp_x2);
            tmp_x1 = true_x1;
            tmp_x2 = true_x2;
            true_x1 = max_for_doubles(tmp_x1,tmp_x2);
            true_x2 = min_for_doubles(tmp_x1,tmp_x2);

            if (compare_two_doubles(x1, true_x1) == EQUAL && compare_two_doubles(x2, true_x2) == EQUAL)

            {
                printf ("OK\n");
                return 0;
            }
            else
            {
                printf ("ERROR ! nSolutions = %d, true_nSolutions = %d, x1 = %lg, true_x1 = %lg, x2 = %lg, true_x2 = %lg\n",
                        nSolutions, true_nSolutions, x1, true_x1, x2, true_x2);
                return 1;
            }
        }
        case INFINITE_NUMBER_OF_SOLUTIONS:

            if (nSolutions == true_nSolutions)
            {
                printf ("OK\n");
                return 0;
            }
            else
            {
                printf ("ERROR ! nSolutions = %d, true_nSolutions = %d\n", nSolutions, true_nSolutions);
                return 1;
            }

        default:

            printf ("ERROR!!! %d solutions", nSolutions);
            return 1;
    }
}

void all_unit_tests_for_quadratic ()
{
    tests test[TEST_COUNT] = {0, 0, 0, 1, 1, -2};
    test[0] = {0.001, -0.001, 1, NAN, NAN, NO_SOLUTIONS};
    test[1] = {5, 0, 0, 0, NAN, ONE_SOLUTION};
    test[2] = {4, 0, -3, sqrt(3)/2, -sqrt(3)/2, TWO_SOLUTIONS};
    test[3] = {4, 0, 36, NAN, NAN, NO_SOLUTIONS};
    test[4] = {4, -7, 0, 0, 7.0/4, TWO_SOLUTIONS};
    test[5] = {1, -84, 12, 42-2*sqrt(438), 42+2*sqrt(438), TWO_SOLUTIONS};
    test[6] = {1, -3, -4, 4, -1, TWO_SOLUTIONS};
    test[7] = {1, -6, 9, 3, NAN, ONE_SOLUTION};
    test[8] = {5, 2, 3, NAN, NAN, NO_SOLUTIONS};
    test[9] = {0, 0, 0, NAN, NAN, INFINITE_NUMBER_OF_SOLUTIONS};

    int errors = 0;

    for (int i = 0 ; i < TEST_COUNT ; i++)
    {
        printf ("%d) ", i+1);
        errors += one_quadratic_unit_test (test[i].a, test[i].b, test[i].c, test[i].x1, test[i].x2, test[i].nSolutions);
    }
    printf ("Number of errors: %d\n", errors);
}

double max_for_doubles (const double val1, const double val2)
{
    if (    compare_two_doubles(val1, val2) == FIRST_IS_BIGGER
        ||  compare_two_doubles(val1, val2) == EQUAL)
        return val1;
    else return val2;
}

double min_for_doubles (const double val1, const double val2)
{
    if (    compare_two_doubles(val1, val2) == FIRST_IS_BIGGER
        ||  compare_two_doubles(val1, val2) == EQUAL)
        return val2;
    else return val1;
}

void show_roots (const int nSolutions, const double x1, const double x2)
{
    switch (nSolutions)
    {
        case NO_SOLUTIONS:
            printf ("There are no solutions\n");
            break;
        case ONE_SOLUTION:
            printf ("The only solution is: %lg\n", x1);
            break;

        case TWO_SOLUTIONS:
            printf ("x1 = %lg, x2 = %lg\n", x1, x2);
            break;

        case INFINITE_NUMBER_OF_SOLUTIONS:
            printf ("Any number is solution\n");
            break;

        default:
            printf ("ERROR!!! %d solutions\n", nSolutions);
            break;
    }
}
